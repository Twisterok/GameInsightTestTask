#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <objects/Object.h>
#include <utils/Position.h>
#include <utils/definitions.h>

class Character : public Object
{
public:
	Character(std::shared_ptr<Image> img, Position pos) :
			Object(img,pos),
			m_MoveDirection(MoveDirection::Stop),
			m_RowImageIndex(0),
			m_stepState(0.0f)	
	{
		m_destination = pos;
	}
	virtual ~Character() {}
	virtual void Move() = 0;	
	bool	isActor()	override;
	int		getLayerNumber() override;

	void				SetDestination(Position dest);
	Position			GetDestination();
	bool				NextPosition(Position& pos);	
	void				SetPath(std::list<Position>& path);
protected:
	std::list<Position>	m_path;
	Position			m_destination;		

	void	RefreshDirection(const Position& nextPos);
	virtual	int		GetRow(int moveDirection) = 0;

	int	m_MoveDirection;
	
	int	m_RowImageIndex;	// column in row

	int IMAGES_IN_ROW;
	int CELL_IMAGE_WIDTH;
	int CELL_IMAGE_HEIGHT;
	
	float	m_speed;
	float	m_stepState;
	bool	nextStateCheck();
};
#endif