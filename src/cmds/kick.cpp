#include "Client.hpp"
#include "command.h"

#define DEFAULT_REASON "Smell ya later"

void cmd_kick(CommandContext& ctx)
{
	Server& server = ctx.server;
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.size() < 2)
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}

	ChannelManager::iterator chanIt = server.channelManager.getChannel(args[0]);

	if (chanIt == server.channelManager.end())
	{
		client.reply<ERR_NOSUCHCHANNEL>(ctx.name);
		return;
	}

	Channel::ClientList::iterator cliPrivIt = chanIt->getClient(client);

	if (cliPrivIt == chanIt->allClients.end())
	{
		client.reply<ERR_NOTONCHANNEL>(chanIt->name);
		return;
	}

	if (cliPrivIt->privilege < PRIV_CHANOP)
	{
		client.reply<ERR_CHANOPRIVSNEEDED>(chanIt->name);
		return;
	}

	std::string const prefix = client.asPrefix();
	std::string const reason = (args.size() >= 3) ? args[2] : DEFAULT_REASON;
	CommandContext::ArgumentList names = CommandContext::splitList(args[1]);
	CommandContext::ArgumentList::iterator nameIt = names.begin();
	NicknameManager::iterator clientIt;
	Channel::ClientList::iterator clientMemberIt;

	for (; nameIt != names.end(); ++nameIt)
	{
		clientIt = server.nickManager.getClient(*nameIt);

		if (clientIt != server.nickManager.end())
		{
			cliPrivIt = chanIt->getClient(*clientIt->second);

			if (cliPrivIt != chanIt->allClients.end())
			{
				clientMemberIt = chanIt->allClients.begin();

				for (; clientMemberIt != chanIt->allClients.end(); ++clientMemberIt)
					clientMemberIt->client->send(prefix + " KICK " + chanIt->name + " " + clientIt->second->nickname + " :" + reason);
				chanIt->removeClient(*cliPrivIt->client);
				continue;
			}
		}
		client.reply<ERR_USERNOTINCHANNEL>(*nameIt, chanIt->name);
	}

	if (chanIt->empty())
		server.channelManager.removeChannel(chanIt);
}
