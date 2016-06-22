#ifndef __UTILS_H__
#define __UTILS_H__
#include <utils/Position.h>

namespace utils
{
	 Position toIsometric(const Position& pos);
	 Position fromIsometric(const Position& pos);
}

#endif