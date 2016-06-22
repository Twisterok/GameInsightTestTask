#ifndef __FORWARD_CANNON_H__
#define __FORWARD_CANNON_H__
#include <objects/actors/others/Cannon.h>

class ForwardCannon : public Cannon
{
public:
	ForwardCannon(std::shared_ptr<Image> img, Position pos) : Cannon(img,pos) {}
	virtual void Draw(Graphics* g) override;
	virtual std::shared_ptr<Bullet> Shoot() override;
};

#endif