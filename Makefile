# Makefile for machine learning C implementation

# Doxygen variables
DOXYGEN = doxygen
DOX_DIR = doxygen
DOX_CFG_FILENAME = ml.config

DOX_CFG_FILE = $(DOX_DIR)/$(DOX_CFG_FILENAME)

DOX_DOC_DIR = doc

# Valgrind variables
VALGRIND=valgrind

MEMCHECKOPTS = --leak-check=full --error-limit=no --show-leak-kinds=all --track-origins=yes
VALGRINDTOOLOPTS =
VALGRINDLOGFILENAME ?= valgrind.log
VALGRINDLOGFILE = $(LOG_DIR)/$(VALGRINDLOGFILENAME)
VALGRINDLOGOPTS = -v --log-file=$(VALGRINDLOGFILE) --time-stamp=yes
VALGRINDEXEARGS ?=

# Makefile variables
VERBOSE = @

MKDIR = mkdir -p

# Executable filename
EXE_NAME ?= ml

# Log directory
LOG_DIR ?= log

# Log filename
LOGFILENAME ?= $(EXE_NAME).log

# Log file
LOGFILE=$(LOG_DIR)/$(LOGFILENAME)

VERBOSITY ?= MEDIUM

# Select compiler:
# - gcc for C files
# - g++ for C++ files
CC = gcc

# Compile-time flags
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic -std=gnu99 -rdynamic
EXTRADFLAGS ?=
DFLAGS = -DLOGFILE="$(LOGFILE)" -DVERBOSITY=$(VERBOSITY)
LIBS= -lm

# Directory containing source and header files
TOP_DIR = top
TEST_DIR = test
LIB_DIR = .

# Directory containing source files
SRC_DIR = src

# Directory containing include files
INCLUDE_DIR = include

# Directory containing object files
OBJ_DIR = obj

# Directory containing binary files
BIN_DIR ?= bin

DIR_LIST = $(LIB_DIR) \
           $(TOP_DIR) \
           $(TEST_DIR)

INCLUDE_PATH = $(LIB_DIR)/$(INCLUDE_DIR) \
               $(TOP_DIR)/$(INCLUDE_DIR) \
               $(TEST_DIR)/$(INCLUDE_DIR)

INCLUDE_PATH := $(foreach DIR, ${DIR_LIST}, $(DIR)/$(INCLUDE_DIR))

INCLUDES := $(foreach INCDIR, ${INCLUDE_PATH}, -I${INCDIR})

SRCS := $(notdir $(wildcard $(foreach DIR, ${DIR_LIST}, $(DIR)/$(SRC_DIR)/*.c)))
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

VPATH = $(LIB_DIR)/$(SRC_DIR) \
        $(TOP_DIR)/$(SRC_DIR) \
        $(TEST_DIR)/$(SRC_DIR)

MAIN = main.c
TOP = $(TOP_DIR)/$(SRC_DIR)/$(MAIN)
EXE = $(BIN_DIR)/$(EXE_NAME)

$(EXE) : $(OBJS)
	$(MKDIR) $(LOG_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE)echo "Compiling $(@F). Object files are: $^"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(DFLAGS) $^ $(LIBS)

$(OBJ_DIR)/%.o : %.c
	$(MKDIR) $(@D)
	$(VERBOSE)echo "Compiling $(<F) and creating object $@"
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< $(DFLAGS) -o $@ $(LIBS)

depend :
	makedepend $(INCLUDES) $^

all : $(EXE)
	$(VERBOSE)echo "Compile machine learning C algorithm"

memleak : $(EXE)
	valgrind $(MEMCHECKOPTS) $(VALGRINDTOOLOPTS) $(VALGRINDLOGOPTS) $(EXE) $(VALGRINDEXEARGS)

debug :
	$(VERBOSE)echo "Compiler: $(CC)"
	$(VERBOSE)echo "Compiler options:"
	$(VERBOSE)echo "--> C flags: $(CFLAGS)"
	$(VERBOSE)echo "--> defines: $(DFLAGS)"
	$(VERBOSE)echo "--> libs: $(LIBS)"
	$(VERBOSE)echo "Files lists:"
	$(VERBOSE)echo "--> Source files: $(SRCS)"
	$(VERBOSE)echo "--> Object files: $(notdir $(OBJS))"
	$(VERBOSE)echo "--> Executable file: $(notdir $(EXE_NAME))"
	$(VERBOSE)echo "Directories lists:"
	$(VERBOSE)echo "--> Source directories: $(VPATH)"
	$(VERBOSE)echo "--> Include directories: $(INCLUDE_PATH)"
	$(VERBOSE)echo "--> Exeutable directory: $(BIN_DIR)"
	$(VERBOSE)echo "--> Log directory: $(LOG_DIR)"

clean :
	$(VERBOSE)echo "Remove object files: $(OBJS)"
	rm -rf $(OBJ_DIR)
	$(VERBOSE)echo "Remove doxygen documentation directory: $(DOX_DOC_DIR)"
	rm -rf $(DOX_DOC_DIR)
	$(VERBOSE)echo "Remove binary file: $(EXE)"
	rm -rf $(BIN_DIR)
	$(VERBOSE)echo "Remove log file: $(LOGFILE)"
	rm -rf $(LOG_DIR)
	$(VERBOSE)echo "Clean completed"

doc :
	$(MKDIR) $(DOX_DOC_DIR)
	$(DOXYGEN) $(DOX_CFG_FILE)

.PHONY: all,clean,depend,$(EXE),debug,doc,memleak
