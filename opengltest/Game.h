#pragma once
#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"
#include "Sprite.h"
#include "MapLoader.h"
#include "HorizontalScrollingBackground.h"
#include "Timer.h"
#include <algorithm>
#include <cmath>
#include "Vector2.h"
#include "ColisionManager.h"
#include "TileManager.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Menu.h"
#include "ScriptReader.h"
//
#include "Controller.h"
#include "Dialog.h"

/* these are enumerated types (just names) of game states
   that the game can be in at any moment.  These help you
   manage the flow of the game.  Especially if you want 
   to do different updates (call different update functions)
   or have different behaviour for input (i.e. mouse and keyboard
   functions might have different behaviour in-game (STATE_GAMEPLAY)
   versus when in the Menu (STATE_MAINMENU)
*/
enum {
	STATE_GAMEPLAY=0, 
	STATE_MAINMENU, 
	STATE_CREDITS,
	STATE_PAUSE
};

// input information related to mouse
// you could add keyboard info in here too if you need to know if a key is currently pressed down
typedef struct _InputInfo
{
	bool mouseDown; // is the mouse down?
	int button; // which mouse button
	float clickX,clickY; // where the mouse was clicked
	float currentX,currentY;
}InputInfo;

// convenience structure to hold rgb values
typedef struct _RGBColor
{
	float red,green,blue;
}RGBColor;

// GameStateInfo
// this stores anything related to the state of the game
// i.e. what level are we on?, what is the score? etc.
typedef struct _GameStateInfo
{
	int gameState; // the game state, see enum's above
	RGBColor bgClearColor; // the default clear color of the background

	// window width/height are the actual size of the window
	int windowWidth, windowHeight;

	// screen width/height are the apparent size of the window
	// i.e. you can have a 640x480 game screen stretched to 1280x1024
	// your calculations for actual pixel locations will depend on the ratio
	//   between screen and window width/height
	int screenWidth, screenHeight;

	float ratioWidth,ratioHeight;
}GameStateInfo;

/* 
 * Game.h
 * This is the main Game class of the base sprite lib starter code
 * it handles input, game loop update, display
 */
class Game
{
public:
	static Game* instance()
	{
		static Game *instance = new Game();
		return instance;
	}
	/* initialization */
	~Game(void);
	void initializeGame();
	void QuitGame();

	/* convenience functions */
	// screen size is the apparent size in pixels
	// i.e. this is what your game calculations should use
	void setScreenSize(int w, int h)
	{
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
	}
	// sets the screen-to-window pixel coordinates ratio
	void updateScreenRatio()
	{
		stateInfo.ratioWidth = stateInfo.screenWidth/(float)stateInfo.windowWidth;
		stateInfo.ratioHeight = stateInfo.screenHeight/(float)stateInfo.windowHeight;
		/* these are only really used for the mouse function
		   to get actual screen pixel coordinates from the window coordinates */
	}

	// sets the window size in pixels for the window itself
	void setNewWindowSize(int width,int height)
	{
		stateInfo.windowWidth = width;
		stateInfo.windowHeight = height;
	}

	float getFPS()
	{
		frame++;
		time = glutGet(GLUT_ELAPSED_TIME);
		if (time - timebase > 1000)
		{
			fps = frame * 1000.0 / (time - timebase);
			timebase = time;
			frame = 0;
		}
		return fps;
	}

	// add a sprite to the draw list
	// only sprites in the draw list will be drawn
	void addSpriteToDrawList(Sprite *s);

	/* draw/rendering routines */
	void draw(); // called from the main

	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void DrawMainMenu();
	void PostDraw(); // cleanup and prepare for next frame
	
	void drawSprites(); // draw the sprite list
	void drawTestPrimitives(); // test function

	/* update routines, the game loop */
	void update(); // called from main frequently

	/* input callback functions */
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);
	void GameOver();

	/*********************************/
	/* DATA */
	/*********************************/
	
	/* game state info */
	GameStateInfo stateInfo;

	/* individual sprites to manipulate by name */
	Sprite *animatedSprite;
	Sprite *animatedSprite2;

	InputInfo input;

	/* sprite list to draw */
	std::vector<Sprite*> spriteListToDraw;
	
	/* you could have more lists of sprite pointers */
	/* such as spritesToUpdateForPhysics  
	   or      spritesToUpdateForCollisions 
	   etc....
    */

	/* timer's for rendering and animation/physics update */
	Timer *renderingTimer;
	Timer *updateTimer; // for physics/collisions etc.


	void ModScore(int mod) { score += mod; }
	
private:
	Game(void);
	int frame = 0, time, timebase = 0, fps = 0;
	float fTime = 0, delay = 0;
	MenuClass* mainMenu;
	Camera* viewCam;
	TileManager* tileManager;
	EntityManager* entityManager;
	ProjectileManager* projectileManager;
	int prevHp;
	float flashDur = 1000.f;
	float nrgFlashDur = 1000.f;
	ColisionManager* colisionManager;
	MapLoader* mapLoader;
	Sprite *hpBar, *energyBar, *hpBG, *s_Score, *s_Time, *entBarSprite;
	Sprite *energyFlash, *healthFlash;
	Script* script;
};

#endif