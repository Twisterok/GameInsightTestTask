#include <objects/actors/characters/Guard.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

Guard::Guard(std::shared_ptr<Image> img, Position from, Position to) : 
			Character(img,from)								
{
	IMAGES_IN_ROW = 8;
	CELL_IMAGE_WIDTH = 50;
	CELL_IMAGE_HEIGHT = 34;
	m_speed = 0.05;
	m_start = from;
	m_finish = to;
}

void Guard::Move()
{
	Position nextPos;
	if (nextStateCheck())
	{
		if (!NextPosition(nextPos))	return;
		m_path.erase(m_path.begin());
		if (m_MoveDirection != MoveDirection::Stop)	++m_RowImageIndex;
		if (m_RowImageIndex >= IMAGES_IN_ROW)	m_RowImageIndex = 0;
		RefreshDirection(nextPos);
		this->setPos(nextPos);	
	}
}

void	Guard::SwitchDestination()
{
	std::swap(m_start,m_finish);
}

void Guard::Draw(Graphics* g)
{
	auto pContext = GlobalContext::singleton();				
	int rowNumber = GetRow(m_MoveDirection);	// row of image		
	auto isoPos = utils::toIsometric(getPos());

	g->DrawImage(getImage().get() , 
			Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY - pContext->m_cellHeight, pContext->m_cellWidth*2, pContext->m_cellHeight*2), 
			Rect(m_RowImageIndex*CELL_IMAGE_WIDTH,
					rowNumber*CELL_IMAGE_HEIGHT,
					CELL_IMAGE_WIDTH,
					CELL_IMAGE_HEIGHT));
}

int		Guard::GetRow(int moveDirection)
{
	switch (moveDirection)
	{
	case MoveDirection::NorthEast:	return 5;
	case MoveDirection::NorthWest:	return 3;
	case MoveDirection::SouthEast:	return 7;
	case MoveDirection::SouthWest:	return 1;
	default:						return 4;
	}
}