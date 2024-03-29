#include "Client.hpp"
#include "CommandMap.hpp"
#include "command.h"
#include <algorithm>

CommandContext::CommandContext(Client& client, std::string const& name, std::string const& line) :
	client(client),
	server(*client.server),
	name(name),
	args(CommandContext::split(line))
{}

CommandContext::~CommandContext()
{}

CommandContext::ArgumentList CommandContext::split(std::string const& line)
{
	return CommandContext::__split(line, ' ', true);
}

CommandContext::ArgumentList CommandContext::splitList(std::string const& line)
{
	return CommandContext::__split(line, ',', false);
}

CommandContext::ArgumentList CommandContext::__split(std::string const& line, char separator, bool colon)
{
	ArgumentList args;
	std::string::const_iterator it = line.begin();
	std::string::const_iterator fast;

	while (it != line.end())
	{
		if (colon && *it == ':')
		{
			++it;
			fast = line.end();
		}
		else
		{
			fast = std::find(it, line.end(), separator);
		}

		args.push_back(std::string(it, fast));
		it = fast;

		if (it != line.end())
			++it;
	}
	return args;
}
