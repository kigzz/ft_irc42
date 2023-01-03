#include "OperatorEntry.hpp"

OperatorEntry::OperatorEntry() :
	name(),
	host(),
	password()
{}

OperatorEntry::OperatorEntry(std::string const& name, std::string const& host, std::string const& password) :
	name(name),
	host(host),
	password(password)
{}

OperatorEntry::OperatorEntry(OperatorEntry const& rhs) :
	name(rhs.name),
	host(rhs.host),
	password(rhs.password)
{}

OperatorEntry& OperatorEntry::operator=(OperatorEntry const& rhs)
{
	this->name = rhs.name;
	this->host = rhs.host;
	this->password = rhs.password;
	return *this;
}

OperatorEntry::~OperatorEntry()
{}
