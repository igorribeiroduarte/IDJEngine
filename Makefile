NAME = Game

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/$(NAME)

CC = g++
CFLAGS = -pedantic -std=c++11 -MMD -g3 -g -fPIC\
		 -W -Wall -Wextra -Wshadow -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
		 -Wdisabled-optimization -Wformat=2 -Wlogical-op -Wmissing-declarations\
		 -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls\
		 -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef\
		 -Wzero-as-null-pointer-constant -Wuseless-cast -Wnon-virtual-dtor
INCLUDES = -Iinclude `sdl2-config --cflags`
LIBS =  `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}

RMDIR = rm -rf

#--------------------------------------------------------------
ifeq ($(OS), Windows_NT)

RMDIR = rd /s /q

SDL_PATH = c:\SDL2-2.0.5\x86_64-w64-mingw32

INCLUDES += -I $(SDL_PATH)\include

LIBS = -L $(SDL_PATH)\lib -lmingw32 -lSDL2main
	   -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

NAME = $(NAME).exe
#--------------------------------------------------------------
else

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer 
	   -framework SDL_TTF
	
#-------------------------------------------------------------

endif
endif

.PHONY: clean depend dist-clean dist

all:
#-------------------------------------------------------------
ifeq ($(OS), Windows_NT)
	@if not exist $(OBJ_DIR) @mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) @mkdir $(BIN_DIR)
else
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)
	$(MAKE) $(TARGET)
endif
#-------------------------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	@echo Building $@
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $@ $(LIBS)
	@echo Done.

run:
	$(TARGET)

reset:
	make dist-clean
	make -j

crun:
	make dist-clean
	make -j
	make run

clean:
	@echo Cleaning...
	@find . -name *.o -exec rm {} \;
	@find . -name *.d -exec rm {} \;
	@$(RMDIR) *~ *.o prog out.txt

dist-clean: clean
	@$(RMDIR) $(TARGET)/$(NAME)
	@$(RMDIR) *.tar.gz $(OBJ_DIR) $(BIN_DIR)
