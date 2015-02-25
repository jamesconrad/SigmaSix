#pragma once
#include "Sprite.h"
#include <string>

class HorizontalScrollingBackground : public Sprite
{
public:
	HorizontalScrollingBackground(std::string filename, int width, int height);
	~HorizontalScrollingBackground(void);

	virtual void update();
	void SetScrollingSpeed(float speed);

	float scrollingSpeed;
	
};
