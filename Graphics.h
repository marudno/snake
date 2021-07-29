#pragma once

#include <Windows.h>
#include <iostream>
#include <d2d1_3.h>

class Graphics
{
private:
	ID2D1Factory* factory = nullptr;
	ID2D1HwndRenderTarget* renderTarget = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

public:
	Graphics(HWND hwnd)
	{
		HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
		if (res != S_OK) throw 1;

		RECT rect;
		GetClientRect(hwnd, &rect);

		res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right, rect.bottom)),
			&renderTarget);

		if (res != S_OK) throw 1;
	}

	~Graphics()
	{
		if(factory) factory->Release(); //if(factory != nullprt)
		if(renderTarget) renderTarget->Release();
		if(brush) brush->Release();
	}

	void beginDraw()
	{
		renderTarget->BeginDraw();
	}

	void endDraw()
	{
		renderTarget->EndDraw();
	}

	void cleanScreen(float r, float g, float b)
	{
		renderTarget->Clear(D2D1::ColorF(r, g, b));
	}

	void drawCircle(float x, float y, float radius, float r, float g, float b, float a)
	{
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
	}
};

//wszystko lepiej mieæ w cpp, bo to on bêdzie kompilowany - w .h zostawiamy jedynie deklaracje by ukryæ kod - poprawiæ!
