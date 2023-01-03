#include "Client.hpp"
#include "CommandMap.hpp"
#include <fstream>

void cmd_motd(CommandContext& ctx)
{
	ctx.server.sendMotd(ctx.client);
}
