#include <objects/actors/others/ForwardBullet.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>


void ForwardBullet::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();			
	auto isoPos = utils::toIsometric(getPos());

	g->DrawImage(getImage().get() , 
			Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY, pContext->m_cellWidth*2, pContext->m_cellHeight), 
			Rect(0,0,m_image->GetWidth(),m_image->GetHeight()));
}

void ForwardBullet::Move()
{
	if (nextStateCheck())	m_pos.cellX++;
}