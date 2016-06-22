#ifndef __FORWARD_BULLET_H__
#define __FORWARD_BULLET_H__
#include <objects/actors/others/Bullet.h>

class ForwardBullet : public Bullet
{
public:
	ForwardBullet(std::shared_ptr<Image> img, Position pos) : Bullet(img,pos) {}
	virtual void Draw(Graphics* g)	override;
	virtual void Move()				override;
};

#endif