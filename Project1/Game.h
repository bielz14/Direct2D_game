//абстрактный класс

#pragma once

#include "Graphics.h"
#include "SpriteSheets.h"

class Game
{
protected:
	static Graphics* gfx;

public:

	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right) = 0;
	virtual void Update(int x_window, int y_window, int x_window2, int y_window2, int x_ball, int y_ball) = 0;

	virtual bool get_event_button() = 0;
	virtual bool get_event_ball_intersect() = 0;
	virtual bool get_motion_angle1() = 0;
	virtual bool get_motion_angle2() = 0;
};

