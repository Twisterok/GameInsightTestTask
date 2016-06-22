#ifndef __BULLET_H__
#define __BULLET_H__
#include <objects/Object.h>

class Bullet : public Object
{
public:
	Bullet(std::shared_ptr<Image> img, Position pos);	// speed = cells per frame (e.g. 0.2 = 5 frames per 1 cell changed	*/
	virtual ~Bullet() {}

	bool	isActor()	override;
	int		getLayerNumber() override;

	virtual void	Draw(Graphics* g) = 0;
	virtual void	Move() = 0;
protected:
	
	bool	nextStateCheck();

	float	m_speed;
	float	m_stepState;
};
#endif