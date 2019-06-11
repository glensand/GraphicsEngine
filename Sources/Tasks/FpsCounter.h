#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>

class FpsCounter : public Component
{
	double	t1;
	int		f1;
	int step{};
	double	fps{1};

public:
	FpsCounter() 
	{
		t1 = Time::GetTime();
		f1 = Time::GetFrameCount();
	}

	virtual ~FpsCounter() {}

	double getFps() {

		return fps;
	}

	virtual void Update() 
	{

		GUI::Label(-1, -1, 0, 0, std::to_string(fps));
		if (step < fps/2) {
			step++;
			return;
		}

		double t2	= Time::GetTime();
		int f2		= Time::GetFrameCount();

		fps = static_cast<double>((f2 - f1)) / (t2 - t1);
		f1 = f2;
		t1 = t2;
		//std::cout << fps << std::endl;
		step = 0;
	}
};
