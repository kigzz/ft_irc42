#ifndef OPERATORENTRY_HPP
# define OPERATORENTRY_HPP

# include <string>

struct OperatorEntry
{
	std::string name;
	std::string host;
	std::string password;

	OperatorEntry();
	OperatorEntry(std::string const& name, std::string const& host, std::string const& password);
	OperatorEntry(OperatorEntry const& rhs);
	OperatorEntry& operator=(OperatorEntry const& rhs);
	~OperatorEntry();
};

#endif
