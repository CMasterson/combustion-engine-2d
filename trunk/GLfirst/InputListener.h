#pragma once
#include "KeyboardKey.h"
#include "MouseState.h"

class InputListener
{
private:
	static InputListener * instance;
	HWND *hWnd;
public:
	
	InputListener();
	~InputListener(void);

	static InputListener* Instance();
	void Initialise(HWND *HWnd);
	vector<KeyboardKey*> keys;
	MouseState *mouseState;

	void UpdateKeyboard();
	void UpdateMouse();
	void CleanupMouseActions();
	Vector2 GetMousePos();
	Vector2 GetOGLPos(int x, int y);
	void SetMouseVelocity(MouseState* MState);
	int GetMouseButtonState(string mouseButton, MouseState* newState);
	void AddKey(int keyCode, string keyName);
	KeyboardKey* keyForKeyName(string keyName);
};
