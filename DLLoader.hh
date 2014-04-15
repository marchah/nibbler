//
// DLLoader.hh for DLLoader in /home/marcha_j//test/c++/Nibbler/tp/ex5
// 
// Made by hugo marchadier
// Login   <marcha_j@epitech.net>
// 
// Started on  Tue Mar  6 16:52:45 2012 hugo marchadier
// Last update Thu Mar  8 15:42:58 2012 hugo marchadier
//

#ifndef DLLOADER_H_
#define DLLOADER_H_

#include <string>

#include <dlfcn.h>

class DLLoaderException : public std::exception
{
  std::string   _message;

public:
  DLLoaderException(std::string const &msg) : _message(msg) {}
  ~DLLoaderException() throw() {}
  std::string const &   getMessage() const throw()
  {
    return (this->_message);
  }
};

template <typename T>
class DLLoader
{
  T	_obj;
  void	*_lib;

  DLLoader(const DLLoader&);
  DLLoader& operator=(const DLLoader&);

public:
  DLLoader(char const * const name)
  {
    T	(*fct)();
    const char *error;
    std::string name_lib = name;

      if ((name[0] >= 'A' && name[0] <= 'Z')
	  || (name[0] >= 'a' && name[0] <= 'z'))
	name_lib = "./" + name_lib;
      if ((this->_lib = dlopen(name_lib.c_str(), RTLD_NOW)) == NULL)
      throw DLLoaderException("Error: dlopen failed.");
    fct = reinterpret_cast<T (*)()> (dlsym(this->_lib, "make"));
    if ((error = dlerror()) != NULL)
      throw DLLoaderException(error);
    this->_obj = fct();
  }

  ~DLLoader()
  {
    dlclose(this->_lib);
  }

  T getInstance() const
  {
    return (this->_obj);
  }
};

#endif // DLLOADER_H_
