#include <objects/actors/others/ReverseCannon.h>
#include <factory/BulletFactory.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

void ReverseCannon::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();		
	auto isoPos = utils::toIsometric(getPos());

	g->DrawImageMirror(getImage().get() , 
			Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY - pContext->m_cellHeight, pContext->m_cellWidth*2, pContext->m_cellHeight*2), 
			Rect(0,0,m_image->GetWidth(),m_image->GetHeight()));
}

std::shared_ptr<Bullet> ReverseCannon::Shoot()
{
	std::shared_ptr<Bullet> result;
	if (nextStateCheck())	result = std::shared_ptr<Bullet>(BulletFactory::singleton()->MakeBullet(Direction::REVERSE,"Bullet", Position(m_pos.cellX,0)) );
	return result;
}