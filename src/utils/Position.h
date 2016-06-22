#ifndef __POSITION_H__
#define __POSITION_H__

class Position
{
public:
	int	cellX;
	int	cellY;

	Position() : cellX(-100), cellY(-100) {}
	Position(int _x, int _y) : cellX(_x), cellY(_y) {}

	bool operator==(const Position& pos)	{ return pos.cellX == cellX && pos.cellY == cellY; }
	bool operator!=(const Position& pos)	{ return !this->operator==(pos); }
	void operator=(const Position& pos)		
	{ 
		cellX = pos.cellX;
		cellY = pos.cellY;
	}
};
#endif