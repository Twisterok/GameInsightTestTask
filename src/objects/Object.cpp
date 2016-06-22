#include <objects/Object.h>

//---------------------------------------
Object::Object(std::shared_ptr<Image> img, Position pos)
{
	setImage(img);
	setPos(pos);
}
//---------------------------------------
void	Object::setImage(std::shared_ptr<Image> img)	
{
	m_image = img;
}
//---------------------------------------
void	Object::setPos(Position pos)
{
	m_pos.cellX = pos.cellX;
	m_pos.cellY = pos.cellY;
}