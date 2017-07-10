#include "Controller.h"

Game* Controller::current;
bool Controller::Loading;

void Controller::Init()
{
	Loading = true;
	current = 0;
}

void Controller::LoadInitialLevel(Game * game)
{
	Loading = false;
	current = game;
	current->Load();
	Loading = false;
}

void Controller::Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right)
{
	if (Loading) return;
	current->Render(left, right, left2, right2, a_or_d, left_or_right);
}

void Controller::Update(int x_window, int y_window, int x_window2, int y_window2, int x, int y)
{
	if (Loading) return;
	current->Update(x_window, y_window, x_window2, y_window2, x, y);
}

bool Controller::get_event_button()
{
	return current->get_event_button();
}

bool Controller::get_event_ball_intersect()
{
	return current->get_event_ball_intersect();
}

bool Controller::get_motion_angle1()
{
	return current->get_motion_angle1();
}

bool Controller::get_motion_angle2()
{
	return current->get_motion_angle2();
}