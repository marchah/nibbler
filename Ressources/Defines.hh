//
// Defines.hh for Define.hh in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Mon Mar  5 16:28:23 2012 hugo marchadier
// Last update Wed Mar 14 18:44:02 2012 fabien karquel
//

#ifndef	DEFINES_HH_
#define DEFINES_HH_

namespace Sizes
{
  const int CASE = 16;
  const int INIT_SNAKE = 4;
}

namespace Rules
{
  const int POINT = 1;
  const int TIME = 150000;
  const int SIZE_MAX = 60;
  const int SPEED_INIT = 1;
  const int SPEED_MAX = 3;
}

enum	Dir
  {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
    QUIT,
    SPACE,
    NONE
  };

#endif // DEFINES_HH_
