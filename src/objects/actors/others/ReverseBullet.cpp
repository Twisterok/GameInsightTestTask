#include <objects/actors/others/ReverseBullet.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

void ReverseBullet::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();		
	auto isoPos = utils::toIsometric(getPos());


	g->DrawImageMirror(getImage().get() , 
			Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY, pContext->m_cellWidth*2, pContext->m_cellHeight), 
			Rect(0,0,m_image->GetWidth(),m_image->GetHeight()));
}

void ReverseBullet::Move()
{
	if (nextStateCheck())	m_pos.cellY++;
}