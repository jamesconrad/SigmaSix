#include "HorizontalScrollingBackground.h"

HorizontalScrollingBackground::HorizontalScrollingBackground(std::string filename, int width, int height)
	: Sprite(filename) 
{
	/* it is assumed that the filename is loaded through the parent class constructor above */
	/* thus we should already have a texture associated with this background */
	scrollingSpeed = 10;
	this->setNumberOfAnimations(1);
	this->addSpriteAnimFrame(0, 0,0);
	this->setSpriteFrameSize(width,height);
	this->setPosition(0,0);
}

HorizontalScrollingBackground::~HorizontalScrollingBackground(void)
{
}

void HorizontalScrollingBackground::SetScrollingSpeed(float speed)
{
	scrollingSpeed = speed;
}

/*
 * update()
 * - we are overriding the update here (since it is a virtual function)
 *   so the background scrolling sprite must do something different
 *   than a traditional sprite 
 * - you will probably want to have boolean flags like isScrolling, etc
 *    and only move if it is scrolling since you might want to control
 *   the scrolling behaviour
 */
void HorizontalScrollingBackground::update()
{
	/* update our x position by scrollingSpeed pixels */
	this->animations[0]->coords[0]->x += scrollingSpeed;

	/* check if we've gone too far */
	if(this->animations[0]->coords[0]->x >= (float)sheet.width - sz.width)
	{
		this->animations[0]->coords[0]->x = sheet.width-sz.width;
	}
	/* u must be normalized for texturing purposes, u,v must be between [0,1] */
	this->animations[0]->coords[0]->u = (float)this->animations[0]->coords[0]->x/(float)sheet.width;
}