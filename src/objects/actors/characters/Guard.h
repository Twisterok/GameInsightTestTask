#ifndef __GUARD_H__
#define __GUARD_H__
#include <objects/actors/characters/Character.h>

class Guard : public Character
{
public:
	Guard(std::shared_ptr<Image> img, Position from, Position to);
	void	Move() override;
	void	Draw(Graphics* g) override;
	int		GetRow(int moveDirection) override;
	void	SwitchDestination();

	Position m_start;
	Position m_finish;
};

#endif