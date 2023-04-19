/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:14 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/19 12:57:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_HPP
# define DEFINES_HPP

// int
typedef int		int32;

// Unsigned int types.
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

// Signed int types.
typedef signed char			sint8;
typedef signed short		sint16;
typedef signed int			sint32;
typedef signed long long	sint64;

// Floating point types
typedef float	fl32;
typedef double	dbl64;

// Boolean types
typedef char	bl8;

// color
# define T_RESET "\033[0m"
# define T_BOLD "\033[1m"
# define T_DIM "\033[2m"
# define T_ITALIC "\033[3m"
# define T_UNDERLINE "\033[4m"
# define T_BLINK "\033[5m"
# define T_INVERT "\033[6m"
# define T_REVERSE "\033[7m"
# define T_CONCEALED "\033[8m"

# define T_BLACK "\033[30m"
# define T_RED "\033[31m"
# define T_GREEN "\033[32m"
# define T_YELLOW "\033[33m"
# define T_BLUE "\033[36m"
# define T_MAGENTA "\033[35m"
# define T_CYAN "\033[34m"
# define T_WHITE "\033[37m"

# define true 1
# define false 0

// Platform detection
# if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define TRS_PLATFORM_WINDOWS 1
# ifndef _WIN64
#  error "64-bit is required on Windows!"
# endif
# elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#  define TRS_PLATFORM_LINUX 1
# endif
# elif defined(__unix__)
// Catch anything not caught by the above.
#  define TRS_PLATFORM_UNIX 1
# elif defined(_POSIX_VERSION)
// Posix
#  define TRS_PLATFORM_POSIX 1
# elif __APPLE__
// Apple platforms
#  define TRS_PLATFORM_APPLE 1
#  include <TargetConditionals.h>
# else
#  error "Unknown platform!"
# endif

# ifdef TRS_EXPORT
// Exports
# ifdef _MSC_VER
#  define MACROS __declspec(dllexport)
# else
#  define MACROS __attribute__((visibility("default")))
# endif
# else
// Imports
#  ifdef _MSC_VER
#   define MACROS __declspec(dllimport)
#  else
#   define MACROS
#  endif
# endif

