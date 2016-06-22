#include <objects/actors/characters/Hero.h>
#include <context/GlobalContext.h>
#include <utils/utils.h>
#include <utils/Position.h>

Hero::Hero(std::shared_ptr<Image> img, Position pos) : Character(img,pos) 
{
	IMAGES_IN_ROW = 8;
	CELL_IMAGE_WIDTH = 50;
	CELL_IMAGE_HEIGHT = 50;
	m_speed = 0.08;
}

void	Hero::Move()
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

void	Hero::Draw(Graphics* g)
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

int		Hero::GetRow(int moveDirection)
{
	switch (moveDirection)
	{
	case MoveDirection::NorthEast:	return 6;
	case MoveDirection::NorthWest:	return 4;
	case MoveDirection::SouthEast:	return 0;
	case MoveDirection::SouthWest:	return 2;
	default:						return 5;
	}
}