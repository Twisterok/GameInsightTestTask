#ifndef __BOARD_H__
#define __BOARD_H__
#include "SexyAppFramework/Widget.h"
#include "SexyAppFramework/ButtonListener.h"

// own includes
#include <engine/GameEngine.h>

namespace Sexy
{
class Graphics;
class GameApp;

//////////////////////////////////////////////////////////////////////////
class Board : public Widget, public ButtonListener
{

	private:

		GameApp*	mApp;		
		GameEngine	mEngine;
		bool		mGaveOver;
		
	public:

		void		Reset();
		Board(GameApp* theApp);
		virtual ~Board();
		virtual void	Draw(Graphics* g);
		virtual void	Update();
		virtual void	MouseUp(int x, int y, int theClickCount);		
};


}

#endif // __BOARD_H__