#pragma once

#include <wincodec.h>	
#include "Graphics.h"

class SpriteSheets
{
	Graphics* gfx;

	ID2D1Bitmap* bmp;
	ID2D1Bitmap* background;
	ID2D1Bitmap* ball;

	int spriteWidth, spriteHeight;
	int spriteAccross;

	SpriteSheets* sprites;

public:
	SpriteSheets();

	~SpriteSheets();

	//создание программной модели игрока
	void CreatePlayers(wchar_t* filename, Graphics* gfx);

	//загрузка изображения фона
	void UpdateBackground(wchar_t* filename, Graphics* gfx);

	//загрузка изображения мяча
	void UpdateBall(wchar_t* filename, Graphics* gfx);

	//отрисовка игрока
	void DrawPlayer(int z, int y, int left, int right);

	//отри+овка фона
	void DrawBackground();

	//отрисовка мяча
	void DrawBall(int x, int y);
};

