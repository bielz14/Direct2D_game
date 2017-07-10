#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
}


Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	//создаем фабрику
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if(res != S_OK) return false;

	RECT rect;

	//получение области дисплея приложения
	GetClientRect(windowHandle, &rect);

	//создаем визуализатор цели для области дисплея (hwnd)
	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
	D2D1::HwndRenderTargetProperties(
		windowHandle, D2D1::SizeU(850, 500)),
		&renderTarget);

	if (res != S_OK) return false;
	return true;
}


