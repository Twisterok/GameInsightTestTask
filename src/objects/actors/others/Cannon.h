#ifndef __CANNON_H__
#define __CANNON_H__

#include <objects/Object.h>
#include <objects/actors/others/Bullet.h>
class Cannon : public Object
{
public:
	Cannon(std::shared_ptr<Image> img, Position pos)  : Object(img,pos), m_attackSpeed(0.007f), m_stepState(0.0f) {}
	virtual ~Cannon() {}
	virtual void Draw(Graphics* g) = 0;
	virtual std::shared_ptr<Bullet> Shoot() = 0;
protected:

	bool	nextStateCheck();

	float	m_attackSpeed;
	float	m_stepState;
};

#endif