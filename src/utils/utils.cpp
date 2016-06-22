#include <utils/utils.h>
#include <context/GlobalContext.h>
#include <boost/math/special_functions/round.hpp>

namespace utils
{
	//--------------------------------------------
	Position toIsometric(const Position& pos)
	{
		auto pContext = GlobalContext::singleton();
		Position result;

		double x = pos.cellX * pContext->m_cellWidth;
		double y = pos.cellY * pContext->m_cellHeight;
		double tmpX,tmpY;
		tmpX = x - y;
		tmpY = (x + y)/2;

		tmpX += (pContext->m_offsetMapX + pContext->m_offsetX);
		tmpY += pContext->m_offsetY;

		result.cellX = boost::math::iround(tmpX);
		result.cellY = boost::math::iround(tmpY);
		return result;
	}
	//--------------------------------------------
	Position fromIsometric(const Position& pos)
	{
		/*
		Position result;

		 f^(-1)(x)
			x = (2iY+iX)/2
			y = (2iY-iX)/2
			iX,iY - isometric X,Y
		result.cellX = (2*pos.cellY + pos.cellX)/2;
		result.cellY = (2*pos.cellY - pos.cellX)/2;
		return result;*/
		Position result;
		auto pContext = GlobalContext::singleton();
		double x = pos.cellX - (pContext->m_offsetMapX + pContext->m_offsetX);
		double y = pos.cellY - pContext->m_offsetY;
		double tmpX = boost::math::iround( (2*y + x)/2.0);
		double tmpY = boost::math::iround( (2*y - x)/2.0);

		result.cellX = boost::math::iround(tmpX / pContext->m_cellWidth);
		result.cellY = boost::math::iround(tmpY / pContext->m_cellHeight);
		return result;
	}
}