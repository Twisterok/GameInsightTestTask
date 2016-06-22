#include <objects/actors/characters/Character.h>

void Character::SetDestination(Position dest)
{
	m_destination = dest;
	m_path.clear();
}

Position Character::GetDestination()
{
	return m_destination;
}

bool Character::NextPosition(Position& pos)
{
	if (m_path.size() > 0)
	{
		pos = m_path.front();
		return true;
	}
	else	return false;
}

void	Character::SetPath(std::list<Position>& path)
{
	m_path.assign(path.begin(),path.end());
}

void	Character::RefreshDirection(const Position& pos)
{
	/*	SouthEast	*/
	if (getPos().cellX < pos.cellX &&
		m_MoveDirection != MoveDirection::SouthEast)
	{
		m_RowImageIndex = 0;
		m_MoveDirection = MoveDirection::SouthEast;
	}

	/*	SouthWest	*/
	else if (getPos().cellY < pos.cellY && 
		m_MoveDirection != MoveDirection::SouthWest)
	{
		m_RowImageIndex = 0;
		m_MoveDirection = MoveDirection::SouthWest;
	}

	/*	NorthWest	*/
	else if ((getPos().cellX > pos.cellX) && 
		m_MoveDirection != MoveDirection::NorthWest)
	{
		m_RowImageIndex = 0;
		m_MoveDirection = MoveDirection::NorthWest;
	}

	/*	NorthEast	*/
	else if (getPos().cellY > pos.cellY && 
		m_MoveDirection != MoveDirection::NorthEast)
	{
		m_RowImageIndex = 0;
		m_MoveDirection = MoveDirection::NorthEast;
	}
	/*	Stop	*/
	else if (getPos() == pos)
	{
		m_RowImageIndex = 4;
		m_MoveDirection = MoveDirection::Stop;
	}
}


bool	Character::nextStateCheck()
{
	m_stepState += m_speed;
	if (abs(m_stepState - 1.0f) < m_speed)
	{
		m_stepState = 0.0f;
		return true;
	}	
	return false;
}

bool Character::isActor()
{
	return true;
}

int Character::getLayerNumber()
{
	return RenderLayer::LAYER_CHARACTER;
}

