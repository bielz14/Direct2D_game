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

	//�������� ����������� ������ ������
	void CreatePlayers(wchar_t* filename, Graphics* gfx);

	//�������� ����������� ����
	void UpdateBackground(wchar_t* filename, Graphics* gfx);

	//�������� ����������� ����
	void UpdateBall(wchar_t* filename, Graphics* gfx);

	//��������� ������
	void DrawPlayer(int z, int y, int left, int right);

	//����+���� ����
	void DrawBackground();

	//��������� ����
	void DrawBall(int x, int y);
};

