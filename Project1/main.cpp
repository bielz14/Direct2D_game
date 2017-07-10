#pragma once

#include <Windows.h>
#include "Graphics.h"
#include <d2d1_1.h>
#include "Controller.h"
#include "Level.h"

Graphics* graphics;
HINSTANCE hInst;
HBITMAP hBitmap = NULL;

//���������� ������� � ����
int x, y, x2, y2, x_ball, y_ball;

//���������� ������� ������ �� ���� ����������� ������� ��� ����������� ���������� ������� ����� �����������
int right, left, right2, left2;

int player1_score, player2_score, msgboxID1, msgboxID2;

wchar_t* button; 

bool was_button, revise, revise2, a_or_d, left_or_right, ball_intersect, ball_top;

//���������� ��� ����������� ��������� ������ ����
bool left_diaginal, right_diagonal;

//����������� ���� ����� �� ��� ��� ����� 90 ��������
bool straight;

bool w_button, a_button, s_button, d_button, up_button, down_button, right_button, left_button;

//���������� ��� ����������� ����, ����� �� ������� ������ ��� � ����� ���������� ������ ���� ����� ����� ������
bool  motion_angle1, motion_angle2;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE) { // �������� ����������� �� ���(����)
		x = 1;
		y = 392;

		x2 = 777;
		y2 = 392;

		left = 0;
		right = 50;

		left2 = 380;
		right2 = 230;


		x_ball = 390; 
		y_ball = 50;
		
		revise = false;
		revise2 = false;

		was_button = true;

		ball_intersect = false;

		a_or_d = false;

		ball_top = false;

		motion_angle1 = NULL;

		motion_angle2 = NULL;

		w_button = false; a_button = false; s_button = false; d_button = false; up_button = false; down_button = false; right_button = false; left_button = false;

		player1_score = 0;
		player2_score = 0;

		return 0;
	}

	if (uMsg == WM_KEYUP)
	{
		if (wParam == 'W') w_button = true;

		if (wParam == 'D')
		{
			if (a_button) a_button = false;

			d_button = true;

			left = 130;
			right = 65;
		}

		if (wParam == 'A')
		{
			if (d_button) d_button = false;

			a_button = true;

			left = 130;
			right = 65;
		}
		
		if (wParam == VK_UP)
		{
			up_button = true;

			left2 = 222;
			right2 = 150;
		}

		if (wParam == VK_RIGHT)
		{
			if (left_button) left_button = false;

			right_button = true;

			left2 = 222;
			right2 = 150;
		}


		if (wParam == VK_LEFT)
		{
			if (right_button) right_button = false;

			left_button = true;

			left2 = 222;
			right2 = 150;
		}

	}

	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


//����� ����������� ������ �������
void was_if_new_data()
{
		if (w_button)
		{
			if (!revise)
			{
				y -= 10;

				if (y == 152) revise = true;
			}
			else {

				y += 10;

				if (y > 382)
				{
					revise = false;

					was_button = true;

					w_button = false;
				}
			}
		}

		if (d_button)
		{ 
			if (x < 350) x += 7;
			else d_button = false;

			a_or_d = true;
		}
	
		if (a_button) 
		{
			if(x>1) x -= 7;
		    else a_button = false;

			a_or_d = true;
		}

		if (up_button)
		{

			if (!revise2)
			{
				y2 -= 10;

				if (y2 == 152) revise2 = true;
			}
			else {

				y2 += 10;

				if (y2 > 382)
				{
					revise2 = false;

					was_button = true;

					up_button = false;
				}
			}
		}

		if (right_button)
		{
			if (x2 < 777) x2 += 7;
			else right_button = false;

			left_or_right = true;
		}

		if (left_button)
		{
			if (x2 > 425) x2 -= 7;
			else left_button = false;

			left_or_right = true;
		}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	    WNDCLASSEX windowclass;
		ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
		windowclass.cbSize = sizeof(WNDCLASSEX);
		windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
		windowclass.hInstance = hInstance;
		windowclass.lpfnWndProc = WindowProc;
		windowclass.lpszClassName = "MainWindow";
		windowclass.style = CS_HREDRAW | CS_VREDRAW;

		RegisterClassEx(&windowclass);

		RECT rect = { 0, 0, 800, 600 };
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

		HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "DirectX Tute!", WS_OVERLAPPEDWINDOW, 200, 38, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, 0);

		if(!windowhandle) return -1;

		graphics = new Graphics();

		graphics->Init(windowhandle);
		
		if (!graphics)
		{
			delete graphics;
			return -1;
		}

		Game::Init(graphics);

		ShowWindow(windowhandle, nCmdShow);

		Controller::LoadInitialLevel(new Level());

		MSG message;
		message.message = WM_NULL; 

		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
				DispatchMessage(&message);
			else
			{
				//��������� ������ ��� ���������
				Controller::Update(x, y, x2, y2, x_ball, y_ball);

				//������ ���������� �� ��� � ��� ����
				ball_intersect = Controller::get_event_ball_intersect();

				//������� ���� � ������ ����
				if (!ball_intersect)
				{
					x_ball -= 2;

					y_ball += 2;

					ball_top = false;

				}
				else {//���� ����� ������ ���� ��� ��� ���������� � �������

					//������ ������ �� ����� ������ �� ����
					motion_angle1 = Controller::get_motion_angle1();

					//����������� ���������� ����� ����� ������� ������
					if (motion_angle1)
					{
						if (y_ball < 460 && x_ball < 790)
						{
							x_ball += 10;

							if (y_ball > 200 && !ball_top)y_ball -= 5;
							else
							{
								if(x_ball > 390) ball_top = true;
								else ball_top = false;

								if (ball_top) y_ball += 5;
							}
						}
						else if (y_ball < 460) y_ball += 2;
					}
					else { motion_angle1 = false; }

					//������ ������ �� ����� ������ �� ����
					motion_angle2 = Controller::get_motion_angle2();

					//����������� ���������� ����� ����� ������� ������
					if (motion_angle2)
					{

						if (y_ball < 460 && x_ball > 0)
						{
							x_ball -= 10;

							if (y_ball > 200 && !ball_top)y_ball -= 5;
							else
							{
								if (x_ball < 390) ball_top = true;
								else ball_top = false;

								if(ball_top)y_ball += 5;
							}
						}
						else if (y_ball < 460) y_ball += 2;
					}
					else { motion_angle2 = false; }
				}

				//���� ��� ���� �� ���
				if (y_ball >= 460)
				{
					if (x_ball > 390) player1_score++;
					else player2_score++;

					char buff_player1[10]; // ����� ���� ����� �������� ��������� ������������� �����

					char buff_player2[10];

					char buff[100];

					//������������ �����
					wsprintf(buff_player1, "%d", player1_score);

					wsprintf(buff_player2, "%d", player2_score);

					wsprintf(buff, "     START NEW ROUND?\n\n\n       GREEN %s   %s RED", buff_player1, buff_player2);

					int msgboxID = MessageBox(windowhandle, buff, "GAME MESSAGE", MB_OK);

					if (player1_score == 3)
					{
						msgboxID2 = MessageBox(windowhandle, "WINNER PLAYER �1!\n\nSTART NEW GAME?", "GAME MESSAGE", MB_OK);
					}

					if (player2_score == 3)
					{
						msgboxID2 = MessageBox(windowhandle, "WINNER PLAYER �2!\n\nSTART NEW GAME?", "GAME MESSAGE", MB_OK);
					}

					//���� ���� ������ ������ OK �� ���� ��� ���� �� ������� ������� 3 ���� - �������� ����� ����� � ������ ��� ���� ������
					if (msgboxID == IDOK)
					{
						x = 1;
						y = 392;

						x2 = 777;
						y2 = 392;

						left = 0;
						right = 50;

						left2 = 380;
						right2 = 230;


						x_ball = 390;
						y_ball = 50;

						revise = false;
						revise2 = false;

						was_button = true;

						ball_intersect = false;

						a_or_d = false;

						ball_top = false;

						w_button = false; a_button = false; s_button = false; d_button = false; up_button = false; down_button = false; right_button = false; left_button = false;
					
						msgboxID = false;
					}

					//���� ���� ������ ������ OK ����� ������ ������ �� ������� (����� 3-� �����) - �������� ����� ����� � ���������� ������
					if (msgboxID2 == IDOK)
					{
						x = 1;
						y = 392;

						x2 = 777;
						y2 = 392;

						left = 0;
						right = 50;

						left2 = 380;
						right2 = 230;


						x_ball = 390;
						y_ball = 50;

						revise = false;
						revise2 = false;

						was_button = true;

						ball_intersect = false;

						a_or_d = false;

						ball_top = false;

						w_button = false; a_button = false; s_button = false; d_button = false; up_button = false; down_button = false; right_button = false; left_button = false;

						player1_score = 0;
						player2_score = 0;

						msgboxID2 = false;
					}

				}

                    //������ ������ �� �������� � �������� �� ��� ���� �������� ��� �������� � ��� ��������� ��� ���������
					was_button = Controller::get_event_button();

					//���� ������ ���� ������ (��� �� ����������, �� ���� � ��������� �������), �� ���������� ������������ ������
					if (was_button)
					{
						left = 0;
						right = 50;
					}

					    was_if_new_data();

					    //Render (������������)

						//������ ���������
						graphics->BeginDraw();

						//�������� ������ �� ������� ������� �� �����������
						Controller::Render(left, right, left2, right2, a_or_d, left_or_right);

						/*������ �������� Render � ��� ����� �������, 
						  ��� ������ �� ���������� ������ a ��� d ��� ��� �� �����*/
						a_or_d = false;
						/*������ �������� Render � ��� ����� �������,
						��� ������ �� ���������� ������ left ��� right ��� ��� �� �����*/
						left_or_right = false;

						//����� ���������
						graphics->EndDraw();

				}
		}

		delete graphics;

	return 0;
}

