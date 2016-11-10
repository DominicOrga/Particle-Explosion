#include <iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include <SDL.h>

#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace std;
using namespace horizongames;

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) 
		cout << "SDL initialization failed." << endl;

	Swarm swarm;

	const Particle* const pParticles = swarm.getParticles();

	int redTemp = 0;
	// Make and update the particles. Also, listen to SDL events.
	while (true) {

		int elapsedTime = SDL_GetTicks();

		// Update particle positions.
		swarm.update(elapsedTime);

		Uint8 red = (1 + sin(elapsedTime * 0.0001)) * 127.5;
		Uint8 green = (1 + sin(elapsedTime * 0.0002)) * 127.5;
		Uint8 blue = (1 + sin(elapsedTime * 0.0003)) * 127.5;

		// Draw particles to screen.
		for (int i = 0; i < Swarm::PARTICLE_COUNT; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = (particle.m_y) * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
			
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		screen.update();

		if (screen.processEvents() == false)
			break;
	}

	screen.close();

	return 0;
}
