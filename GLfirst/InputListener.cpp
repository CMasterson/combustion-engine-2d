#include "precompiled.h"
#include "InputListener.h"


InputListener* InputListener::instance = NULL;
InputListener* InputListener::Instance()
{
	if(!instance)
		instance = new InputListener();
	return instance;	
}
InputListener::InputListener(void)
{}
InputListener::~InputListener(void)
{}
void InputListener::Initialise(HWND *HWnd)
{
	this->mouseState = new MouseState();
	this->hWnd = HWnd;
	string keyName = "0";
	string endChar = "9";
	int current = 0x30;
	for(int i = 0; i < 2; i++)//Add Number+char  Keys
	{
		for(;keyName[0] <= endChar[0];current++,keyName[0]++)
		{
			this->AddKey(current,keyName);
		}
		if(keyName[0] == '9'+1)
		{
			keyName = "A";
			endChar = "Z";
			current = 0x41;
		}
	}
	//Add FKeys (awkwardness!)
	keyName = "F1";
	current = VK_F1;
	for(int i = 1;current <= VK_F12;current++, i++)
	{
		stringstream ss;
		ss << i;
		this->AddKey(current,"F" + ss.str());
	}
	//Add arrow Keys
	keyName = "Arrow";
	current = VK_LEFT;
	for(;current<=VK_DOWN;current++)
	{
		string append;
		switch(current)
		{
			case VK_LEFT:
					append = "Left";
				break;
			case VK_UP:
					append = "Up";
				break;
			case VK_RIGHT:
					append = "Right";
				break;
			case VK_DOWN:
					append = "Down";
				break;
		}
		this->AddKey(current,keyName+append);
	}
	//Add other keys (SPACE, TAB, CRTL etc.)
	this->AddKey(VK_ESCAPE,"Escape");
	this->AddKey(0x08,"Backspace");
	this->AddKey(0xDC,"Backslash");
	this->AddKey(VK_TAB,"Tab");
	this->AddKey(VK_SHIFT,"Shift");
	this->AddKey(VK_CONTROL,"Ctrl");
	this->AddKey(VK_MENU,"Alt");
	this->AddKey(VK_SPACE,"Space");
	this->AddKey(VK_RETURN,"Enter");

}
void InputListener::UpdateKeyboard()
{
	vector<KeyboardKey*>::iterator current;
	for(current = this->keys.begin();current < this->keys.end();current++)
	{
		bool keyPressed = GetAsyncKeyState((*current)->keyCode);
		if(keyPressed)
		{
			if((*current)->keyState == KEY_STATE_INACTIVE || (*current)->keyState == KEY_STATE_RELEASED)
				(*current)->keyState = KEY_STATE_PRESSED;
			else if ((*current)->keyState == KEY_STATE_PRESSED)
				(*current)->keyState = KEY_STATE_HELD;
		}
		else
		{
			if((*current)->keyState == KEY_STATE_PRESSED || (*current)->keyState == KEY_STATE_HELD)
				(*current)->keyState = KEY_STATE_RELEASED;
			else if((*current)->keyState == KEY_STATE_RELEASED)
				(*current)->keyState = KEY_STATE_INACTIVE;
		}
	}	
}
void InputListener::UpdateMouse()
{
	this->mouseState->position = this->GetMousePos();
	this->mouseState->leftMouseButtonState = this->GetMouseButtonState("LEFT", this->mouseState);
	this->mouseState->rightMouseButtonState = this->GetMouseButtonState("RIGHT", this->mouseState);
	this->mouseState->timeStamp = GetTickCount();
}

Vector2 InputListener::GetMousePos()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	Vector2 mPos = Vector2(cursorPos.x,cursorPos.y);
	RECT windowRect, clientRect;
	GetWindowRect(*hWnd, &windowRect);
	GetClientRect(*hWnd, &clientRect);
	mPos = mPos - Vector2(windowRect.left, windowRect.top);
	int xDiff = windowRect.right - windowRect.left - clientRect.right;
	int yDiff = windowRect.bottom - windowRect.top - clientRect.bottom;
	mPos.X -= xDiff/2 - 1;
	mPos.Y -= yDiff-xDiff/2;
	mPos = GetOGLPos((int)mPos.X, (int)mPos.Y);
	
	return mPos;
}
Vector2 InputListener::GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return Vector2(posX, posY);
}
void InputListener::SetMouseVelocity(MouseState* MState)
{
	if(this->mouseState->timeStamp)
	{
		Vector2 oldPosition = this->mouseState->position;
		Vector2 newPosition = MState->position;
		Vector2 difference = oldPosition - newPosition;
		MState->velocity = difference / (float)((MState->timeStamp - this->mouseState->timeStamp) / CLOCKS_PER_SEC);
	}
	else
		MState->velocity = Vector2();

}
int InputListener::GetMouseButtonState(string mouseButton, MouseState* newState)
{
	int state = KEY_STATE_INACTIVE;
	bool pressed = false;
	MouseState * lastMouseState = this->mouseState;
	if(lastMouseState)
	{
		int lastButtonState;

		if(mouseButton == "LEFT")
		{
			pressed = GetAsyncKeyState(VK_LBUTTON);
			lastButtonState = lastMouseState->leftMouseButtonState;
		}		
		else if(mouseButton == "RIGHT")
		{
			pressed = GetAsyncKeyState(VK_RBUTTON);
			lastButtonState = lastMouseState->rightMouseButtonState;
		}
	
		if(pressed)
		{
			if(lastButtonState == KEY_STATE_PRESSED || lastButtonState == KEY_STATE_HELD || lastButtonState == KEY_STATE_DRAG)
			{
				if(lastMouseState->position == newState->position)
					state = KEY_STATE_HELD;
				else
					state = KEY_STATE_DRAG;
			}
			else if(lastButtonState == KEY_STATE_INACTIVE || lastButtonState == KEY_STATE_RELEASED)
				state = KEY_STATE_PRESSED;
		}
		else
		{
			if(lastButtonState == KEY_STATE_PRESSED || lastButtonState == KEY_STATE_HELD || lastButtonState == KEY_STATE_DRAG)
				state = KEY_STATE_RELEASED;
		}
		//Set the timeStamp of the beginning of the state
		if(state != lastButtonState)
		{
			if(mouseButton == "LEFT")
				newState->leftMouseButtonStateTime = GetTickCount();
			else if(mouseButton == "RIGHT")
				newState->rightMouseButtonStateTime = GetTickCount();
		}
		else
		{
			if(mouseButton == "LEFT")
				newState->leftMouseButtonStateTime = lastMouseState->leftMouseButtonStateTime;
			else if(mouseButton == "RIGHT")
				newState->rightMouseButtonStateTime = lastMouseState->rightMouseButtonStateTime;
		}

	}
	else
	{
		if(pressed)
			state = KEY_STATE_PRESSED;
	}
	return state;
}
void InputListener::AddKey(int keyCode, string keyName)
{
	KeyboardKey *key = new KeyboardKey();
	key->keyCode = keyCode;
	key->keyName = keyName;
	key->keyState = KEY_STATE_INACTIVE;
	this->keys.push_back(key);
}
KeyboardKey* InputListener::keyForKeyName(string keyName)
{
	vector<KeyboardKey*>::iterator current = this->keys.begin();
	while((*current)->keyName != keyName)
	{
		if(current == this->keys.end())
			return NULL;
		else
			current++;
	}
	return *current;
}