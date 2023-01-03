#ifndef NAMEUTILS_HPP
# define NAMEUTILS_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <vector>

namespace NameUtils
{
struct Request
{
	std::string name;
	Channel* channel;
};

typedef std::vector< Request > RequestList;

void showAllNames(Client& client);
void showNames(Client& client, RequestList& requests);
void showName(Client& client, Request& request);
}

#endif // NAMEUTILS_HPP
