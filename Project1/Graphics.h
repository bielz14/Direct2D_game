#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
	//фабрика для отрисовки изображения
	ID2D1Factory* factory;
	//визуализатор цели для области дисплея (hwnd)
	ID2D1HwndRenderTarget* renderTarget;
	//кисть
	ID2D1SolidColorBrush* brush;

public:
	Graphics();
	~Graphics();

	ID2D1HwndRenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	//инициализация графики
	bool Init(HWND windowHandle);

	void BeginDraw() {renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); } 
};

