#include "class/ClientManager.hpp"
#include "Client.hpp"

ClientManager::ClientManager()
{}

ClientManager::~ClientManager()
{}

ClientManager::iterator ClientManager::getClient(int sockFd)
{
	return this->_clients.find(sockFd);
}

void ClientManager::addClient(Client const& client)
{
	this->_clients[client.sock_fd] = client;
}

void ClientManager::removeClient(iterator it)
{
	this->_clients.erase(it);
}

ClientManager::iterator ClientManager::begin()
{
	return this->_clients.begin();
}

ClientManager::iterator ClientManager::end()
{
	return this->_clients.end();
}

void ClientManager::clear()
{
	this->_clients.clear();
}
