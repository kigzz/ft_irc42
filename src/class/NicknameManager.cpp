#include "class/NicknameManager.hpp"

NicknameManager::NicknameManager() :
	_nicknames()
{
}

NicknameManager::~NicknameManager()
{
}

bool NicknameManager::registerNickname(std::string const& nickname, Client* client)
{
	return this->_nicknames.insert(std::make_pair(nickname, client)).second;
}

bool NicknameManager::unregisterNickname(std::string const& nickname)
{
	return this->_nicknames.erase(nickname) > 0;
}

bool NicknameManager::hasNickname(std::string const& nickname)
{
	return this->_nicknames.find(nickname) != this->_nicknames.end();
}

NicknameManager::iterator NicknameManager::getClient(std::string const& nickname)
{
	return this->_nicknames.find(nickname);
}

NicknameManager::iterator NicknameManager::begin()
{
	return this->_nicknames.begin();
}

NicknameManager::iterator NicknameManager::end()
{
	return this->_nicknames.end();
}

void NicknameManager::clear()
{
	this->_nicknames.clear();
}
