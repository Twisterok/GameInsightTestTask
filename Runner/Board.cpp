#include "Board.h"
#include "GameApp.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/ImageFont.h"
#include "SexyAppFramework/DDImage.h"
#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/DialogButton.h"

#include <context/GlobalContext.h>
#include <objects/common/Ground.h>
#include <factory/CannonFactory.h>
#include <objects/actors/others/Wall.h>
#include <objects/actors/characters/Guard.h>
#include <objects/actors/characters/Hero.h>
#include <utils/utils.h>
#include <utils/LoseException.h>
#include <utils/WinException.h>

using namespace Sexy;

Board::Board(GameApp* theApp)
{
	mApp = theApp;
	Reset();
}

Board::~Board()
{
}

void Board::Update()
{
	Widget::Update();	
	if (mGaveOver)	return;
	try
	{
		mEngine.GameStep();
	}
	catch (WinException& ex)
	{
		mApp->PlaySample(1);
		auto response =mApp->DoDialog(1, true, _S("VICTORY"), 
					_S("VICTORY!"),
					_S("OK"), Dialog::BUTTONS_FOOTER);		
		Reset();
	}
	catch (LoseException& ex)
	{		
		mApp->PlaySample(2);
		mApp->DoDialog(1, true, _S("You lost"), 
					_S("You lost!"),
					_S("OK"), Dialog::BUTTONS_FOOTER);		
		Reset();
	}

	MarkDirty();
}

void Board::Draw(Graphics* g)
{	
	g->SetColor(Color(69, 115, 95));
	g->FillRect(0, 0, mWidth, mHeight);
	g->SetColor(Color(0, 255, 0));

	auto pContext = GlobalContext::singleton();	
	for (int j(0);j<pContext->m_rowsCount;++j)
	{
		for (int i(0);i<pContext->m_columsCount;++i)
		{		
			Ground grd(mApp->mGround,Position(i,j), (i+j) == 0 ? 1 : 3,1);
			grd.Draw(g);
		}
	}

	/*	Draw Flag	*/
	auto isoPos = utils::toIsometric(Position(-1,-1));
	g->DrawImage(mApp->mFinishFlag.get() , 
				Rect(isoPos.cellX - pContext->m_cellWidth,isoPos.cellY, pContext->m_cellWidth*2, pContext->m_cellHeight), 
				Rect(0,
					0,
					mApp->mFinishFlag->GetWidth(),
					mApp->mFinishFlag->GetHeight()));
	// Flag

	std::list< std::shared_ptr<Object> > renderObjects;
	mEngine.FillRenderObjects(renderObjects);

	for (auto it = renderObjects.begin(); it != renderObjects.end(); ++it)
	{
		(*it)->Draw(g);
	}
}
void Board::MouseUp(int x, int y, int theClickCount)
{
	Widget::MouseUp(x, y, theClickCount);

	auto pContext = GlobalContext::singleton();
	if (theClickCount == ButtonClickEvent::LEFT_BUTTON_CLICK)
	{
		Position isoPos(x,y);
		auto fromIso = utils::fromIsometric(isoPos);		
		mEngine.GetHero()->SetDestination(fromIso);
		mEngine.MoveHero();
	}
	else if (theClickCount == ButtonClickEvent::RIGHT_BUTTON_CLICK)
	{
		Position isoPos(x,y);
		auto fromIso = utils::fromIsometric(isoPos);		
		auto wall = std::shared_ptr<Wall>(new Wall(mApp->mWall,fromIso));
		mEngine.ToggleWall(wall);
	}
}
void	Board::Reset()
{
	mEngine.Clear();

	mGaveOver = false;
	mEngine.AddActor(CannonFactory::singleton()->MakeCannon(Position(-1,7)));
	mEngine.AddActor(CannonFactory::singleton()->MakeCannon(Position(11,-1)));
	mEngine.AddActor(CannonFactory::singleton()->MakeCannon(Position(21,-1)));
	mEngine.AddActor(CannonFactory::singleton()->MakeCannon(Position(-1,14)));
	mEngine.AddActor(CannonFactory::singleton()->MakeCannon(Position(-1,23)));
	
	std::shared_ptr<Guard> guard(new Guard(mApp->mGuard, Position(0,20), Position(20,15)));
	mEngine.AddActor(guard);

	guard.reset(new Guard(mApp->mGuard, Position(20,12), Position(8,8)));
	mEngine.AddActor(guard);

	guard.reset(new Guard(mApp->mGuard, Position(0,5), Position(5,0)));
	mEngine.AddActor(guard);

	std::shared_ptr<Hero> hero(new Hero(mApp->mHero,Position(29,29)));
	mEngine.AddActor(hero);	
}