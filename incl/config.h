#ifndef CONFIG_H
# define CONFIG_H

# define SERVER_NAME "FT IRC42"

# define VERSION_MAJOR 1
# define VERSION_MINOR 0
# define VERSION_PATCH 0

# define _STR(S) #S
# define STR(S) _STR(S)

# define VERSION "" STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

#endif // CONFIG_H
