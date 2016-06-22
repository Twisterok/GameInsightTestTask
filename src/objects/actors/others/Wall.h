#ifndef __WALL_H__
#define __WALL_H__

#include <objects/Object.h>

class Wall : public Object
{
public:
	Wall(std::shared_ptr<Image> img, Position pos)  : 
			Object(img,pos),
			IMAGE_CELL_WIDTH(87.5),
			IMAGE_CELL_HEIGHT(87.5),
			IMAGE_CELL_X(1),
			IMAGE_CELL_Y(3)
	{
	}
	void	Draw(Graphics* g) override;
	int		getLayerNumber() override;


private:

	const int	IMAGE_CELL_X;
	const int	IMAGE_CELL_Y;
	const float IMAGE_CELL_WIDTH;
	const float IMAGE_CELL_HEIGHT;
};

#endif