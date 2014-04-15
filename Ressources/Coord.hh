//
// Coord.hh for Coord in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Mon Mar  5 18:35:11 2012 hugo marchadier
// Last update Mon Mar  5 19:21:55 2012 hugo marchadier
//

#ifndef	COORD_HH_
#define COORD_HH_

struct	Coord
{
  int	_y;
  int	_x;

  Coord()
    : _y(0), _x(0) {}

  Coord(int y, int x)
    : _y(y), _x(x) {}

  bool	operator==(const Coord &c)
  {
    if (this->_x == c._x && this->_y == c._y)
      return (true);
    return (false);
  }
};

#endif // COORD_HH_
