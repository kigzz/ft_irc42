#include "Channel.hpp"
#include <iostream>

Channel::Channel(Server* server) : Recipient(server),
	name(),
	topic(),
	passwd(),
	modes("+"),
	inviteMode(false),
	keyMode(false),
	usrLimitMode(false),
	userLimit(0),
	allClients(),
	invitedClients()
{}

Channel::Channel(Server* server, std::string name, std::string passwd) : Recipient(server),
	name(name),
	topic(),
	passwd(passwd),
	modes("+"),
	inviteMode(false),
	keyMode(false),
	usrLimitMode(false),
	userLimit(0),
	allClients(),
	invitedClients()
{}

Channel::Channel(Channel const& rhs) : Recipient(rhs.server),
	name(rhs.name),
	topic(rhs.topic),
	passwd(rhs.passwd),
	modes(rhs.modes),
	inviteMode(rhs.inviteMode),
	keyMode(rhs.keyMode),
	usrLimitMode(rhs.usrLimitMode),
	userLimit(rhs.userLimit),
	allClients(rhs.allClients)
{}

Channel	&Channel::operator=(Channel const& rhs) {

	if (this != &rhs) {
		this->server = rhs.server;
		const_cast<std::string&>(this->name) = rhs.name;
		this->topic = rhs.topic;
		this->passwd = rhs.passwd;
		this->modes = rhs.modes;
		this->inviteMode = rhs.inviteMode;
		this->keyMode = rhs.keyMode;
		this->usrLimitMode = rhs.usrLimitMode;
		this->userLimit = rhs.userLimit;
		this->allClients = rhs.allClients;
		this->invitedClients = rhs.invitedClients;
	}
	return (*this);
}

Channel::~Channel() {}

bool Channel::empty() const
{
	return this->allClients.empty();
}

void Channel::addChanModes(std::string newModes) {

	std::string allowedModes = "ikl";

	for (uint i = 0; i < newModes.length(); i++) {
		char c = newModes[i];
		if (this->modes.find(c) == std::string::npos && allowedModes.find(c) != std::string::npos)
			this->modes += c;
	}
}

void Channel::removeChanModes(std::string byeModes) {

	std::string allowedModes = "ikl";

	for (uint i = 0; i < byeModes.length(); i++) {
		char c = byeModes[i];
		if (this->modes.find(c) == std::string::npos && allowedModes.find(c) != std::string::npos) {
			this->modes.erase(c, 1);
		}
	}
}

void	Channel::addClient(Client &client, ChannelPrivilege privilege) {
	ClientPrivilege const entry = {&client, privilege};

	this->allClients.push_back(entry);
}

void Channel::removeClient(Client &client) {
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
		{
			this->allClients.erase(it);
			return;
		}
}

bool Channel::hasClient(Client &client) const {
	ClientList::const_iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
			return true;
	return false;
}

Channel::ClientList::iterator Channel::getClient(Client& client)
{
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
		if (it->client == &client)
			break;
	return it;
}

void	Channel::inviteClient(Client& client) {

	this->invitedClients.insert(&client);
}

bool	Channel::isInvited(Client& client) {

	return (this->invitedClients.find(&client) != this->invitedClients.end());
}

void	Channel::uninviteClient(Client& client) {

	this->invitedClients.erase(&client);
}

int		Channel::getClientPriv(Client &client) {

	int						priv = PRIV_NONE;
	ClientList::iterator 	itCli = this->allClients.begin();

	for (; itCli != this->allClients.end(); ++itCli)
		if (itCli->client == &client)
			priv = itCli->privilege;
	return (priv);
}

void	Channel::setPriv(std::string const &nick, ChannelPrivilege priv) {

	ClientList::iterator	itCli = this->allClients.begin();

	for (; itCli != this->allClients.end(); ++itCli)
		if (itCli->client->nickname == nick)
		{
			itCli->privilege = priv;
			break;
		}
}

std::string const& Channel::getIdentifier() const
{
	return this->name;
}

void Channel::sendMessage(Client& sender, std::string const& command, std::string const& message)
{
	std::string const& prefix = sender.asPrefix();
	ClientList::iterator it;

	for (it = this->allClients.begin(); it != this->allClients.end(); ++it)
	{
		if (it->client != &sender)
			it->client->send(prefix + " " + command + " " + this->name + " :" + message);
	}
}
