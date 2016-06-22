#include <factory/BulletFactory.h>
#include <objects/actors/others/ForwardBullet.h>
#include <objects/actors/others/ReverseBullet.h>

BulletFactory::BulletFactory()
{	
}	

void BulletFactory::Init(std::shared_ptr<Image> img)
{
	m_image = img;	
	/*	forward bullets	*/
	m_forwardBulletGenerators["Bullet"] = [this](Position pos) -> Bullet* {
		auto lockImg = m_image.lock();
		return (Bullet*) new ForwardBullet(lockImg,pos);
	};

	/*	reverse bullets	*/
	m_reverseBulletGenerators["Bullet"] = [this](Position pos) -> Bullet* {
		auto lockImg = m_image.lock();
		return (Bullet*) new ReverseBullet(lockImg,pos);
	};
}

std::shared_ptr<Bullet>	BulletFactory::MakeBullet(int BulletDirection, std::string BulletType, Position pos)
{
	decltype(m_forwardBulletGenerators)	*ptrGeneratorsPool;
	if (BulletDirection == Direction::FORWARD)		ptrGeneratorsPool = &m_forwardBulletGenerators;
	else if (BulletDirection == Direction::REVERSE)	ptrGeneratorsPool = &m_reverseBulletGenerators;
	else											return nullptr;


	auto found = ptrGeneratorsPool->find(BulletType);
	if (found == ptrGeneratorsPool->end())	return nullptr;
	auto BulletMaker = found->second;
	return std::shared_ptr<Bullet>(BulletMaker(pos));
}

BulletFactory* BulletFactory::singleton()
{
    static BulletFactory s_factory;
	return &s_factory;
}