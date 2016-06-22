#ifndef __LOSE_EXCEPTION_H__
#define __LOSE_EXCEPTION_H__
#include <utils/Exception.h>
#include <string>

class LoseException: public Exception
{
public:
	LoseException() : Exception(0,"You lost") {}
};

#endif