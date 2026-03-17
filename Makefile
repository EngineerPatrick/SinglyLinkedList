# -------- Toolchain --------
CC      ?= gcc
CSTD    ?= -std=c11

# -------- Layout --------
INC_DIR := include
SRC_DIR := src
APP_DIR := apps/cli
BLD_DIR := build
BIN_DIR := bin
TARGET  := $(BIN_DIR)/Launcher

# -------- Flags --------
WARN := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion \
        -Wcast-qual -Wformat=2 -Wundef -Wwrite-strings

CPPFLAGS ?= -I$(INC_DIR) -I$(APP_DIR)
CFLAGS   ?= $(CSTD) $(WARN) -O2 -g
LDFLAGS  ?=
LDLIBS   ?=

CFLAGS  += $(CFLAGS_EXTRA)
LDFLAGS += $(LDFLAGS_EXTRA)
LDLIBS  += $(LDLIBS_EXTRA)

# -------- Sources --------
LIB_SRC := $(wildcard $(SRC_DIR)/*.c)
APP_SRC := $(wildcard $(APP_DIR)/*.c)

# Put objects in build/ but avoid name collisions by prefixing
LIB_OBJ := $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/lib_%.o,$(LIB_SRC))
APP_OBJ := $(patsubst $(APP_DIR)/%.c,$(BLD_DIR)/app_%.o,$(APP_SRC))

DEP := $(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d)

.PHONY: all clean run sanitize docs

all: $(TARGET)

$(BLD_DIR) $(BIN_DIR):
	mkdir -p $@

# Compile library objects
$(BLD_DIR)/lib_%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Compile app objects
$(BLD_DIR)/app_%.o: $(APP_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Link final executable
$(TARGET): $(LIB_OBJ) $(APP_OBJ) | $(BIN_DIR)
	$(CC) $(LIB_OBJ) $(APP_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

run: $(TARGET)
	./$(TARGET)

SAN := -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: clean
	$(MAKE) all CFLAGS_EXTRA="$(SAN) -O0 -g" LDFLAGS_EXTRA="$(SAN)"

clean:
	rm -rf $(BLD_DIR) $(BIN_DIR) docs/html docs/latex

docs:
	doxygen docs/Doxyfile

-include $(DEP)
