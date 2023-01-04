#pragma once

#include <deque>
#include <string>

class Channel;

class ChannelManager
{
public:
	typedef std::deque< Channel > container_type;
	typedef container_type::iterator iterator;
	typedef container_type::reverse_iterator reverse_iterator;

private:
	container_type _channels;

public:
	ChannelManager();
	~ChannelManager();

public:
	iterator getChannel(std::string const& name);
	iterator addChannel(Channel const& channel);
	bool removeChannel(std::string const& channelName);
	bool removeChannel(iterator channel);
	void clear();

public:
	iterator begin();
	iterator end();

};
