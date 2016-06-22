#ifndef __BULLET_FACTORY_H__
#define __BULLET_FACTORY_H__
#include <objects/actors/others/Bullet.h>

// std includes
#include <memory>
#include <unordered_map>
#include <functional>

class BulletFactory
{	
	BulletFactory();
	std::weak_ptr<Image>	m_image;
	std::unordered_map<std::string, std::function<Bullet*(Position pos)> >	m_forwardBulletGenerators;
	std::unordered_map<std::string, std::function<Bullet*(Position pos)> >	m_reverseBulletGenerators;
	
public:
	void Init(std::shared_ptr<Image> img);
	std::shared_ptr<Bullet>	MakeBullet(int BulletDirection, std::string BulletType, Position pos);
	static BulletFactory* singleton();
};
#endif