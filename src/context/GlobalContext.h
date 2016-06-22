#ifndef __GLOBAL_CONTEXT_H__
#define __GLOBAL_CONTEXT_H__
// Own includes
#include <utils/Position.h>
// std includes


class GlobalContext
{
    GlobalContext();
    ~GlobalContext();

public:	

	int	m_rowsCount;
	int	m_columsCount;
	int	m_fieldWidth;
	int	m_fieldHeight;

	float	m_offsetMapX;
	float	m_offsetX;
	float	m_offsetY;

	float	m_cellWidth;
	float	m_cellHeight;

	bool checkPos(const Position& pos);

    static  GlobalContext*	singleton();
};

#endif

