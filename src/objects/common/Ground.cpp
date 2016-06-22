#include <objects/common/Ground.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

using namespace Sexy;

Ground::Ground(std::shared_ptr<Image> img, Position pos, int imgCellXIndex, int imgCellYIndex) :
		Object(img,pos),
		IMAGE_CELL_WIDTH(150),
		IMAGE_CELL_HEIGHT(75),
		m_ImageCellX(imgCellXIndex),
		m_ImageCellY(imgCellYIndex)
{
}
		

void Ground::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();		
	auto isoPos = utils::toIsometric(getPos());

	g->DrawImage(getImage().get() , 
				Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY, pContext->m_cellWidth*2, pContext->m_cellHeight), 
				Rect(m_ImageCellX*IMAGE_CELL_WIDTH,
					m_ImageCellY*IMAGE_CELL_HEIGHT,
					IMAGE_CELL_WIDTH,
					IMAGE_CELL_HEIGHT));
}