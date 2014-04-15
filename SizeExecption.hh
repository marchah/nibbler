//
// SizeExecption.hh for SizeExecption in /home/marcha_j//test/c++/Nibbler/proj
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Thu Mar  1 18:09:15 2012 hugo marchadier
// Last update Wed Mar  7 18:01:42 2012 hugo marchadier
//

#ifndef	SIZEEXECPTION_HH__
#define SIZEEXECPTION_HH__

class SizeException : public std::exception
{
  std::string   _message;

public:
  SizeException(std::string const &msg) : _message(msg) {}
  ~SizeException() throw() {}
  std::string const &   getMessage() const throw()
  {
    return (this->_message);
  }
};

#endif // SIZEEXECPTION_HH__
