#pragma once

#include <map>
#include <string>

class Client;

class ClientManager
{
public:
	typedef std::map< int, Client > container_type;
	typedef container_type::iterator iterator;

private:
	container_type _clients;

public:
	ClientManager();
	~ClientManager();

public:
	iterator getClient(int sockFd);
	iterator getClient(std::string const& nickname);

	void addClient(Client const& client);
	void removeClient(iterator it);

	void clear();

	iterator begin();
	iterator end();
};
