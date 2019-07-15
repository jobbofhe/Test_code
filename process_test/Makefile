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
DEFINES       = -DALL_CODER_TRANS
CFLAGS        += -g -O3 -std=gnu99 -std=c++11 -Wno-pointer-sign $(DEFINES)
LFLAGS        = $(MARCH)

LIBS          = -L/usr/local/lib64  -L/usr/lib
                  
#-lpaho-mqtt3c-lavformat  -lsc_midware
# Target
TARGET        = process_test
 
SYMBOL = process_test

# Header file path
INCDIR = .
INCDIR += /usr/local/include
INCPATH = $(addprefix -I, $(INCDIR))

# Source file path
VPATH = .
SRC_PATH = $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cc)) 

# Output dir and files 
OBJ_DIR = ./objs
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .cc,.o, $(SRC_PATH))) 

OBJ_PATH = $(addprefix  $(OBJ_DIR)/,$(VPATH)) 

MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR) $(OBJ_PATH)) 

$(warning  $(SRC_PATH))
$(warning  $(DEPS))

first: all

# ------------------------------------------------------------------------------------------
# Obj dependence
DEPS = $(OBJS:.o=.d)
include $(DEPS)
$(OBJ_DIR)/%.d : %.cpp
	$(CXX) -std=c++11 -MM $(INCPATH) $< > $@

# Compile rules
$(OBJ_DIR)/%.o : %.cpp
	$(CXX)   -o $@ -c $< $(INCPATH) $(CFLAGS)

#$(warning  $(DEPS))
#$(warning  $(OBJS))

#------------------------------------------------------------------------------------------



####### Build rules
$(TARGET):  $(OBJS)
	-$(DEL_FILE) $(TARGET)
	#$(CXX)  -g -fPIC -shared -o $(TARGET) $(OBJS) $(LIBS)
	@echo -----------------------------------Build Complete-----------------------------------
	$(CXX)  -g -fPIC -o $(SYMBOL) $(OBJS) $(LIBS)



all: $(TARGET)

clean:
	-$(DEL_R) $(OBJ_DIR)

distclean:
	-$(DEL_R) $(OBJ_DIR)
	-$(DEL_FILE) $(TARGET)

# ------------------------------------------------------------------------------------------
# Install
INSTALL_PATH = /usr/local/lib64/showclear
install: $(TARGET)
	@test -d $(INSTALL_PATH) || mkdir -p $(INSTALL_PATH)
	-$(INSTALL_PROGRAM) $(TARGET) $(INSTALL_PATH)/$(TARGET)

uninstall:
	-$(DEL_FILE) $(INSTALL_PATH)/$(TARGET)

FORCE:







