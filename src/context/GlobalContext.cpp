// Own includes
#include <context/GlobalContext.h>

// std includes

GlobalContext::GlobalContext() : 
	m_rowsCount(30), 
	m_columsCount(30),
	m_fieldWidth(810),
	m_fieldHeight(810),
	m_offsetX(25),
	m_offsetY(100)
{    
	m_cellWidth =	m_fieldWidth  / float(m_columsCount);
	m_cellHeight =	m_fieldHeight / float(m_rowsCount);
	m_offsetMapX =	m_fieldHeight;
}

GlobalContext::~GlobalContext()
{
}

GlobalContext*	GlobalContext::singleton()
{
    static GlobalContext s_context;
	return &s_context;
}


bool GlobalContext::checkPos(const Position& pos)
{
	auto pContext = GlobalContext::singleton();
	return (pos.cellX >= 0 && pos.cellX < pContext->m_columsCount) &&
		(pos.cellY >= 0 && pos.cellY < pContext->m_rowsCount);
}