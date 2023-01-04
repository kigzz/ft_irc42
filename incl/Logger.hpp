#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>

enum LogLevel
{
	DEBUG,
	INFO,
	NOTICE,
	WARNING,
	ERROR,
	FATAL,
};

class Logger
{
private:
	LogLevel _level;

public:
	explicit Logger(LogLevel level);
	~Logger();

public:
	void log(LogLevel level, std::string const& message);
};

#endif
