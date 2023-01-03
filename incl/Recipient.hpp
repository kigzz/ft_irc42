#ifndef RECIPIENT_HPP
# define RECIPIENT_HPP

# include <string>

class Server;
class Client;

class Recipient
{
public:
	Server* server;

	Recipient(Server* server);
	virtual ~Recipient();

public:
	virtual std::string const& getIdentifier() const = 0;
	virtual void sendMessage(Client& sender, std::string const& command, std::string const& message) = 0;
}; // class Recipient

#endif // RECIPIENT_HPP
