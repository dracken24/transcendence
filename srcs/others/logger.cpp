/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:28 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/19 12:57:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.hpp"
#include <cstdarg>
#include <stdio.h>

void	PlatconsoleWriteError(std::string message, uint8 color);
void	PlatconsoleWrite(std::string message, uint8 color);

Logger::Logger(void)
{
}

Logger::Logger(Logger const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

Logger &Logger::operator=(Logger const &copy)
{
	if (this != &copy)
	{

	}

	return (*this);
}

Logger::~Logger(void)
{
}


bl8		Logger::LogInit(void)
{
	return (true);
}

void	Logger::LogShutdown(void)
{
}

// Platform platform;

void	Logger::LogMessage(logLevel level, const char *message, ...)
{
	const char	*levelStr[6] = {"[*FATAL*]   : ", "[*ERROR*]   : ", "[*WARNING*] : ",
		"[*INFO*]    : ", "[*DEBUG*]   : ", "[*TRACE*]   : "};
	bl8 shouldLog = level < TRS_LOG_LEVEL_WARNING;

	char outMessage[4096];
	std::memset(outMessage, 0, sizeof(outMessage));

	va_list args;
	va_start(args, message);
	vsnprintf(outMessage, 4096, message, args);
	va_end(args);

	std::string outBuffer = levelStr[level];
	outBuffer += outMessage;

	if (shouldLog)
	{
		PlatconsoleWriteError(outBuffer, level);
	}
	else
	{
		PlatconsoleWrite(outBuffer, level);
	}
}

void	PlatconsoleWrite(std::string message, uint8 color)
{
	// WARN,INFO,DEBUG,TRACE
	std::string colorStr[] = {T_YELLOW, T_GREEN, T_BLUE, T_CYAN};

	std::cout << colorStr[color - 2] << message << T_RESET << std::endl;
}

void	PlatconsoleWriteError(std::string message, uint8 color)
{
	// FATAL,ERROR
	std::string colorStr[] = {T_RED, T_RED};

	std::cout << colorStr[color] << message << T_RESET << std::endl;
}
