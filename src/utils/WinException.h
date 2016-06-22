#ifndef __WIN_EXCEPTION_H__
#define __WIN_EXCEPTION_H__
#include <utils/Exception.h>
#include <string>

class WinException: public Exception
{
public:
	WinException() : Exception(0,"You won") {}
};

#endif