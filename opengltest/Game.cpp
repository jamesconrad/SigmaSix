#include "Game.h"
#include "drawPrimitives.h"
#include "Camera.h"

#define WINDOW_SCREEN_WIDTH 256
#define WINDOW_SCREEN_HEIGHT 196


int score;


/* this is called by std::sort to sort the list based on layerID
 *  for drawing in the proper order
 */
bool spriteSortingFunction(Sprite *s1, Sprite *s2)
{
	// return true if s1's layerID is less than s2's layerID
	return (s1->layerID < s2->layerID);
}

/* constructor */
Game::Game(void)
{
	stateInfo.bgClearColor.red = 0;
	stateInfo.bgClearColor.green = 0;
	stateInfo.bgClearColor.blue = 0;

	/* init state */
	stateInfo.gameState = STATE_MAINMENU;
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");

	//temp really need to make a "score time modifier"
	score = 10000;

	mainMenu = new MenuClass(1);
}

/* destructor */
Game::~Game(void)
{
	/* deallocate memory and clean up here. if needed */
}

/*
 * initializeGame()
 * - this function is called in the constructor to initialize everything related
 *   to the game, i..e loading sprites etc.
 * - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
 */
void Game::initializeGame()
{
	score = 100;
	hpBar = new Sprite;
	hpBG = new Sprite;
	energyBar = new Sprite;
	s_Score = new Sprite;
	s_Time = new Sprite;

	hpBar->loadSpriteSheet("assets/ui.png");
	SpriteSheetInfo bars = hpBar->sheet;

	viewCam = new Camera;
	tileManager = TileManager::instance();
	projectileManager = ProjectileManager::instance();
	entityManager = EntityManager::instance();
	mapLoader = MapLoader::instance();
	mapLoader->LoadMap(7);
	colisionManager = ColisionManager::instance();
	colisionManager->RebuildColisionMap();

	hpBG->sheet = bars;
	energyBar->sheet = bars;
	s_Score->sheet = bars;
	s_Time->sheet = bars;

	hpBG->setNumberOfAnimations(1);
	hpBG->setCurrentAnimation(0);
	hpBG->setSpriteFrameSize(528, 59);
	hpBG->addSpriteAnimFrame(0, 0, 53);

	hpBar->setNumberOfAnimations(1);
	hpBar->setCurrentAnimation(0);
	hpBar->setSpriteFrameSize(497, 22);
	hpBar->addSpriteAnimFrame(0, 8, 29);

	energyBar->setNumberOfAnimations(1);
	energyBar->setCurrentAnimation(0);
	energyBar->setSpriteFrameSize(427, 22);
	energyBar->addSpriteAnimFrame(0, 51, 0);

	s_Score->setNumberOfAnimations(1);
	s_Score->setCurrentAnimation(0);
	s_Score->setSpriteFrameSize(134, 24);
	s_Score->addSpriteAnimFrame(0, 0, 113);

	s_Time->setNumberOfAnimations(1);
	s_Time->setCurrentAnimation(0);
	s_Time->setSpriteFrameSize(91, 24);
	s_Time->addSpriteAnimFrame(0, 0, 146);
}

void Game::QuitGame()
{
	free(hpBar);
	free(hpBG);
	free(energyBar);
	free(s_Score);
	free(s_Time);
	free(viewCam);
}

/* draw()
 * - this gets called automatically about 30 times per second
 * - this function just draws the sprites
 */
void Game::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	if (stateInfo.gameState == STATE_GAMEPLAY)
		DrawGame();
	else if (stateInfo.gameState == STATE_MAINMENU)
		DrawMainMenu();
	else if (stateInfo.gameState == STATE_PAUSE)
	{
		DrawGame();
		PostDraw();
		DrawMainMenu();
	}
	glutSwapBuffers();
	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}

/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
void Game::PreDraw()
{
	/* clear the screen */
	glViewport(0, 0, stateInfo.windowWidth, stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red,
		stateInfo.bgClearColor.green,
		stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // clear out the transformation matrix
	glEnable(GL_TEXTURE_2D); // turn on texturing
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	renderingTimer->tick();
	//renderingTimer->print();


	/* sort the sprites by layerID so we draw them in the right order */
	//std::sort(spriteListToDraw.begin(), spriteListToDraw.end(), spriteSortingFunction);

}

/*
 * DrawGame()
 *  - this is the actual drawing of the current frame of the game.
 */
void Game::DrawGame()
{
	//tileManager->DrawScene(entityManager->getXofID(0)-WINDOW_SCREEN_WIDTH/2, entityManager->getYofID(0)-WINDOW_SCREEN_HEIGHT/2);

	//NEED TO DIVIDE BY PLAYER WIDTH/HEIGHT
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(entityManager->getXofID(0) - WINDOW_SCREEN_WIDTH / 2.0, entityManager->getXofID(0) + 34/2 + WINDOW_SCREEN_WIDTH / 2.0, 
		entityManager->getYofID(0) - WINDOW_SCREEN_HEIGHT / 2.0, entityManager->getYofID(0) + 46/2 + WINDOW_SCREEN_HEIGHT / 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	tileManager->DrawScene(entityManager->getXofID(0), entityManager->getYofID(0), updateTimer->getElapsedTimeMS());
	entityManager->DrawAll(0, 0);
	projectileManager->Draw();


	drawSprites();

	glDisable(GL_TEXTURE_2D);

	drawTestPrimitives();
	/* this makes it actually show up on the screen */
}

/*
 * PostDraw()
 *  - in here you should clean up and set up things for the next frame
 *  - i.e. once I've used my assets, I can change them to set up things for
 *    the next frame, usually just memory management or setting up game state
 *    boolean values etc.
 */
void Game::PostDraw()
{
	// nothing here at the moment
}

/* drawSprites()
 * - this function is what actually draws the sprites
 *   onto the screen at their appropriate location
 * - it actually loops through a list of active sprites
 *   and then sorts them by their layerID and then draws them
 * - the sorting has to happen so that you draw from back to front
 *   just like a painter and a canvas.
 */
void Game::drawSprites()
{
	/* we could just do the following to draw the three sprites
	   but that would be silly since we have a list of sprites to draw
	   stored, so all we need to do is go through the list and draw eaach
	   sprite in the list */
	/* // silly way
	testSprite->draw();
	animatedSprite->draw();
	animatedSprite2->draw();
	*/

	/* better way */
	/* this is better because it doesn't matter how many sprites we have, they will always be drawn */
	/*std::vector<Sprite*>::iterator it;
	for(it=spriteListToDraw.begin(); it != spriteListToDraw.end();it++)
	{
	Sprite *s = (*it);
	s->draw(entityManager->getXofID(0)-WINDOW_SCREEN_WIDTH/2, entityManager->getYofID(0)-WINDOW_SCREEN_HEIGHT/2);
	}*/


	//SCALE BARS BASED OFF OF VALUES
	float w, dec = (float)entityManager->getHP(0) / entityManager->getMaxHP(0);
	if (dec <= 0)
		w = 0;
	else
		dec > 1 ? w = 497 : w = 497 * dec;
	hpBar->setSpriteFrameSize(w, 22);
	dec = (float)entityManager->getEnergy(0) / entityManager->getMaxEnergy(0);
	if (dec <= 0)
		w = 0;
	else
		w = 427 * dec;
	energyBar->setSpriteFrameSize(w, 22);



	hpBG->setPosition(entityManager->getCXofID(0) - (66), entityManager->getYofID(0) - (74));
	hpBG->draw(0.25);


	hpBar->setPosition(entityManager->getCXofID(0) - (66 - 3), entityManager->getYofID(0) - (74 - 8.5));
	hpBar->draw(0.25);
	energyBar->setPosition(entityManager->getCXofID(0) - (66 - 13), entityManager->getYofID(0) - (74 - 1.1));
	energyBar->draw(0.25);

	s_Score->setPosition(entityManager->getCXofID(0) - (132), entityManager->getYofID(0) + (100));
	s_Score->draw(0.25);

	s_Time->setPosition(entityManager->getCXofID(0) - (132), entityManager->getYofID(0) + (110));
	s_Time->draw(0.25);
}

/* for testing purposes to show you how to use
   the drawing primitives capabilities */
void Game::drawTestPrimitives()
{
	/*
	draw line
	setLineWidth(5.f);
	setColor(1,0,0);
	drawLine(100,100,200,200);
	setLineWidth(1.f);

	draw rectangle
	setColor(1,1,0);
	drawRectangle(true, 200,200,50,50,45.f);

	draw circle
	setLineWidth(5.f);
	setColor(0,1,1);
	drawCircle(20, 50, 200,200);
	drawFilledCircle(20,50,500,200);
	setLineWidth(1.f);

	draw triangle
	setColor(0.5,0,0.5);
	drawTriangle(true, 100,100,200,200,300,100);
	*/
	setColor(1.f, 0.4f, 0.f);
	char fpsbuffer[16];
	_ltoa_s(score, fpsbuffer, 10);
	drawText(fpsbuffer, entityManager->getCXofID(0) - (130), entityManager->getYofID(0) + (101.1));


	std::string gameClock; 
	int mins = (int)(fTime / 60) % 60;
	int secs = (int)fTime % 60;
	if (mins < 10)
		gameClock.append("0");
	_ltoa_s(mins, fpsbuffer, 10);
	gameClock.append(fpsbuffer);
	gameClock.append(":");
	if (secs < 10)
		gameClock.append("0");
	_ltoa_s(secs, fpsbuffer, 10);
	gameClock.append(fpsbuffer);
	setColor(1.f, 1.f, 1.f);
	drawText(gameClock, entityManager->getCXofID(0) - (130), entityManager->getYofID(0) + (111.1));
}

void Game::DrawMainMenu()
{
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(entityManager->getXofID(0) - WINDOW_SCREEN_WIDTH / 2.0, entityManager->getXofID(0) + 34 / 2 + WINDOW_SCREEN_WIDTH / 2.0,
	entityManager->getYofID(0) - WINDOW_SCREEN_HEIGHT / 2.0, entityManager->getYofID(0) + 46 / 2 + WINDOW_SCREEN_HEIGHT / 2.0);
	*/
	if (stateInfo.gameState == STATE_PAUSE)
	{
		glViewport(0, 0, stateInfo.windowWidth, stateInfo.windowHeight);
		glLoadIdentity(); 
		glEnable(GL_TEXTURE_2D); 

		renderingTimer->tick();
	}
	if (stateInfo.gameState != STATE_PAUSE)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	mainMenu->Draw();
	if (stateInfo.gameState != STATE_PAUSE)
	{
		glDisable(GL_TEXTURE_2D);
		setColor(1.f, 0.f, 0.f);
	}
}

/* update()
  - this function is essentially the game loop
  it gets called often and as such you
  don't actually need a "loop" to define the game
  it happens behind the scenes
  - think of this function as one iteration of the game loop
  - if you need to update physics calculations, sprite animation info,
  or sound etc, it goes in here
  */
void Game::update()
{
#ifdef CONTROLLER_ENABLE
	Controller::instance()->Refresh();
#endif
	if (stateInfo.gameState == STATE_GAMEPLAY)
	{
		// update our clock so we have the delta time since the last update
		updateTimer->tick();

		entityManager->Update(updateTimer->getElapsedTimeMS());
		projectileManager->Update(updateTimer->getElapsedTimeMS());
		colisionManager->Update();

		fTime += updateTimer->getElapsedTimeSeconds();
#ifdef CONTROLLER_ENABLE
		if (Controller::instance()->IsPressed(XINPUT_GAMEPAD_START))
		{
			stateInfo.gameState = STATE_PAUSE;
			mainMenu->Pause();
			mainMenu->setSelection(-1);
		}
#endif
	}
#ifdef CONTROLLER_ENABLE
	else
	{
		if (Controller::instance()->leftStickY > 0.75f)
			mainMenu->KeyPress('w', true);
		else if (Controller::instance()->leftStickY < -0.75f)
			mainMenu->KeyPress('s', true);
		if (Controller::instance()->IsPressed(XINPUT_GAMEPAD_A))
		{
			mainMenu->KeyPress(' ', true);
			if (mainMenu->StartGame())
				stateInfo.gameState = STATE_GAMEPLAY;
		}
	}
#endif
}

/*
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
void Game::addSpriteToDrawList(Sprite *s)
{
	if (s)
	{
		/* push the sprite to the back of the list */
		this->spriteListToDraw.push_back(s);
	}
}


/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardDown()
   - this gets called when you press a key down
   - you are given the key that was pressed
   and where the (x,y) location of the mouse is when pressed
   */
void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	if (stateInfo.gameState == STATE_MAINMENU || stateInfo.gameState == STATE_PAUSE)
	{
		mainMenu->KeyPress(key, true);
		if (mainMenu->StartGame())
			stateInfo.gameState = STATE_GAMEPLAY;
	}
	else if (stateInfo.gameState == STATE_GAMEPLAY)
	{
		entityManager->HandleInput(key, true);
		if (key == 'p' || key == 'P')
		{
			stateInfo.gameState = STATE_PAUSE;
			mainMenu->Pause(); 
			mainMenu->setSelection(-1);
		}
		
	}
}
/* keyboardUp()
   - this gets called when you lift a key up
   - you are given the key that was pressed
   and where the (x,y) location of the mouse is when pressed
   */
void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	if (stateInfo.gameState == STATE_MAINMENU)
	{
		mainMenu->KeyPress(key, false);
	}
	else if (stateInfo.gameState == STATE_GAMEPLAY)
	{
		entityManager->HandleInput(key, false);
	}
}

/*
 * mouseClicked
 * - this function is called when the mouse is clicked and it handles the
 *   input state managment
 */
void Game::mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight - y)*stateInfo.ratioHeight;
		input.button = button;

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			//animatedSprite2->setPosition(input.clickX, input.clickY);
			break;
		case GLUT_RIGHT_BUTTON:

			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		input.mouseDown = false;
	}

}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight - y)*stateInfo.ratioHeight;

	if (input.mouseDown)
	{
		if (input.button == GLUT_LEFT_BUTTON)
		{
			
		}
	}
}
