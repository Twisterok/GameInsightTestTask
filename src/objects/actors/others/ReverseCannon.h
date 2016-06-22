#ifndef __REVERSE_CANNON_H__
#define __REVERSE_CANNON_H__
#include <objects/actors/others/Cannon.h>

class ReverseCannon : public Cannon
{
public:
	ReverseCannon(std::shared_ptr<Image> img, Position pos) : Cannon(img,pos) {}
	virtual void Draw(Graphics* g) override;
	virtual std::shared_ptr<Bullet> Shoot() override;
};

#endif