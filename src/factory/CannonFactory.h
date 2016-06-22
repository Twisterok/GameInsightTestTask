#ifndef __CANNON_FACTORY_H__
#define __CANNON_FACTORY_H__
#include <objects/actors/others/Cannon.h>

// std includes
#include <memory>

class CannonFactory
{
	CannonFactory();
	std::weak_ptr<Image>	m_image;
public:
	void Init(std::shared_ptr<Image> img);
	std::shared_ptr<Cannon>	MakeCannon(Position pos);
	static CannonFactory* singleton();
};
#endif