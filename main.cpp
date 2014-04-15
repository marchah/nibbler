//
// main.cpp for main in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Thu Mar  1 17:58:38 2012 hugo marchadier
// Last update Wed Mar 14 18:34:21 2012 fabien karquel
//

#include <iostream>

#include "SizeExecption.hh"
#include "Ressources/Defines.hh"
#include "Game.hh"
#include "DLLoader.hh"

int	my_getnbr(char *str, std::string const & type)
{
  int	pos = 0;
  int	sign = 1;
  int	nbr = 0;

  while (str[pos] != '\0' && (str[pos] == '+' || str[pos] == '-'))
    {
      if (str[pos] == '-')
	sign = sign * -1;
      pos = pos + 1;
    }
  str = str + pos;
  pos = 0;
  if (sign < 0)
    throw SizeException(type + " negative.");
  while (str[pos] >= '0' && str[pos] <= '9')
    {
      nbr = nbr * 10;
      nbr = nbr + (str[pos] - '0');
      if (sign == 1 && nbr < 0)
	throw SizeException(type + " overflow.");
      pos = pos + 1;
    }
  if (str[pos] != '\0')
    throw SizeException(type + " invalid charactere.");
  if (nbr > Rules::SIZE_MAX)
    throw SizeException(type + " size too big.");
  return (nbr);
}

int	main(int argc, char **argv)
{
  int	width;
  int	height;

  if (argc != 4)
    {
      std::cerr << "Usage: width height lib_nibbler_XXX.so" << std::endl;
      return (-1);
    }
  try
    {
      width = my_getnbr(argv[1], "Width");
      height = my_getnbr(argv[2], "Height");
      if (width < (Sizes::INIT_SNAKE + 1) || height < (Sizes::INIT_SNAKE + 1))
	throw SizeException("Window size too small.");
      try
	{
	  DLLoader<IDisplayModule*> test(argv[3]);
	  Game game(height, width, test.getInstance());
	  game.run();
	}
      catch (const IDisplayModuleException& e)
	{
	  std::cerr << e.getMessage() << std::endl;
	}
      catch (const DLLoaderException& e)
	{
	  std::cerr << e.getMessage() << std::endl;
	}
      catch (const GameException& e)
	{
	  std::cerr << e.getMessage() << std::endl;
	}

    }
  catch (const SizeException& e)
    {
      std::cerr << e.getMessage() << std::endl;
    }
  
}
