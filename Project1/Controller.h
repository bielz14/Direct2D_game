#pragma once

#include "Game.h"

class Controller
{
	Controller() { }
	static Game* current;
public:
	static bool Loading;

	static void Init();

	static void LoadInitialLevel(Game* game);

	static void Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right);

	static void Update(int x_window, int y_window, int x_window2, int y_window2, int x, int y);

	static bool get_event_button();

	static bool get_event_ball_intersect();

	static bool get_motion_angle1();

	static bool get_motion_angle2();
};

