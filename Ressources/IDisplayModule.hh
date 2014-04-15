//
// IDisplayModule.hh for IDisplayModule.hh in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Mon Mar  5 18:29:52 2012 hugo marchadier
// Last update Wed Mar  7 16:19:40 2012 hugo marchadier
//

#ifndef	IDISPLAYMODULE_HH_
#define IDISPLAYMODULE_HH_

#include <string>

#include "Defines.hh"
#include "Coord.hh"

class IDisplayModuleException : public std::exception
{
  std::string   _message;

public:
  IDisplayModuleException(std::string const &msg) : _message(msg) {}
  ~IDisplayModuleException() throw() {}
  std::string const &   getMessage() const throw()
  {
    return (this->_message);
  }
};

class IDisplayModule
{
public:
  virtual ~IDisplayModule() {}
  virtual void	init(int const, int const) = 0;
  virtual void	stop() = 0;
  virtual Dir	getEvent() = 0;
  virtual void	draw(std::list<Coord> const& snake, const Coord &, int const) = 0;
};

#endif // IDISPLAYMODULE_HH_
