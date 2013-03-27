#include "precompiled.h"
#include "TextureManager.h"
#include "ShapeManager.h"
#include "EntityManager.h"
#include "InputListener.h"

//=====
#include "Player.h"
#include "AsteroidManager.h"
#include "GameNodeManager.h"
#include "Asteroid.h"
#include "Spring.h"
#include "Entity.h"
#include "Node.h"
#include "Shape.h"
//=====

#define DEBUG

HWND    hWnd;
HDC     hDC;
HGLRC   hRC;

//The Game loop boolean, if true the game loops, if false the game stops
bool loopMore = true;
//Time of last frame
float lastTimeStamp;
float zoom;

//====
Shape *reticle;
Player *player;
Entity * collideShape;
//====
//Functions
void GameEnd();
	
float randFloat(float);
float randFloat(float,float);
float getDeltaT();

Vector2* LineIntersection(Vector2* firstStart, Vector2* firstEnd, Vector2* secondStart, Vector2* secondEnd);

//Game Setup
void GameInit()
{
	ShowCursor(true);
	srand ( time(NULL) );
	IListener->Initialise(&hWnd);
	SManager->Initialise();
	TManager->Initialise();
	EManager->Initialise();
	AManager->Initialise();

	lastTimeStamp = GetTickCount();

	#ifdef DEBUG
	SManager->debug = true;
	#endif

	//AManager->CreateAsteroid(Vector2(5,5));

	//==
	collideShape = new Entity();
	collideShape->vertices.push_back(Vector2(-10,10));
	collideShape->vertices.push_back(Vector2(10,10));
	collideShape->vertices.push_back(Vector2(10,-10));
	collideShape->vertices.push_back(Vector2(-10,-10));

	collideShape->texture = TManager->TextureForName("sprites/archer.tga");

	collideShape->position = Vector2(10,0);
	collideShape->mass = 10;

	GNManager->RootNode()->AddChild(collideShape);
	//==
/*
	player = new Player();
	GNManager->RootNode()->AddChild(player);
	EManager->AddEntity(player);

	reticle = new Shape(Vector2(),"reticle.tga");

	reticle->vertices.push_back(Vector2(-1,1));
	reticle->vertices.push_back(Vector2(1,1));
	reticle->vertices.push_back(Vector2(1,-1));
	reticle->vertices.push_back(Vector2(-1,-1));

	AManager->CreateAsteroid(Vector2(5,5));

	GNManager->RootNode()->AddChild(reticle);
	
	Entity *springStart = player;
	Entity *springEnd = new Entity();
	Spring* nSpring;

//===
	for(int i = 0; i < 10; i++)
	{
		GNManager->RootNode()->AddChild(springEnd);
		EManager->AddEntity(springEnd);

		springEnd->position = springStart->position + Vector2(1,0);

		springEnd->mass = 0.2;

		springEnd->vertices.push_back(Vector2(-1,1));
		springEnd->vertices.push_back(Vector2(1,1));
		springEnd->vertices.push_back(Vector2(1,-1));
		springEnd->vertices.push_back(Vector2(-1,-1));
//===
		nSpring = new Spring();
		nSpring->CoDamping = 0.1;
		nSpring->end = springEnd;
		nSpring->idealLength = 2;
		nSpring->start = springStart;
		nSpring->tightness = 5;
		nSpring->breakForce = 10000;

		EManager->springs.push_back(nSpring);

		springStart = springEnd;
		springEnd = new Entity();
	}
//===
	*/
}
//GameLogic
void GameUpdate()
{
	IListener->UpdateKeyboard();
	IListener->UpdateMouse();
	if(IListener->keyForKeyName("Escape")->keyState == KEY_STATE_PRESSED)
		GameEnd();

//	reticle->position = IListener->GetMousePos();
//	reticle->rotation = player->rotation;
//	AManager->Asteroids.front()->rotation += 1;
	GNManager->Update(getDeltaT());
	EManager->UpdateEntities();
}
//GameCleanup
void GameEnd()
{
	loopMore = false;
}


//returns the frame time in seconds
float getDeltaT()
{
	float deltaT = GetTickCount() - lastTimeStamp;
	lastTimeStamp = GetTickCount();
	return deltaT/CLOCKS_PER_SEC;
}
//Draw Debug Content
void DrawDebug()
{
	//glLoadIdentity();
    //glTranslated(0, 0, -10);

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glBegin(GL_LINES);

	glColor4f(0.5,0.5,0.5,1);

	for(int i = 0; i < 2000; i++) // Change this to draw only on visable space
	{
		glVertex3f(-1000 + 10 * i, 1000, 1);
		glVertex3f(-1000 + 10 * i, -1000, 1); 

		glVertex3f(1000, -1000 + 10 * i, 1);
		glVertex3f(-1000, -1000 + 10 * i, 1);
	}
	
	glColor4f(1,0,0,1);
	glVertex3f(0,0,1);
	glColor4f(1,0,0,1);
	glVertex3f(1,0,1);
	
	glColor4f(0,1,0,1);
	glVertex3f(0,0,1);
	glColor4f(0,1,0,1);
	glVertex3f(0,1,1);

	glColor4f(0,0,1,1);
	glVertex3f(0,0,1);
	glColor4f(0,0,1,1);
	glVertex3f(0,0,2);

	//glColor4f(1,1,1,1);
	//glVertex3f(0,0,1);
	//glVertex3f(player->GetWorldPosition().X,player->GetWorldPosition().Y,1);


	glColor4f(0,1,1,1);
	list<Spring*>::iterator iter = EManager->springs.begin();
	for(;iter != EManager->springs.end();iter++)
	{
		glVertex3f((*iter)->start->GetWorldPosition().X,(*iter)->start->GetWorldPosition().Y,1);
		glVertex3f((*iter)->end->GetWorldPosition().X,(*iter)->end->GetWorldPosition().Y,1);
	}
	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

// Set up pixel format for graphics initialization
void SetupPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 16;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    pixelformat = ChoosePixelFormat(hDC, ppfd);
    SetPixelFormat(hDC, pixelformat, ppfd);
}

// Initialize OpenGL graphics
void InitGraphics()
{
    hDC = GetDC(hWnd);

    SetupPixelFormat();

    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);
    glClearColor(0.2, 0.2, 0.2, 0);
    glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
}
// Resize graphics to fit window
void ResizeGraphics()
{
    // Get new window size
    RECT rect;
	int width, height;
	GLfloat aspect;

    GetClientRect(hWnd, &rect);
    width = rect.right;
    height = rect.bottom;
    aspect = (GLfloat)width / height;

    // Adjust graphics to window size
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0, aspect, 1.0, 100.0)
	width /= 20;
	height /= 20;
	glOrtho(-width, width, -height, height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
	//UpdateProjection(GL_TRUE);
}

// Draw frame
void DrawGraphics()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set location in front of camera
    glLoadIdentity();
    glTranslated(0, 0, -10);
	//glTranslatef(-player->position.X,-player->position.Y,-10);

    // Draw shapes

	#ifdef DEBUG
		DrawDebug();
	#endif

	//SManager->DrawShapes();
	GNManager->RootNode()->Node::Draw();
    // Show the new scene
    SwapBuffers(hDC);
}

// Handle window events and messages
LONG WINAPI MainWndProc (HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam)
{
    switch (uMsg)
    {
    case WM_SIZE:
        ResizeGraphics();
        break;

    case WM_CLOSE: 
        DestroyWindow(hWnd);
        break;
 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
 
    // Default event handler
    default: 
        return DefWindowProc (hWnd, uMsg, wParam, lParam); 
        break; 
    } 
 
    return 1; 
}

// Main function
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    const LPCWSTR appname = TEXT("Combustion Engine V00.00.01a");

    WNDCLASS wndclass;
    MSG      msg;
 
    // Define the window class
    wndclass.style         = 0;
    wndclass.lpfnWndProc   = (WNDPROC)MainWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon(hInstance, appname);
    wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = appname;
    wndclass.lpszClassName = appname;
 
    // Register the window class
    if (!RegisterClass(&wndclass)) return FALSE;
 
    // Create the window
    hWnd = CreateWindow(
            appname,
            appname,
            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            800,
            600,
            NULL,
            NULL,
            hInstance,
            NULL);
 
    if (!hWnd) return FALSE;

    // Initialize OpenGL
    InitGraphics();

    // Display the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	GameInit();
    // Event loop
    while (loopMore)
    {
		//GameLogic
		GameUpdate();
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
        {
            if (!GetMessage(&msg, NULL, 0, 0)) return TRUE;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        DrawGraphics();

	}
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

