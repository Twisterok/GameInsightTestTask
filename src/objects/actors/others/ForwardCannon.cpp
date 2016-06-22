#include <objects/actors/others/ForwardCannon.h>
#include <factory/BulletFactory.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

void ForwardCannon::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();
	auto isoPos = utils::toIsometric(getPos());

	g->DrawImage(getImage().get() , 
			Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY - pContext->m_cellHeight, pContext->m_cellWidth*2, pContext->m_cellHeight*2), 
				Rect(0,0,m_image->GetWidth(),m_image->GetHeight()));
}

std::shared_ptr<Bullet> ForwardCannon::Shoot()
{
	std::shared_ptr<Bullet> result;
	if (nextStateCheck())	result = std::shared_ptr<Bullet>(BulletFactory::singleton()->MakeBullet(Direction::FORWARD,std::string("Bullet"), Position(0,m_pos.cellY)) );	
	return result;
}