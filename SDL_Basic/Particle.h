#pragma once

#ifndef PARTICLE_H_
#define PARTICLE_H_
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <cmath>

namespace horizongames {
	struct Particle {
		double m_x;		// x values range between -1 to 1.
		double m_y;		// y values range between -1 to 1.

	private:
		double m_momentum;		// Momentum value ranges between 0 to 1.
		double m_direction;		// Direction is based on radian values between 0 to 2PI.

	public:
		Particle();
		~Particle();

		void update(int& deltaTime);
	};
}

#endif