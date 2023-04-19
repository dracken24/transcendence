/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:20:43 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/19 13:21:02 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// telnet :> open 127.0.0.1 8000
#include "includes/defines.hpp"

#ifdef TRS_PLATFORM_LINUX
# include <cstdlib>
#endif

#include "others/logger.hpp"
#include "others/trsMemory.hpp"


void MemoryTests(Logger log)
{
	// Memory Test //
	IrcMemory memSystem;
	char *test = memSystem.Mallocate(test, sizeof("BananaBomb!!!?!"), TRS_MEMORY_TAG_STRING);
	log.TRS_INFO(memSystem.GetMemoryUsageStr().c_str());

	// TODO: remove when log message are fully implemented
	log.TRS_FATAL("Hello World! %2.f lol %s", 1.0f, "test");
	log.TRS_ERROR("Hello World! %2.f lol %s", 1.0f, "test");
	log.TRS_WARNING("Hello World! %2.f lol %s", 1.0f, "test");
	log.TRS_INFO("Hello World! %2.f lol %s", 1.0f, "test");
	log.TRS_DEBUG("Hello World! %2.f lol %s", 1.0f, "test");
	log.TRS_TRACE("Hello World! %2.f lol %s", 1.0f, "test");

	// Memory Test //
	memSystem.FreeMem(test, sizeof("BananaBomb!!!?!"), TRS_MEMORY_TAG_STRING);
	log.TRS_INFO(memSystem.GetMemoryUsageStr().c_str());
}

int main(int argc, char *argv[])
{
	Logger log;

	log.TRS_INFO("Welcome to Transcendence\n");

	MemoryTests(log);

	return 0;
}
