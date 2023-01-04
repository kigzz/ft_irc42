#include "Client.hpp"
#include "Channel.hpp"
#include "CommandMap.hpp"
#include <set>

void cmd_quit(CommandContext& ctx)
{
	CommandContext::ArgumentList& args = ctx.args;
	Client& client = ctx.client;
	Server& server = ctx.server;
	std::string const prefix = client.asPrefix();
	Client::ChannelList::iterator chanIt;
	Channel::ClientList::iterator clientIt;
	std::set< Client* > recipients;
	std::set< Client* >::iterator recipIt;
	std::string reason;

	if (!args.empty())
		reason = args[0];

	for (chanIt = client.channels.begin(); chanIt != client.channels.end(); ++chanIt)
	{
		(*chanIt)->removeClient(client);
		if ((*chanIt)->empty())
			server.channelManager.removeChannel((*chanIt)->name);
		else
			for (clientIt = (*chanIt)->allClients.begin(); clientIt != (*chanIt)->allClients.end(); ++clientIt)
				recipients.insert(clientIt->client);
	}
	for (recipIt = recipients.begin(); recipIt != recipients.end(); ++recipIt)
		(*recipIt)->send(prefix + " QUIT :Quit: " + reason);
	client.send("ERROR :See you next time!");
	client.shouldClose = true;
	client.hasQuit = true;
}
