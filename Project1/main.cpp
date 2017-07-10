#pragma once

#include <Windows.h>
#include "Graphics.h"
#include <d2d1_1.h>
#include "Controller.h"
#include "Level.h"

Graphics* graphics;
HINSTANCE hInst;
HBITMAP hBitmap = NULL;

//координаты игроков и мяча
int x, y, x2, y2, x_ball, y_ball;

//переменные отступа справа от края изображения спрайта для отображения конкретной области этого изображения
int right, left, right2, left2;

int player1_score, player2_score, msgboxID1, msgboxID2;

wchar_t* button; 

bool was_button, revise, revise2, a_or_d, left_or_right, ball_intersect, ball_top;

//переменные для определения диагонали полета мяча
bool left_diaginal, right_diagonal;

//определение того летит ли мяч под углом 90 градусов
bool straight;

bool w_button, a_button, s_button, d_button, up_button, down_button, right_button, left_button;

//переменные для определения того, какой из игроков ударил мяч и какую траекторию полета мяча после этого делать
bool  motion_angle1, motion_angle2;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE) { // загрузка изображения на фон(окно)
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


//метод определения физики игроков
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
				//загружаем данные для отрисовки
				Controller::Update(x, y, x2, y2, x_ball, y_ball);

				//узнаем столкнулся ли мяч с чем либо
				ball_intersect = Controller::get_event_ball_intersect();

				//падение мяча в начале игры
				if (!ball_intersect)
				{
					x_ball -= 2;

					y_ball += 2;

					ball_top = false;

				}
				else {//если после начала игры мяч уже столкнулся с игроком

					//узнаем первый ли игрок ударил по мячу
					motion_angle1 = Controller::get_motion_angle1();

					//определение траектории после удара первого игрока
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

					//узнаем второй ли игрок ударил по мячу
					motion_angle2 = Controller::get_motion_angle2();

					//определение траектории после удара второго игрока
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

				//если мяч упал на пол
				if (y_ball >= 460)
				{
					if (x_ball > 390) player1_score++;
					else player2_score++;

					char buff_player1[10]; // буфер куда будет помещено строковое представление числа

					char buff_player2[10];

					char buff[100];

					//конкатенация строк
					wsprintf(buff_player1, "%d", player1_score);

					wsprintf(buff_player2, "%d", player2_score);

					wsprintf(buff, "     START NEW ROUND?\n\n\n       GREEN %s   %s RED", buff_player1, buff_player2);

					int msgboxID = MessageBox(windowhandle, buff, "GAME MESSAGE", MB_OK);

					if (player1_score == 3)
					{
						msgboxID2 = MessageBox(windowhandle, "WINNER PLAYER №1!\n\nSTART NEW GAME?", "GAME MESSAGE", MB_OK);
					}

					if (player2_score == 3)
					{
						msgboxID2 = MessageBox(windowhandle, "WINNER PLAYER №2!\n\nSTART NEW GAME?", "GAME MESSAGE", MB_OK);
					}

					//если была нажата кнопка OK до того как один из игроков наберет 3 очка - начинаем новый раунд и задаем для него данные
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

					//если была нажата кнопка OK после победы одного из игроков (набор 3-х очков) - начинаем новый раунд с обнуленным счетом
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

                    //узнаем кнопка ли нажалась и выполнят ли еще свое действие или нажалась и уже закончила его выполнять
					was_button = Controller::get_event_button();

					//если кнопка была нажата (уже не выполнятся, то есть в прошедшем времени), то выбирается определенный спрайт
					if (was_button)
					{
						left = 0;
						right = 50;
					}

					    was_if_new_data();

					    //Render (Визуализатор)

						//начало отрисовки
						graphics->BeginDraw();

						//загрузка данных об участке спрайта на изображении
						Controller::Render(left, right, left2, right2, a_or_d, left_or_right);

						/*данные переданы Render и нам нужно указать, 
						  что данные об активности кнопок a или d уже нам не нужны*/
						a_or_d = false;
						/*данные переданы Render и нам нужно указать,
						что данные об активности кнопок left или right уже нам не нужны*/
						left_or_right = false;

						//конец отрисовки
						graphics->EndDraw();

				}
		}

		delete graphics;

	return 0;
}

