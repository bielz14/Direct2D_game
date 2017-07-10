#pragma once

#include "Game.h"

class Level: public Game
{
	//� main ������� �������� ������ ����������
	int x, y, x2, y2, x_ball, y_ball, motion_angle1, motion_angle2;

	bool was_button, ball_intersect, background, remove;

	SpriteSheets* sprites;

public:
	
	/*�������������� ����������� ������ ������������ ������, 
	������� ����� �������������� � cpp ����� � ������������ � �������� ������ main �� ��������,
	� ����� ����� Controller, ������� ����� ������� �������� ��� ���� ������� (������ �������������� factory)*/
	virtual void Load() override;
	//virtual void UnLoad() override;
	virtual void Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right) override;
	virtual void Update(int x_window, int y_window, int x_window2, int y_window2, int x_ball_window, int y_ball_window) override;

	//����� ������������ ���� �� ������ ������ ��� ������ 1-�� �� ���� ����������� ������� (������)
	bool get_event_button();
	//����� ��� ����������� ������������ ���� � ��� ����
	bool get_event_ball_intersect();

	//������ ��� ������������ ���������� ������
	bool get_motion_angle1();
	bool get_motion_angle2();
};

