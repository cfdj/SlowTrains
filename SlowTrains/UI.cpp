#include "UI.h"

UI::UI(Sprite* _state0, Sprite* _state1, Sprite* _state2, int _xPos, int _yPos)
{
	xpos = _xPos;
	ypos = _yPos;
	state0 = _state0;
	state1 = _state1;
	state2 = _state2;
}

void UI::render()
{
	switch (state) {
	case 0:
		state0->render(xpos,ypos);
		break;
	case 1:
		state1->render(xpos, ypos);
		break;
	case 2:
		state2->render(xpos, ypos);
		break;
	}
}

void UI::setState(int newState)
{
	state = newState;
}
