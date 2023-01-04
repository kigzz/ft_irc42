#pragma once

#include <stdexcept>
#include <string>

class IOException : public std::exception
{
private:
	std::string _reason;

public:
	IOException(std::string const& syscallName, int errnum);
	~IOException() throw();

public:
	char const* what() const throw();
};
