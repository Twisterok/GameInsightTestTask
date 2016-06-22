#include <objects/actors/others/Bullet.h>
#include <utils/definitions.h>

Bullet::Bullet(std::shared_ptr<Image> img, Position pos) : 
		Object(img,pos),
		m_stepState(0)
{
	m_speed = 0.1f;
	// speed = cells per frame (e.g. 0.2 = 5 frames per 1 cell changed	*/
}
bool Bullet::isActor()
{
	return true;
}

int Bullet::getLayerNumber()
{
	return RenderLayer::LAYER_BULLET;
}

bool	Bullet::nextStateCheck()
{
	m_stepState += m_speed;
	if (abs(m_stepState - 1.0f) < m_speed)
	{
		m_stepState = 0.0f;
		return true;
	}	
	return false;
}