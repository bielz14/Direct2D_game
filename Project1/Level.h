#pragma once

#include "Game.h"

class Level: public Game
{
	//в main указано описание данных переменных
	int x, y, x2, y2, x_ball, y_ball, motion_angle1, motion_angle2;

	bool was_button, ball_intersect, background, remove;

	SpriteSheets* sprites;

public:
	
	/*инициализируем вирутальные методы абстрактного класса, 
	которые будем переопределять в cpp файле и использовать в основном методе main не напрямую,
	а через класс Controller, который будет являтся фабрикой для этих методов (шаблон проектирования factory)*/
	virtual void Load() override;
	//virtual void UnLoad() override;
	virtual void Render(int left, int right, int left2, int right2, bool a_or_d, bool left_or_right) override;
	virtual void Update(int x_window, int y_window, int x_window2, int y_window2, int x_ball_window, int y_ball_window) override;

	//метод определяющий была ли нажата кнопка для выбора 1-го из двух изображений спрайта (скинов)
	bool get_event_button();
	//метод для определения столкновения мяча с чем либо
	bool get_event_ball_intersect();

	//методы для попределения ударившего игрока
	bool get_motion_angle1();
	bool get_motion_angle2();
};

