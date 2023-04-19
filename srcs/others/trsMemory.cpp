/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trsMemory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:54:30 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/19 13:09:22 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trsMemory.hpp"
#include <stdio.h>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

IrcMemory::IrcMemory(void)
{
	_memSystem.allocCount = 0;
	_memSystem.stats.allocTotal = 0;

	for (int i = 0; i < TRS_MEMORY_TAG_MAX_TAGS; i++)
		_memSystem.stats.allocTagged[i] = 0;

	_memoryTagStrings.push_back("              UNKNOWN     : ");
	_memoryTagStrings.push_back("              STRING      : ");
	_memoryTagStrings.push_back("              APPLICATION : ");
	_memoryTagStrings.push_back("\n              TOTAL       : ");
}

IrcMemory::IrcMemory(IrcMemory const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

IrcMemory	&IrcMemory::operator=(IrcMemory const &copy)
{
	if (this != &copy)
	{
		_log = copy._log;
		_memSystem.allocCount = copy._memSystem.allocCount;
		_memSystem.stats.allocTotal = copy._memSystem.stats.allocTotal;

		for (int i = 0; i < TRS_MEMORY_TAG_MAX_TAGS; i++)
			_memSystem.stats.allocTagged[i] = copy._memSystem.stats.allocTagged[i];
	}

	return *this;
}

IrcMemory::~IrcMemory(void)
{
	
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

void*	IrcMemory::CopyMemory(void* dest, const void* source, uint64 size)
{
	return std::memcpy(dest, source, size);
}

void*	IrcMemory::SetMemory(void* dest, sint32 value, uint64 size)
{
	return std::memset(dest, value, size);
}

std::string	IrcMemory::GetMemoryUsageStr(void)
{
	const uint64 gib = 1024 * 1024 * 1024;
	const uint32 mib = 1024 * 1024;
	const uint16 kib = 1024;

	std::string buffer = "------------------------------\n";
	buffer += "              Memory in use for the engine :\n\n";
	// uint64 offset = buffer.size();
	for (uint32 i = 0; i <= TRS_MEMORY_TAG_MAX_TAGS; ++i)
	{
		char unit[4] = " Xb";
		float amount = 1.0f;

		if (i < TRS_MEMORY_TAG_MAX_TAGS)
			amount = (float)_memSystem.stats.allocTagged[i];
		else
			amount = (float)_memSystem.stats.allocTotal;

		if (_memSystem.stats.allocTagged[i] >= gib || (_memSystem.stats.allocTotal
			>= gib && i >= TRS_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'G';
			amount /= (float)gib;
		}
		else if (_memSystem.stats.allocTagged[i] >= mib || (_memSystem.stats.allocTotal
			>= mib && i >= TRS_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'M';
			amount /= (float)mib;
		}
		else if (_memSystem.stats.allocTagged[i] >= kib || (_memSystem.stats.allocTotal
			>= kib && i >= TRS_MEMORY_TAG_MAX_TAGS))
		{
			unit[1] = 'K';
			amount /= (float)kib;
		}
		else
		{
			unit[1] = 'B';
			unit[2] = 0;
		}
		buffer += _memoryTagStrings[i].c_str();
		buffer += std::to_string(amount);
		buffer += unit;
		buffer += "\n";
	}
	buffer += "\n              NBR OF ALLOC: ";
	buffer += std::to_string(GetMemoryAllocCount());
	buffer += "\n              ------------------------------\n";
	// std::string outString = buffer;

	return (buffer);
}

uint64	IrcMemory::GetMemoryAllocCount(void)
{
	return _memSystem.allocCount;
}
