#include "Client.hpp"
#include "command.h"

void cmd_ping(CommandContext& ctx)
{
	Client& client = ctx.client;
	CommandContext::ArgumentList& args = ctx.args;

	if (args.empty())
	{
		client.reply<ERR_NOORIGIN>();
		return;
	}

	client.send("PONG :" + args[0]);
}
