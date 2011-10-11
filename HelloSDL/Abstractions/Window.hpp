#ifndef ITUENGINE_WINDOW_H
#define ITUENGINE_WINDOW_H

#include <SDL.h>

class Window
{
public:
	Window() {}
	~Window() {}

	void StartUp();
	void ShutDown();

	void Resize();
	void Resize(int Width, int Height);
	
	void SetHeight(int Height);
	int Height() const;

	void SetWidth(int Width);
	int Width() const;

	void SetColorDepth(int ColorDepth);
	int ColorDepth() const;

	void SetWindowTitle(char *Title);

private:
	int m_Height;
	int m_Width;
	int m_ColorDepth;
	int m_VideoFlags;

	SDL_Surface *Surface;

	void InitSDL();
	void InitOpenGL();

	void SetVideoMode();
};

#endif // ITUENGINE_WINDOW_H