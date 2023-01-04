#include "ft_irc.h"
#include "command.h"
#include "Client.hpp"

void cmd_die(CommandContext& ctx)
{
	Client& client = ctx.client;

	if (client.checkState(CLIENT_STATE_OPERATOR)) {
		g_Mode = 0;
	}
	else
		client.reply<ERR_NOPRIVILEGES>();
}
