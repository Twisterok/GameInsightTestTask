#include <factory/CannonFactory.h>
#include <objects/actors/others/ForwardCannon.h>
#include <objects/actors/others/ReverseCannon.h>

CannonFactory::CannonFactory()
{
}
//--------------------------------------------------------------
void CannonFactory::Init(std::shared_ptr<Image> img)
{
	m_image = img;
}
//--------------------------------------------------------------
std::shared_ptr<Cannon>	CannonFactory::MakeCannon(Position pos)
{
	auto lockImg = m_image.lock();
	if (pos.cellX * pos.cellY > 0		||
		pos.cellX == 0 && pos.cellY == 0	||
		!lockImg)	
	{
		/* invalid position	or image isn't set	*/
		return nullptr;
	}

	std::shared_ptr<Cannon> result;
	if (pos.cellY > 0)	result = std::shared_ptr<Cannon>(new ForwardCannon(lockImg,pos));	// left border
	else				result = std::shared_ptr<Cannon>(new ReverseCannon(lockImg,pos));	// top border
	return result;
}
//--------------------------------------------------------------
CannonFactory* CannonFactory::singleton()
{
    static CannonFactory s_factory;
	return &s_factory;
}