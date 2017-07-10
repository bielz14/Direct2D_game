#include "Level.h"
#include "Controller.h"
#include "Graphics.h"

void Level::Load()
{

	background = false;
	remove = true;
	ball_intersect = false;

	motion_angle1 = false;

	motion_angle2 = false;

	sprites = new SpriteSheets();

	sprites->UpdateBackground(L"vol.jpg", gfx);

	sprites->CreatePlayers(L"player.png", gfx);

	sprites->UpdateBall(L"ball.png", gfx);
}

//�������� ������ ��������� ������� � ���� � ������ main, � ������� ����� ���������� ������ ��� ����������� ������������ ����� � ������ ������� ������
void Level::Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right)
{
	if (!a_or_d)//���� �� ���� ������ ������ a ��� d
	{
		left = 0;
		right = 50;
	}

	if (!left_or_right)
	{
		left2 = 380;
		right2 = 230;
	}

	sprites->DrawBackground();

	sprites->DrawPlayer(x, y, left, right);

	sprites->DrawPlayer(x2, y2, left2, right2);

	sprites->DrawBall(x_ball, y_ball);
}

//�������� ������ ��������� ������� � ���� � ������ main, � ������� ����� ���������� ������ ��� ����������� ������������ �����
void Level::Update(int x_window, int y_window, int x_window2, int y_window2, int x_ball_window, int y_ball_window)
{ 
	x = x_window;
	y = y_window;

	x2 = x_window2;
	y2 = y_window2;

	x_ball = x_ball_window;
	y_ball = y_ball_window;
}

bool Level::get_event_button()
{
	if (was_button)return true; 
	else return false;
}

bool Level::get_event_ball_intersect()
{
	//���� ������ ����� ������ �� ����
	if (y_ball + 10 >= y && x_ball < x+50 && x_ball + 20 > x)
	{
		motion_angle1 = true;//��������� ���������� ������ ���� ����� ����� �� ������� ������

		motion_angle2 = false;//���������� ������ ���� ����� ����� �� ������� ������ ����� �� �����������

		ball_intersect = true;//��� ���������� � �������
	}

	//���� ������ ����� ������ �� ����
	if (y_ball + 10 >= y2 && x_ball + 20 > x2 && x_ball < x2 + 20)
	{
		motion_angle2 = true;//��������� ���������� ������ ���� ����� ����� �� ������� ������

		motion_angle1 = false;//���������� ������ ���� ����� ����� �� ������� ������ ����� �� �����������
		
		ball_intersect = true;//��� ���������� � �������
	}

	if (ball_intersect)return true;
	else return false;
}

bool Level::get_motion_angle1()
{
	return motion_angle1;
}

bool Level::get_motion_angle2()
{
	return motion_angle2;
}
