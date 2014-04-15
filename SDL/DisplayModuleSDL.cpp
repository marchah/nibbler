//
// displaymode.cpp for  in /home/l-huil_o//test/nibbler/sdl
// 
// Made by olivier l-huillier
// Login   <l-huil_o@epitech.net>
// 
// Started on  Mon Mar  5 17:55:31 2012 olivier l-huillier
// Last update Wed Mar 14 18:22:00 2012 fabien karquel
//

#include <iostream>
#include <sstream>
#include "DisplayModuleSDL.hh"
#include "../Ressources/Defines.hh"
#include "../Ressources/Coord.hh"

DisplayModuleSDL::DisplayModuleSDL()
{
}

DisplayModuleSDL::~DisplayModuleSDL()
{
  this->stop();
}

void DisplayModuleSDL::initWindow(int const width, int const height)
{
  this->_width = width;
  this->_height = height;
  if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
    throw IDisplayModuleException("Error: SDL_Init failed.");
  SDL_WM_SetCaption("Nibbler", NULL);
  this->_screen = SDL_SetVideoMode(width * Sizes::CASE, (height + 2) * Sizes::CASE, 32, SDL_HWSURFACE);
}

void DisplayModuleSDL::initGame()
{
  this->_snakeHead = SDL_CreateRGBSurface(SDL_HWSURFACE, Sizes::CASE, Sizes::CASE, 32, 0, 0, 0, 0);
  this->_snakeBody = SDL_CreateRGBSurface(SDL_HWSURFACE, Sizes::CASE, Sizes::CASE, 32, 0, 0, 0, 0);
  this->_eat = SDL_CreateRGBSurface(SDL_HWSURFACE, Sizes::CASE, Sizes::CASE, 32, 0, 0, 0, 0);
  SDL_FillRect(this->_snakeHead, NULL, SDL_MapRGB(this->_snakeHead->format, 255, 128, 0));
  SDL_FillRect(this->_snakeBody, NULL, SDL_MapRGB(this->_snakeBody->format, 128, 255, 0));
  SDL_FillRect(this->_eat, NULL, SDL_MapRGB(this->_eat->format, 255, 0, 0));
}

void DisplayModuleSDL::initScore()
{
  this->_font = TTF_OpenFont("./Ressources/font.ttf", Sizes::CASE * 2);
  if (this->_font == NULL)
    {
      this->stop();
      throw IDisplayModuleException("Error: TTF_OpenFont failed.");
    }
  this->_textColor.r = 255;
  this->_textColor.g = 255;
  this->_textColor.b = 255;
}

void DisplayModuleSDL::init(int const width, int const height)
{
  this->initWindow(width, height);
  this->initGame();
  this->initScore();
}

void DisplayModuleSDL::stop()
{
  SDL_FreeSurface(this->_snakeHead);
  SDL_FreeSurface(this->_snakeBody);
  TTF_CloseFont(this->_font);
  TTF_Quit();
  SDL_Quit();
}

void DisplayModuleSDL::drawSnake(const std::list<Coord>& snake)
{
  SDL_Rect	position;

  for (std::list<Coord>::const_iterator it = snake.begin();
       it != snake.end(); ++it)
    {
      position.x = (*it)._x * Sizes::CASE;
      position.y = (*it)._y * Sizes::CASE;
      if (it == snake.begin())
	SDL_BlitSurface(this->_snakeHead, NULL, this->_screen, &position);
      else
	SDL_BlitSurface(this->_snakeBody, NULL, this->_screen, &position);
    }
}

void DisplayModuleSDL::drawEat(const Coord& eat)
{
  SDL_Rect position;

  position.x = eat._x * Sizes::CASE;
  position.y = eat._y * Sizes::CASE;
  SDL_BlitSurface(this->_eat, NULL, this->_screen, &position);
}

void DisplayModuleSDL::drawScore(const int score)
{
  SDL_Surface*		back;
  SDL_Rect		position;
  SDL_Surface*		text;
  std::stringstream	ss;
  
  position.x = 0;
  position.y = this->_height * Sizes::CASE;
  ss << "Score: " << score;
  text = TTF_RenderText_Blended(this->_font, ss.str().c_str(), this->_textColor);
  back = SDL_CreateRGBSurface(SDL_HWSURFACE, this->_width * Sizes::CASE, Sizes::CASE * 2, 32, 0, 0, 0, 0);
  SDL_FillRect(back, NULL, SDL_MapRGB(back->format, 0, 0, 0));
  SDL_BlitSurface(back, NULL, this->_screen, &position);
  position.y += 2;
  SDL_BlitSurface(text, NULL, this->_screen, &position);
  SDL_FreeSurface(back);
  SDL_FreeSurface(text);
}

void DisplayModuleSDL::draw(const std::list<Coord>& snake, const Coord& eat, int const score)
{
  SDL_FillRect(this->_screen, NULL, SDL_MapRGB(this->_screen->format, 42, 42, 42));
  this->drawSnake(snake);
  this->drawEat(eat);
  this->drawScore(score);
  SDL_Flip(this->_screen);
}

Dir DisplayModuleSDL::getEvent()
{
  SDL_Event	event;
  int		key;

  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT)
    return QUIT;
  if (event.type == SDL_KEYDOWN)
    {
      key = event.key.keysym.sym;
      switch (key)
	{
	case SDLK_LEFT:
	  return LEFT;
	case SDLK_RIGHT:
	  return RIGHT;
	case SDLK_UP:
	  return UP;
	case SDLK_DOWN:
	  return DOWN;
	case SDLK_ESCAPE:
	  return QUIT;
	case SDLK_SPACE:
	  return SPACE;
	default:
	  return NONE;
	}
    }
  return NONE;
}

extern "C" IDisplayModule*	make()
{
  return (new DisplayModuleSDL());
}
