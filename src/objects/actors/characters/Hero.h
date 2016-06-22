#ifndef __HERO_H__
#define __HERO_H__
#include <objects/actors/characters/Character.h>

class Hero : public Character
{
public:
	Hero(std::shared_ptr<Image> img, Position pos);
	void	Move() override;
	void	Draw(Graphics* g) override;
	int		GetRow(int moveDirection) override;
};
#endif