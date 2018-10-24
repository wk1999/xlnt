
# git repo position
REPO = $(shell cd .. && pwd)

RM = rm
SED = sed
CXX = g++
CC  = gcc
C_FILES   = $(wildcard *.c)
CPP_FILES = $(wildcard *.cc)
OBJ_DEP   = $(C_FILES:%.c=%.d) $(CPP_FILES:%.cc=%.d)
OBJ_FILES = $(C_FILES:%.c=%.o) $(CPP_FILES:%.cc=%.o)

# obj config
OBJ_NAME = a.out

# flag config
INC_DIRS = -I$(REPO)/include
CFLAGS = -Wall -std=c++17
LDFLAGS = -L$(REPO)/source -lxlnt -Wl,-rpath,$(REPO)/source

all: $(OBJ_NAME)

#use - for the first time where OBJ_DEP not exist
-include $(OBJ_DEP)

%.o: %.cc
	$(CXX) -c $(CFLAGS) $(INC_DIRS) -Wp,-MD,$(@:%.o=%.d) -o $@ $<

%.o: %.c
	$(CC) -c $(CFLAGS) $(INC_DIRS) -Wp,-MD,$(@:%.o=%.d) -o $@ $<

$(OBJ_NAME): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ_FILES)
	rm -f $(OBJ_NAME)
	rm -f $(OBJ_DEP)
