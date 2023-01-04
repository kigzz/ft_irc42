#ifndef COMMANDMAP_HPP
# define COMMANDMAP_HPP

# include "command.h"
# include "ClientState.hpp"

# include <map>
# include <string>

class Client;
class Server;

class CommandMap
{
public:
	typedef void (*Handler)(::CommandContext& ctx);
	typedef std::pair< Handler, ClientState > HandlerPair;
	typedef std::map< std::string, HandlerPair > MapType;

private:
	MapType _commands;
	Server& server;

public:
	CommandMap(Server& server);
	~CommandMap();

public:
	void put(std::string const& name, Handler handler, ClientState requiredFlags = CLIENT_STATE_INIT);
	void process(Client& client, std::string const& line);
	void dispatch(Client& client, std::string const& prefix, std::string const& name, std::string const& line);

public:
	void handleUnknownCommand(Client& client, std::string const& name);
};

#endif
