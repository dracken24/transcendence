/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/19 12:57:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include "../includes/defines.hpp"
// # include <stdio.h>
// # include <stdarg.h>
# include <cstring>
# include <iostream>

# define LOG_WARNING_ENABLED true
# define LOG_INFO_ENABLED true
# define LOG_DEBUG_ENABLED true
# define LOG_TRACE_ENABLED true

// Disable debug and trace logs in release builds
# if DE_RELEASE == 1
#  undef LOG_DEBUG_ENABLED 0
#  undef LOG_TRACE_ENABLED 0
# endif

typedef enum	logLevel
{
	TRS_LOG_LEVEL_FATAL = 0,
	TRS_LOG_LEVEL_ERROR = 1,
	TRS_LOG_LEVEL_WARNING = 2,
	TRS_LOG_LEVEL_INFO = 3,
	TRS_LOG_LEVEL_DEBUG = 4,
	TRS_LOG_LEVEL_TRACE = 5
}	logLevel;

class Logger
{
	public:
		Logger(void);
		Logger(Logger const &copy);
		Logger	&operator=(Logger const &copy);
		~Logger(void);

	//*************************************************************************************//
		bl8 LogInit();
		void LogShutdown();

		// Fonction Macros
		MACROS void LogMessage(logLevel level, const char *message, ...);
	//*************************************************************************************//
	private:
};


// Log an error message as a fatal error lvl.
# define TRS_FATAL(message, ...) LogMessage(TRS_LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

# ifndef TRS_ERROR
// Log an error message as an error lvl.
#  define TRS_ERROR(message, ...) LogMessage(TRS_LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
# endif

# if LOG_WARNING_ENABLED == 1
// Log an error message as a warning lvl.
#  define TRS_WARNING(message, ...) LogMessage(TRS_LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
# else
// if warnings are disabled, just ignore them
#  define TRS_WARNING(message, ...) ;
# endif

# if LOG_INFO_ENABLED == 1
// Log an error message as an info lvl.
#  define TRS_INFO(message, ...) LogMessage(TRS_LOG_LEVEL_INFO, message, ##__VA_ARGS__);
# else
// if info logs are disabled, just ignore them
#  define TRS_INFO(message, ...) ;
# endif

# if LOG_DEBUG_ENABLED == 1
// Log an error message as a debug lvl.
#  define TRS_DEBUG(message, ...) LogMessage(TRS_LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
# else
// if debug logs are disabled, just ignore them
#  define TRS_DEBUG(message, ...) ;
# endif

# if LOG_TRACE_ENABLED == 1
// Log an error message as a trace lvl.
#  define TRS_TRACE(message, ...) LogMessage(TRS_LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
# else
// if trace logs are disabled, just ignore them
#  define TRS_TRACE(message, ...) ;
# endif

#endif
