####### Compiler, tools and options
CC            = gcc
CXX           = g++
MARCH         = -m64
CFLAGS        = $(MARCH) -pipe -Wall -W -fPIC
CXXFLAGS      = $(MARCH) -pipe -Wall -W -fPIC
DEL_FILE      = rm -f
DEL_R         = rm -rf
MKDIR         = mkdir -p
DEL_DIR       = rmdir
MOVE          = mv -f
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
SYMLINK       = ln -f -s
TAR           = tar -cf
COMPRESS      = gzip -9f
LINK          = gcc
AR            = ar cqs
SED           = sed
STRIP         = strip

# Program specifical options
DEFINES 	  += -DFACE_RECOGNITION 
DEFINES 	  += -DPEOPLE_NUMBER_DETECT 
DEFINES 	  += -DPLAY_PHONE_DETECT 
DEFINES 	  += -DHELMET_DETECT 
DEFINES 	  += -DSLEEP_DETECT

CFLAGS        += -g -O3  $(DEFINES)

LFLAGS        = $(MARCH)
LIBS          =  -L/usr/local/cuda/lib64 -lcuda -lcudart -lcublas -lcurand

# Target
TARGET        = test


# Header file path
INCDIR = .
INCDIR += ./include
INCDIR += /usr/local/cuda/include/


INCDIR += /usr/lib/include
INCPATH = $(addprefix -I, $(INCDIR))

# Source file path
VPATH = .
SRC_PATH = $(foreach dir,$(VPATH),$(wildcard $(dir)/*.c))

# Output dir and files
OBJ_DIR = .
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .c,.o, $(SRC_PATH)))

OBJ_PATH = $(addprefix  $(OBJ_DIR)/,$(VPATH))
MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR) $(OBJ_PATH))


first: all

# Obj dependence
DEPS = $(OBJS:.o=.d)
include $(DEPS)
$(OBJ_DIR)/%.d : %.c
	$(CC) -MM $(INCPATH) $< > $@

# Compile rules
$(OBJ_DIR)/%.o : %.c
	$(CC) -o $@ -c $< $(INCPATH) $(CFLAGS)

####### Build rules
$(TARGET):  $(OBJS)
	-$(DEL_FILE) $(TARGET)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	-$(DEL_R) $(OBJ_DIR)
	rm -rf ./*.o 
	rm -rf ./*.o 
	rm -rf ./objs

distclean:
	-$(DEL_R) $(OBJ_DIR)
	-$(DEL_FILE) $(TARGET)


