##
## Makefile for Makefile in /home/marcha_j//afs/test/unix/mysh
## 
## Made by hugo marchadier
## Login   <marcha_j@epitech.net>
## 
## Started on  Tue Dec 28 10:55:56 2010 hugo marchadier
## Last update Wed Mar 14 17:43:45 2012 fabien karquel
##

NAME=	nibbler

SRC=	main.cpp \
	Game.cpp \




NAME_NCURSES=		ncurses

NAME_NCURSES_LIB=	lib_nibbler_Ncurses.so

NAME_SDL=		sdl

NAME_SDL_LIB=	lib_nibbler_SDL.so

NAME_OPENGL=		opengl

NAME_OPENGL_LIB=	lib_nibbler_OpenGl.so


CXX=	g++

CXXFLAGS=	-Wextra -Wall -Werror

OBJ=	$(SRC:.cpp=.o)

all:	$(NAME) $(NAME_NCURSES) $(NAME_SDL) $(NAME_OPENGL)

$(NAME_NCURSES):
	$(CXX) -c -fPIC Ncurses/DisplayModuleNcurses.cpp
	$(CXX) -shared -o $(NAME_NCURSES_LIB) DisplayModuleNcurses.o

$(NAME_SDL):
	$(CXX) -c -fPIC SDL/DisplayModuleSDL.cpp
	$(CXX) -shared -o $(NAME_SDL_LIB) DisplayModuleSDL.o

$(NAME_OPENGL):
	$(CXX) -c -fPIC OpenGL/DisplayModuleOpenGL.cpp
	$(CXX) -shared -o $(NAME_OPENGL_LIB) DisplayModuleOpenGL.o


$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -ldl -lncurses -lSDL -lSDL_ttf -lGLU -lGL
clean:
	rm -f $(OBJ) DisplayModuleNcurses.o DisplayModuleSDL.o DisplayModuleOpenGL.o 

fclean:	clean
	rm -f $(NAME) $(NAME_NCURSES_LIB) $(NAME_SDL_LIB) $(NAME_OPENGL_LIB)

re:	fclean all

.PHONY: all clean fclean re