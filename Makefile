NAME	=	ircserv

CC		=	c++

FLAGS	=	-Wall -Wextra -Werror -Iincl -g3 -MMD -MP -std=c++98

# main
SRC		= main.cpp

# utils

SRC		+= utils/NameUtils.cpp

# classes
SRC		+= class/NicknameManager.cpp
SRC		+= class/ClientManager.cpp
SRC		+= class/ChannelManager.cpp
SRC		+= class/ConnectionManager.cpp
SRC		+= class/exception/IOException.cpp

SRC		+= Recipient.cpp
SRC		+= Client.cpp
SRC		+= CommandContext.cpp
SRC		+= Channel.cpp
SRC		+= Server.cpp
SRC		+= CommandMap.cpp
SRC		+= Reply.cpp
SRC		+= OperatorEntry.cpp
SRC		+= wildcard.cpp
SRC		+= Logger.cpp

# commands
SRC		+= cmds/user.cpp
SRC		+= cmds/nick.cpp
SRC		+= cmds/pass.cpp
SRC		+= cmds/quit.cpp
SRC		+= cmds/part.cpp
SRC		+= cmds/join.cpp
SRC		+= cmds/motd.cpp
SRC		+= cmds/oper.cpp
SRC		+= cmds/die.cpp
SRC		+= cmds/kill.cpp
SRC		+= cmds/ping.cpp
SRC		+= cmds/mode.cpp
SRC		+= cmds/privmsg.cpp
SRC		+= cmds/restart.cpp
SRC		+= cmds/notice.cpp
SRC		+= cmds/topic.cpp
SRC		+= cmds/kick.cpp
SRC		+= cmds/list.cpp
SRC		+= cmds/names.cpp
SRC		+= cmds/invite.cpp

OBJ		:=	$(addprefix ./obj/,$(SRC:%.cpp=%.o))

DEP		=	$(OBJ:%.o=%.d)

RM		=	rm -rf

all: $(NAME)

-include $(DEP)

./obj/%.o: ./src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) obj/

fclean:
	$(RM) obj/
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
