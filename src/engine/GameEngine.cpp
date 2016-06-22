#include <engine/GameEngine.h>
#include <context/GlobalContext.h>
#include <utils/LoseException.h>
#include <utils/WinException.h>

GameEngine::GameEngine()
{
	Clear();
}

void GameEngine::AddActor(std::shared_ptr<Cannon> cannon)
{
	auto found = std::find_if(m_cannons.begin(),m_cannons.end(),[&cannon](const std::shared_ptr<Cannon>& curCannon) 
	{
		return curCannon->getPos() == cannon->getPos();
	});
	if (found == m_cannons.end())	m_cannons.push_back(cannon);
}

void GameEngine::AddActor(std::shared_ptr<Bullet> bullet)
{
	if (bullet)
	{		
		std::shared_ptr<Wall> pWall;
		std::shared_ptr<Bullet> pBullet;
		std::shared_ptr<Guard> pGuard;
		std::shared_ptr<Hero> pHero;
		auto actor = m_gameField[bullet->getPos().cellX][bullet->getPos().cellY];
		if ( ( pWall =	std::dynamic_pointer_cast<Wall>(actor)) || 
			( pGuard = std::dynamic_pointer_cast<Guard>(actor)))
		{
		}
		else if ( pBullet =	std::dynamic_pointer_cast<Bullet>(actor))
		{
			RemoveActor(pBullet);
		}
		else if ( pHero = std::dynamic_pointer_cast<Hero>(actor))
		{
			throw LoseException();
		}
		else
		{
			m_bullets.push_back(bullet);
			m_gameField[bullet->getPos().cellX][bullet->getPos().cellY] = bullet;
		}
	}
}

void GameEngine::AddActor(std::shared_ptr<Wall> wall)
{
	if (!checkPos(wall->getPos()))	return;
	if (wall && isCellFree(wall->getPos().cellX, wall->getPos().cellY))	
	{
		m_walls.push_back(wall);
		m_gameField[wall->getPos().cellX][wall->getPos().cellY] = wall;
	}
}	

void GameEngine::MoveActor(std::list< std::shared_ptr<Cannon> >::iterator cannonIt)
{
	auto cannon = *cannonIt;
	auto bullet = cannon->Shoot();	
	AddActor(bullet);
}

void GameEngine::MoveActor(std::list< std::shared_ptr<Bullet> >::iterator bulletIt)
{
	auto pContext = GlobalContext::singleton();
	auto bullet = *bulletIt;
	m_gameField[bullet->getPos().cellX][bullet->getPos().cellY] = nullptr;
	m_bullets.erase(bulletIt);

	bullet->Move();
	if ( (bullet->getPos().cellX < pContext->m_columsCount	&& bullet->getPos().cellX >= 0 ) && 
		 (bullet->getPos().cellY < pContext->m_rowsCount && bullet->getPos().cellY >= 0) )
	{
		/* check others defined in AddActor	*/
		AddActor(bullet);
	}	
}

bool GameEngine::isCellFree(int cellX,int cellY)
{
	if (m_gameField[cellX][cellY])	return false;
	else							return true;
}

void GameEngine::RemoveActor(std::shared_ptr<Wall> wall)
{
	if (wall)
	{
		/*	find wall in collection	*/
		auto found = std::find_if(m_walls.begin(),m_walls.end(),[&wall](const std::shared_ptr<Wall>& curWall) 
		{
			return curWall->getPos() == wall->getPos();
		});
		
		if (found != m_walls.end() && isMe(wall->getPos().cellX,wall->getPos().cellY,wall))
		{
			/*	if found and gameCell is	*/
			m_walls.erase(found);
			m_gameField[wall->getPos().cellX][wall->getPos().cellY] = nullptr;
		}		
	}
}

bool GameEngine::isMe(int cellX, int cellY, std::shared_ptr<Object> obj)
{
	if (m_gameField[obj->getPos().cellX][obj->getPos().cellY] == obj)	return true;
	else																return false;
}

void GameEngine::GameStep()
{
	for (auto it = m_guards.begin(); it != m_guards.end(); ++it)	MoveActor(it);

	size_t count = 0;
	for (; count < m_bullets.size(); ++count)
	{
		auto it = m_bullets.begin();
		MoveActor(it);
	}
		
	/*	shoot cannon	*/
	for (auto it = m_cannons.begin(); it != m_cannons.end();++it)	MoveActor(it);
	MoveHero();
}

void GameEngine::FillRenderObjects(std::list< std::shared_ptr<Object> >& collection)
{
	collection.clear();
	collection.insert(collection.end(),m_bullets.begin(),m_bullets.end());
	collection.insert(collection.end(),m_cannons.begin(),m_cannons.end());
	collection.insert(collection.end(),m_walls.begin(),m_walls.end());		
	collection.insert(collection.end(),m_guards.begin(),m_guards.end());		
	collection.push_back(m_hero);

	collection.sort([](const std::shared_ptr<Object>& a,const std::shared_ptr<Object>& b) -> bool
	{
			return a->getDeep() < b->getDeep();
	});	
}

void GameEngine::ToggleWall(std::shared_ptr<Wall> wall)
{
	/* if cell isn't empty - addition prohibited	*/
	if (!checkPos(wall->getPos()))	return;
	std::shared_ptr<Wall> pFoundWall;
	auto actor = m_gameField[wall->getPos().cellX][wall->getPos().cellY];
	if (actor && (pFoundWall = std::dynamic_pointer_cast<Wall>(actor)))
	{
		RemoveActor(pFoundWall);
	}
	else if (m_walls.size() < 5 && 
			isCellFree(wall->getPos().cellX,wall->getPos().cellY))
	{
		/* if cell free and walls count less then 5 => add wall	*/
		AddActor(wall);
	}
}

bool GameEngine::checkPos(const Position& pos)
{
	auto pContext = GlobalContext::singleton();
	return (pos.cellX >= 0 && pos.cellX < pContext->m_columsCount) &&
		(pos.cellY >= 0 && pos.cellY < pContext->m_rowsCount);
}

void GameEngine::FillPath(const Position& from, const Position& to, std::list<Position>& path)
{
	std::shared_ptr<node>	root(new node);
	root->distance = 0;
	root->m_pos = from;

	std::vector< std::shared_ptr<node> >	Tree;
	std::vector< Position >					check;
	Tree.push_back(root);	
	check.push_back(from);

	std::shared_ptr<node>	result;
	for (int i(0);i < Tree.size();++i)
	{
		Position newPosition;		
		auto current = Tree[i];

		// SouthEast
		newPosition = Position(current->m_pos.cellX+1,current->m_pos.cellY);
		if (std::find(check.begin(),check.end(),newPosition) == check.end())
		{
			check.push_back(newPosition);
			result = Step(current,Tree,newPosition, to);
			if (result)	break;
		}

		// SouthWest
		newPosition = Position(current->m_pos.cellX,current->m_pos.cellY+1);
		if (std::find(check.begin(),check.end(),newPosition) == check.end())
		{
			check.push_back(newPosition);
			result = Step(current,Tree,newPosition, to);
			if (result)	break;
		}

		// NorthWest
		newPosition = Position(current->m_pos.cellX-1,current->m_pos.cellY);
		if (std::find(check.begin(),check.end(),newPosition) == check.end())
		{
			check.push_back(newPosition);
			result = Step(current,Tree,newPosition, to);
			if (result)	break;
		}


		// NorthEast
		newPosition = Position(current->m_pos.cellX,current->m_pos.cellY-1);
		if (std::find(check.begin(),check.end(),newPosition) == check.end())
		{
			check.push_back(newPosition);
			result = Step(current,Tree,newPosition, to);
			if (result)	break;
		}
	}	

	Tree.clear();
	path.clear();
	if (result)
	{			
		auto tmpPtr = result;
		do 
		{
			path.push_front(tmpPtr->m_pos);
			tmpPtr = tmpPtr->m_parent;
		}
		while(tmpPtr);
	}
}
std::shared_ptr<node> GameEngine::Step(std::shared_ptr<node> parent, std::vector< std::shared_ptr<node> >& Tree, 
		Position newPosition, const Position& finishPosition)
{
	std::shared_ptr<Wall> pWall;
	/* out of board	*/
	if (!checkPos(newPosition)) return nullptr;

	auto actor = m_gameField[newPosition.cellX][newPosition.cellY];
	/* cant walk to wall */
	if	(pWall = std::dynamic_pointer_cast<Wall>(actor))
	{
		if (newPosition == finishPosition)	return parent;
		else								return nullptr;
	}
	std::shared_ptr<node> newNode(new node);
	newNode->distance	= parent->distance+1;
	newNode->m_parent	= parent;
	newNode->m_pos		= newPosition;	
	parent->m_childs.push_back(newNode);
	Tree.push_back(newNode);
	if (newPosition == finishPosition)	return newNode;
	return nullptr;
}

void GameEngine::AddActor(std::shared_ptr<Guard> guard)
{	
	std::list<Position> path;
	FillPath(guard->m_start, guard->m_finish, path);	
	guard->SetPath(path);
	m_guards.push_back(guard);
}

void GameEngine::MoveActor(std::list< std::shared_ptr<Guard> >::iterator guardIt)
{
	Position nextPos;
	std::shared_ptr<Wall> pWall;
	std::shared_ptr<Bullet> pBullet;
	std::shared_ptr<Hero> pHero;
	std::list<Position> path;
	auto pContext = GlobalContext::singleton();
	auto guard = *guardIt;
	m_gameField[guard->getPos().cellX][guard->getPos().cellY] = nullptr;
		
	if (guard->NextPosition(nextPos))
	{
		auto actor = m_gameField[nextPos.cellX][nextPos.cellY];
		if ( pWall =	std::dynamic_pointer_cast<Wall>(actor))
		{
			/*	if wall appears - reset path	*/
			FillPath(guard->getPos(), guard->m_finish, path);	
			guard->SetPath(path);
		}
		else if (pBullet =	std::dynamic_pointer_cast<Bullet>(actor))
		{
			RemoveActor(pBullet);
		}
		else if ( pHero = std::dynamic_pointer_cast<Hero>(actor))
		{
			throw LoseException();
		}
	}
	else
	{
		guard->SwitchDestination();
		FillPath(guard->getPos(), guard->m_finish, path);
		guard->SetPath(path);
	}
	guard->Move();
	m_gameField[guard->getPos().cellX][guard->getPos().cellY] = guard;
}

void GameEngine::RemoveActor(std::shared_ptr<Bullet> bullet)
{
	if (bullet)
	{
		/*	find wall in collection	*/
		auto found = std::find_if(m_bullets.begin(),m_bullets.end(),[&bullet](const std::shared_ptr<Bullet>& curBullet) 
		{
			return curBullet->getPos() == bullet->getPos();
		});
		
		if (found != m_bullets.end() && isMe(bullet->getPos().cellX,bullet->getPos().cellY,bullet))
		{
			/*	if found and gameCell is	*/
			m_bullets.erase(found);
			m_gameField[bullet->getPos().cellX][bullet->getPos().cellY] = nullptr;
		}		
	}
}

void GameEngine::AddActor(std::shared_ptr<Hero> hero)
{
	std::list<Position> path;	
	m_hero = hero;
}

void GameEngine::MoveHero()
{	
	Position nextPos;
	std::shared_ptr<Wall> pWall;
	std::shared_ptr<Guard> pGuard;
	std::shared_ptr<Bullet> pBullet;
	std::list<Position> path;
	auto pContext = GlobalContext::singleton();
	auto hero = m_hero;
	if (!checkPos(hero->GetDestination()))	return;
	m_gameField[hero->getPos().cellX][hero->getPos().cellY] = nullptr;

	if (hero->NextPosition(nextPos))
	{
		auto actor = m_gameField[nextPos.cellX][nextPos.cellY];
		if ( pWall =	std::dynamic_pointer_cast<Wall>(actor))
		{
			/*	if wall appears - reset path	*/
			FillPath(hero->getPos(), hero->GetDestination(), path);	
			hero->SetPath(path);
		}
		else if ( (pBullet =	std::dynamic_pointer_cast<Bullet>(actor)) ||
				(pGuard = std::dynamic_pointer_cast<Guard>(actor)))
		{
			hero->Move();
			throw LoseException();
		}
		else if (nextPos == Position(0,0))
		{
			hero->Move();
			throw WinException();
		}
	}
	else if (hero->getPos() != hero->GetDestination())
	{
		FillPath(hero->getPos(), hero->GetDestination(), path);
		hero->SetPath(path);
	}
	hero->Move();
	m_gameField[hero->getPos().cellX][hero->getPos().cellY] = hero;
}

void GameEngine::Clear()
{
	auto pContext = GlobalContext::singleton();
	m_cannons.clear();
	m_bullets.clear();
	m_walls.clear();
	m_guards.clear();
	m_hero.reset();
	m_gameField.clear();
	m_gameField.resize(pContext->m_rowsCount, std::vector<std::shared_ptr<Object> >(pContext->m_columsCount,nullptr));
}