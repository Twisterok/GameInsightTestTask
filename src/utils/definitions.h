#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__


namespace Direction
{
	const int FORWARD = 0;
	const int REVERSE = 1;
}

namespace MoveDirection
{
	const int NorthWest					= 0;
	const int NorthEast					= 1;
	const int SouthEast					= 2;
	const int SouthWest					= 3;
	const int Stop						= 4;
}

namespace ButtonClickEvent
{
	const int LEFT_BUTTON_CLICK			= 1;
	const int LEFT_BUTTON_DOUBLE_CLICK	= 2;
	const int MIDDLE_BUTTON_CLICK		= 0;
	const int RIGHT_BUTTON_CLICK		= -1;
	const int RIGHT_BUTTON_DOUBLE_CLICK	= -2;			
}

namespace RenderLayer
{
	const int LAYER_COMMON		= 1;
	const int LAYER_CHARACTER	= 2;
	const int LAYER_BULLET		= 2;
	const int LAYER_WALL		= 2;
}

namespace globals
{
	const int EPSILON			= 0.0001;

}


#endif