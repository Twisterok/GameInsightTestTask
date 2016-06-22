#ifndef __REVERSE_BULLET_H__
#define __REVERSE_BULLET_H__
#include <objects/actors/others/Bullet.h>

class ReverseBullet : public Bullet
{
public:
	ReverseBullet(std::shared_ptr<Image> img, Position pos) : Bullet(img,pos) {}
	virtual void Draw(Graphics* g)	override;
	virtual void Move()				override;
};

#endif