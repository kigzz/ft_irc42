#include "class/exception/IOException.hpp"
#include <cstring>

IOException::IOException(std::string const& syscallName, int errnum) :
	_reason(syscallName + ": " + std::strerror(errnum))
{}

IOException::~IOException() throw()
{}

char const* IOException::what() const throw()
{
	return this->_reason.c_str();
}
