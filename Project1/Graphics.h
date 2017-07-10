#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
	//������� ��� ��������� �����������
	ID2D1Factory* factory;
	//������������ ���� ��� ������� ������� (hwnd)
	ID2D1HwndRenderTarget* renderTarget;
	//�����
	ID2D1SolidColorBrush* brush;

public:
	Graphics();
	~Graphics();

	ID2D1HwndRenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}

	//������������� �������
	bool Init(HWND windowHandle);

	void BeginDraw() {renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); } 
};

