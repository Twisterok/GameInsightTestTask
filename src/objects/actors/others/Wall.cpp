#include <objects/actors/others/Wall.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

int Wall::getLayerNumber()
{
	return RenderLayer::LAYER_WALL;
}
void Wall::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();
	auto isoPos = utils::toIsometric(getPos());
	
	g->DrawImage(getImage().get() , 
				Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY - pContext->m_cellHeight, pContext->m_cellWidth*2, pContext->m_cellHeight*2), 
				Rect(IMAGE_CELL_X*IMAGE_CELL_WIDTH,
					IMAGE_CELL_Y*IMAGE_CELL_HEIGHT,
					IMAGE_CELL_WIDTH,
					IMAGE_CELL_HEIGHT));
}