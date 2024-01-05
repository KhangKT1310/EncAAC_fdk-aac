VERSION=1.0.0
# linux
TOOLS_DIR	=
NAME_LIB	= libaac.a
OPTIMIZE	= -Wall -O2
PROJECT_DIR = $(PWD)
-include $(PROJECT_DIR)/Makefile.sdk.conf


OBJ_DIR=$(PROJECT_DIR)/_build
OBJ = $(OBJ_DIR)/aac.o


CC = $(CROSSCOMPILE)gcc
CXX = $(CROSSCOMPILE)g++
AR	  =$(CROSSCOMPILE)ar
STRIP =$(CROSSCOMPILE)strip

#enviroment
CFLAGS  +=  -I$(SDK_LIB)/include
CFLAGS	+= -L$(SDK_LIB)/lib

#flag
CFLAGS += $(OPTIMIZE)
CFLAGS +=$(FLAG_HAVE)


lib: create $(OBJ_DIR)/$(NAME_LIB)

create:
	@mkdir -p $(OBJ_DIR)


clean:
	rm -rf $(OBJ_DIR)

install:
	sudo cp -r $(OBJ_DIR)/$(NAME_LIB) $(INSTALL_DIR)



$(OBJ_DIR)/$(NAME_LIB): $(OBJ) 
	@echo $(GREEN) "--Compiling '${STATIC_LIB} build release'..." $(NONE)
	@$(AR) rcs $(OBJ_DIR)/$(NAME_LIB) ${OBJ}

$(OBJ_DIR)/%.o: %.cpp
	@echo  $(GREEN) $(CPP) $< $(NONE)
	@$(CPP) -o $@ -c $< $(CFLAGS)

$(OBJ_DIR)/%.o: %.c aac.h
	@echo $(GREEN)$(CPP)  $< $(NONE)
	@$(CC) -o $@ -c $< $(CFLAGS)

