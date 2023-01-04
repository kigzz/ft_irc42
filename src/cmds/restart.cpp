#include "ft_irc.h"
#include "command.h"
#include "Client.hpp"

void cmd_restart(CommandContext& ctx)
{
	Client& client = ctx.client;

	if (!client.checkState(CLIENT_STATE_OPERATOR))
		client.reply<ERR_NOPRIVILEGES>();
	else {
		g_Mode = 2;
	}
}
