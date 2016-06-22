#ifndef __GROUND_H__
#define __GROUND_H__
#include <objects/Object.h>

class Ground : public Object
{
public:
	Ground(std::shared_ptr<Image> img, Position pos, int imgCellXIndex, int imgCellYIndex);
	void Draw(Graphics* g) override;
private:
	int m_ImageCellX;
	int m_ImageCellY;

	const int IMAGE_CELL_WIDTH;
	const int IMAGE_CELL_HEIGHT;
};

#endif