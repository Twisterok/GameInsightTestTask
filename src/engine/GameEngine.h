#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

// own includes
#include <objects/actors/others/Cannon.h>
#include <objects/actors/others/Bullet.h>
#include <objects/actors/others/Wall.h>
#include <objects/actors/characters/Guard.h>
#include <objects/actors/characters/Hero.h>
#include <utils/node.h>

//std includes
#include <list>

class GameEngine
{
public:

	GameEngine();
	void Clear();

	void AddActor(std::shared_ptr<Cannon> cannon);
	void AddActor(std::shared_ptr<Bullet> bullet);
	void AddActor(std::shared_ptr<Wall> wall);
	void AddActor(std::shared_ptr<Guard> guard);
	void AddActor(std::shared_ptr<Hero> hero);

	void RemoveActor(std::shared_ptr<Wall> wall);
	void RemoveActor(std::shared_ptr<Bullet> bullet);
	

	void MoveActor(std::list< std::shared_ptr<Cannon> >::iterator cannon);
	void MoveActor(std::list< std::shared_ptr<Bullet> >::iterator bullet);
	void MoveActor(std::list< std::shared_ptr<Guard> >::iterator guard);
	void MoveHero();

	void ToggleWall(std::shared_ptr<Wall> wall);

	bool isCellFree(int cellX, int cellY);

	void GameStep();
	void FillRenderObjects(std::list< std::shared_ptr<Object> >& collection);	

	std::shared_ptr<Hero> GetHero() { return m_hero; }

private:
	
	bool checkPos(const Position& pos);
	bool isMe(int cellX, int cellY, std::shared_ptr<Object> obj);

	/*	PathFinder	*/
	void FillPath(const Position& from, const Position& to, std::list<Position>& path);
	std::shared_ptr<node> Step(std::shared_ptr<node> parent, std::vector< std::shared_ptr<node> >& Tree, 
			Position newPosition, const Position& finishPosition);
	//	PathFinder

	std::list< std::shared_ptr<Cannon> >	m_cannons;
	std::list< std::shared_ptr<Bullet> >	m_bullets;
	std::list< std::shared_ptr<Wall> >		m_walls;
	std::list< std::shared_ptr<Guard> >		m_guards;
	std::shared_ptr<Hero>					m_hero;

	std::vector< std::vector< std::shared_ptr<Object> > >	m_gameField;
};

#endif