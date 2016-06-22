#ifndef __OBJECT_H__
#define __OBJECT_H__

// Sexy includes
#include <SexyAppFramework/Widget.h>
#include <SexyAppFramework/DDImage.h>

// own includes
#include <utils/definitions.h>
#include <utils/Position.h>

// std includes
#include <memory>

using namespace Sexy;

class Object
{
public:

	Object(std::shared_ptr<Image> img, Position pos);
	virtual ~Object() {}

	virtual void	Draw(Graphics* g) = 0;
	virtual int		getLayerNumber()	{	return RenderLayer::LAYER_COMMON;	}
	virtual bool	isActor()			{	return false;}

	int	getDeep()	{	return m_pos.cellY * getLayerNumber() + m_pos.cellX; }
	/* getters	*/
	std::shared_ptr<Image>	getImage()	{ return m_image;	} 
	Position				getPos()	{ return m_pos;		}

	/*	setters	*/
	void	setImage(std::shared_ptr<Image> img);
	void	setPos(Position pos);
protected:
	std::shared_ptr<Image>	m_image;
	Position				m_pos;
};
#endif