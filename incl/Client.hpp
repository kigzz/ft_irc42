#pragma once

#include "Server.hpp"
#include "Channel.hpp"
#include "Reply.hpp"
#include "ClientState.hpp"
#include "Recipient.hpp"
#include "Logger.hpp"

#include <ctime>
#include <string>
#include <netinet/in.h>
#include <set>

class Channel;
class Server;
class Recipient;
class Logger;

class Client : public Recipient {

	public:
		Client(Server* server = NULL);
		Client(Server* server, int fd, sockaddr_in& addr);
		Client(Client const &src);
		~Client();

		Client &operator=(Client const& src);

		typedef std::set<Channel*> ChannelList;

		void					send(std::string const& command);
		template< Reply reply >
		void 					reply();
		template< Reply reply >
		void 					reply(std::string const& param);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2);
		template< Reply reply >
		void 					reply(std::string const& param1, std::string const& param2, std::string const& param3);
		bool					readFrom();
		void					flushWriteBuffer();
		void					tryLogin();
		void 					closeConnection();
		bool					checkState(ClientState state);
		void					setState(ClientState state);

		std::string				asPrefix();
		std::string const&		getIdentifier() const;
		void					sendMessage(Client& sender, std::string const& command, std::string const& message);

		ChannelList 			channels;
		std::string				username;
		std::string				hostname;
		std::string				realname;
		int						sock_fd;
		std::string				nickname;
		::sockaddr_in			address;
		std::string				readBuffer;
		std::string				writeBuffer;
		std::string				password;
		bool					shouldClose;
		bool					hasQuit;
		bool					isInvisible;

	private:
		int _state;

		template< Reply code >
		void __replyRaw(std::string const& message);
		void __replyRaw(Reply code, std::string const& message);
		void __processReadBuffer();
		void __log(LogLevel level, std::string const& message);
};

bool operator==(Client const& lhs, Client const& rhs);
bool operator!=(Client const& lhs, Client const& rhs);

#include "template/Client.tpp"
