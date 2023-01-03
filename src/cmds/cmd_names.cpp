#include "Client.hpp"
#include "command.h"
#include "utils/NameUtils.hpp"

using NameUtils::Request;
using NameUtils::RequestList;

void cmd_names(CommandContext& ctx)
{
	Server& server = ctx.server;
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
		NameUtils::showAllNames(client);
	else
	{
		CommandContext::ArgumentList chanNames = CommandContext::splitList(args[0]);
		CommandContext::ArgumentList::iterator nameIt = chanNames.begin();
		ChannelManager::iterator chanIt;
		RequestList requests;
		Request req;

		for (; nameIt != chanNames.end(); ++nameIt)
		{
			chanIt = server.channelManager.getChannel(*nameIt);
			req.name = *nameIt;
			if (chanIt == server.channelManager.end())
				req.channel = NULL;
			else
				req.channel = &*chanIt;
			requests.push_back(req);
		}

		NameUtils::showNames(client, requests);
	}

}
