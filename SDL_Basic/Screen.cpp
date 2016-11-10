#include <Windows.h>
#include "Screen.h"

namespace horizongames {
	Screen::Screen(): 
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_pPixelBuffer(NULL) {}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return false;

		m_window = SDL_CreateWindow("My Particle Animation", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
		);

		if (m_window == NULL) {
			SDL_Quit();

			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();

			return false;
		}

		// RGBA8888 means that each pixel is formatted to RGBA with 8 bytes for each 
		// Red, Green, Blue and Alpha.
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, 
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT
		);

		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();

			return false;
		}

		// A buffered memory for each pixel data.
		m_pPixelBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_pBlurPixelBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		// Set each memory cell value of the m_pPixelBuffer to 0 or 0x00 (black). 
		int bufferMemCellCount = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32);
		memset(m_pPixelBuffer, 0x00, bufferMemCellCount);

		return true;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_pPixelBuffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	void Screen::boxBlur() {
		Uint32* temp = m_pPixelBuffer;
		m_pPixelBuffer = m_pBlurPixelBuffer;
		m_pBlurPixelBuffer = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++)
			for (int x = 0; x < SCREEN_WIDTH; x++) {

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++)
					for (int col = -1; col <= 1; col++) {
						int xCurrent = x + col;
						int yCurrent = y + row;

						if (xCurrent >= 0 && xCurrent < SCREEN_WIDTH && yCurrent >= 0 && yCurrent < SCREEN_HEIGHT) {
							Uint32 currentPixel = m_pBlurPixelBuffer[xCurrent + yCurrent * SCREEN_WIDTH];
							
							Uint8 red = currentPixel >> 24;
							Uint8 green = currentPixel >> 16;
							Uint8 blue = currentPixel >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}

	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

		Uint32 color = 0;

		color += red;
		color <<= 8; 
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_pPixelBuffer[x + (SCREEN_WIDTH * y)] = color;
	}

	bool Screen::processEvents() {
		SDL_Event event;

		// SDL_PollEvent returns true if an event within the screen is dispatched, 
		// such as clicking the close button.
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				return false;
	
		return true;
	}

	void Screen::close() {
		delete[] m_pPixelBuffer;
		delete[] m_pBlurPixelBuffer;
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}