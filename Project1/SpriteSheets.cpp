#include "SpriteSheets.h"

SpriteSheets::SpriteSheets()
{
	
}


SpriteSheets::~SpriteSheets()
{
	if (bmp) bmp->Release();

	if (background) background->Release();

	if (ball) ball->Release();
}

void SpriteSheets::UpdateBackground(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;
	background = NULL;
	HRESULT hr;

	//Create a WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// Create a decoder
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&background
	);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

void SpriteSheets::CreatePlayers(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;

	//Create a WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// Create a decoder
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spriteAccross = 1;

}

void SpriteSheets::UpdateBall(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;
	ball = NULL;
	HRESULT hr;

	//Create a WIC factory
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// Create a decoder
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	//получаем фрейм для декодера
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	//конвертирование изображения
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//инициализация изображения
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	//создание изображения
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&ball
	);

	//реализация всего созданного выше
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

//отрисовка игрока
void SpriteSheets::DrawPlayer(int x, int y, int left, int right)
{
	//метод для указания области  и размера изображения на основе которой будет создан спрайт
	D2D1_RECT_F src = D2D1::RectF(
		(float)(left),
		(float)(0),
		(float)(right),
		(float)(spriteHeight));

	//метод для указания области спрайта и его размеров на самом экране приложения
	D2D1_RECT_F dest = D2D1::RectF(
		x, y,
		x + spriteWidth/4, y + spriteHeight);

	//русуем изображение
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src);
}

//отрисовка фона
void SpriteSheets::DrawBackground()
{
	gfx->GetRenderTarget()->DrawBitmap(
		background,
		D2D1::RectF(0.0f, 0.0f,
			background->GetSize().width, background->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, background->GetSize().width, background->GetSize().height)
	);
}

//отрисовка мяча
void SpriteSheets::DrawBall(int x, int y)
{
	D2D1_RECT_F src = D2D1::RectF(
		(float)(0),
		(float)(0),
		(float)(20),
		(float)(20));

	D2D1_RECT_F dest = D2D1::RectF(
		x, y, x+58, y+39);

	gfx->GetRenderTarget()->DrawBitmap(
		ball,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, background->GetSize().width, background->GetSize().height)
	);
}