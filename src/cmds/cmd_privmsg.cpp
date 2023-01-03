#include "Client.hpp"
#include "command.h"

void cmd_privmsg(CommandContext& ctx)
{
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;
	CommandContext::ArgumentList recips;
	CommandContext::ArgumentList::const_iterator recipIt;
	Recipient* recipient;

	if (args.size() < 2)
	{
		client.reply<ERR_NEEDMOREPARAMS>(ctx.name);
		return;
	}

	recips = CommandContext::splitList(args[0]);
	for (recipIt = recips.begin(); recipIt != recips.end(); ++recipIt)
	{
		recipient = ctx.server.getRecipient(*recipIt);
		if (recipient == NULL)
			client.reply<ERR_NOSUCHNICK>(*recipIt);
		else
			recipient->sendMessage(client, ctx.name, args[1]);
	}
}
