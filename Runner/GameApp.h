#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

//////////////////////////////////////////////////////////////////////////
//							GameApp.h
//
//	This is what drives the whole game. In here, you derive your class
//	from SexyAppBase and implement common game tasks, such as 
//	responding to widgets (covered later), initializing and loading
//	resources, setting up the various game screens, etc.
//	All applications at minimum must have a class that derives from
//	SexyAppBase.
//
//	The GameApp class is used to do such things as create the main 
//	menu screen, create the main game class (where all drawing/updating/
//	interaction takes place), etc.
//////////////////////////////////////////////////////////////////////////

#include "SexyAppFramework/SexyAppBase.h"
#include <memory>
#include <functional>

// We place all our classes inside the "Sexy" namespace to avoid name collisions
// with other libraries that might be added.
namespace Sexy
{

	// The GameApp class will be responsible for creating a class by the name
	// of "Board", which we will use to do all the game's drawing, input processing,
	// etc. Board is the second most important class and is where almost all of your
	// game logic code will originate from. It is a widget, which allows for
	// easy and automatic invocation of its update, drawing, and input processing
	// functions. See the "Board" class for more details. 
	class Board;

	class Image;

class GameApp : public SexyAppBase
{

	private:

		std::unique_ptr<Board> mBoard;

	public:

		std::shared_ptr<Image>	mGround;
		std::shared_ptr<Image>	mWall;
		std::shared_ptr<Image>	mGunImage;
		std::shared_ptr<Image>	mBullet;
		std::shared_ptr<Image>	mGuard;
		std::shared_ptr<Image>	mHero;
		std::shared_ptr<Image>	mFinishFlag;

		GameApp();
		virtual ~GameApp();
		virtual void	Init();
		virtual void	LoadingThreadProc();
		virtual void	LoadingThreadCompleted();
		virtual void	ButtonPress(int theId);

};

}


#endif	// __GAMEAPP_H__
