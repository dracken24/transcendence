/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trsMemory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:54:37 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/19 13:09:38 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRSMEMORY_HPP
# define TRSMEMORY_HPP

# include "../includes/defines.hpp"
# include "logger.hpp"

# include <string>
# include <vector>

typedef enum	memoryTag
{
	// For temporary use. Should be assigned one of the below or have a new tag created.
	TRS_MEMORY_TAG_UNKNOWN,
	TRS_MEMORY_TAG_STRING,
	TRS_MEMORY_TAG_APPLICATION,

	TRS_MEMORY_TAG_MAX_TAGS
}	memoryTag;

typedef struct memoryStats
{
	uint64	allocTotal;
	uint64	allocTagged[TRS_MEMORY_TAG_MAX_TAGS];
}	memoryStats;

typedef struct	memorySystemState
{
	struct memoryStats	stats;
	uint64				allocCount;
}	memorySystemState;

class IrcMemory
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//

	public:
		IrcMemory(void);
		IrcMemory(IrcMemory const &copy);
		IrcMemory &operator=(IrcMemory const &copy);
		~IrcMemory(void);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		template <typename T>
		T		Mallocate(T memPtr, uint64 size, memoryTag tag)
		{
			if (tag == TRS_MEMORY_TAG_UNKNOWN)
			{
				_log.TRS_WARNING("Mallocate called using TRS_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
			}

			_memSystem.stats.allocTotal += size;
			_memSystem.stats.allocTagged[tag] += size;
			_memSystem.allocCount++;

			void *block = (void *)new T();
			SetMemory(block, 0, sizeof(T));

			return (T)block;
		}

		template <typename T>
		void 		FreeMem(T block, uint64 size, memoryTag tag)
		{
			if (tag == TRS_MEMORY_TAG_UNKNOWN)
			{
				_log.TRS_WARNING("FreeMem called using TRS_MEMORY_TAG_UNKNOWN. Re-class this allocation.");
			}

			_memSystem.stats.allocTotal -= size;
			_memSystem.stats.allocTagged[tag] -= size;
			_memSystem.allocCount--;

			// TODO: Memory alignment
			delete block;
		}

		void		*CopyMemory(void* dest, const void* source, uint64 size);

		void		*SetMemory(void* dest, sint32 value, uint64 size);

		std::string	GetMemoryUsageStr(void);

		uint64		GetMemoryAllocCount(void);

	//**********************************************************************//
	//**                        Private Variables                         **//
	//**********************************************************************//

	private:

		Logger						_log;

		memorySystemState			_memSystem;

		std::vector<std::string>	_memoryTagStrings;
};

#endif
