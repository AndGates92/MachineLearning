# Makefile for machine learning C implementation

DATE_FORMAT = %a %d %b %Y
TIME_FORMAT = %H:%M:%S

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

VERBOSITY ?= LOW

# Select compiler:
# - gcc for C files
# - g++ for C++ files
CC = gcc

# Compile-time flags
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic -std=gnu99 -rdynamic
CEXTRAFLAGS ?=
DFLAGS = -DLOGFILE="$(LOGFILE)" -DVERBOSITY=$(VERBOSITY)
LIBS= -lm
GLUTLIBS = -lGLU -lGL -lglut
X11LIBS = -lX11

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
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiling $(@F). Object files are: $^"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(DFLAGS) $(CEXTRAFLAGS) $^ $(LIBS) $(GLUTLIBS) $(X11LIBS)

$(OBJ_DIR)/%.o : %.c
	$(MKDIR) $(@D)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiling $(<F) and creating object $@"
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< $(DFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS) $(GLUTLIBS) $(X11LIBS)

depend :
	makedepend $(INCLUDES) $^

all : $(EXE)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compile machine learning C algorithm"

memleak : $(EXE)
	valgrind $(MEMCHECKOPTS) $(VALGRINDTOOLOPTS) $(VALGRINDLOGOPTS) $(EXE) $(VALGRINDEXEARGS)

debug :
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiler: $(CC)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Compiler options:"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> C flags: $(CFLAGS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> C extra flags: $(CEXTRAFLAGS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> defines: $(DFLAGS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> libs: $(LIBS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> OpenGL GLUT libraries: $(GLUTLIBS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> X11 libraries: $(X11LIBS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Files lists:"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Source files: $(SRCS)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Object files: $(notdir $(OBJS))"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Executable file: $(notdir $(EXE_NAME))"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Directories lists:"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Source directories: $(VPATH)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Include directories: $(INCLUDE_PATH)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Exeutable directory: $(BIN_DIR)"
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] --> Log directory: $(LOG_DIR)"

clean :
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove object files: $(OBJS)"
	rm -rf $(OBJ_DIR)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove doxygen documentation directory: $(DOX_DOC_DIR)"
	rm -rf $(DOX_DOC_DIR)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove binary directory: $(BIN_DIR)"
	rm -rf $(BIN_DIR)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Remove log directory: $(LOG_DIR)"
	rm -rf $(LOG_DIR)
	$(VERBOSE)echo "[${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}] Clean completed"

doc :
	$(MKDIR) $(DOX_DOC_DIR)
	$(DOXYGEN) $(DOX_CFG_FILE)

.PHONY: all,clean,depend,$(EXE),debug,doc,memleak
