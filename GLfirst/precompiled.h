#ifndef PRECOMPILED_H
#define PRECOMPILED_H
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>
#include <mmsystem.h>
#include <cmath>
#include <stdio.h> 
#include <string.h>
#include <fstream>
#include <iostream>
#include <math.h>						// Header File For Windows Math Library		( ADD )
#include <stdio.h>						// Header File For Standard Input/Output	( ADD )
#include <stdarg.h>						// Header File For Variable Argument Routines	( ADD )
#include <time.h>
//#include "GLwindow.h"
#include "Vector2.h"
#define PI 3.14159
#define TO_RADIANS (PI/180)
#define TO_DEGREES (180/PI)
#define MAX_ROTATION 360
#define BITMAP_ID 0x4D42				// the universal bitmap ID
// State for keyboard and mouse input
#define KEY_STATE_INACTIVE 0			// Not pressed
#define KEY_STATE_PRESSED 1				// Pressed this tick
#define KEY_STATE_HELD 2				// Pressed last tick or earlier, not released
#define KEY_STATE_DRAG 3				// Held but moved (mouse only, probably)
#define KEY_STATE_RELEASED 4			// Released this tick

//Convenience Defines
#define IListener InputListener::Instance()
#define SManager ShapeManager::Instance()
#define GNManager GameNodeManager::Instance()
#define EManager EntityManager::Instance()
#define AManager AsteroidManager::Instance()
#define TManager TextureManager::Instance()


#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <time.h>

using namespace std;


#endif