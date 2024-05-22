#pragma once
#include "Object.h"

class Background :public Object
{
private:
	int distance1 = 0;
	int distance2 = 800;
	int pipeDistance1 = 400;
	int pipeDistance2 = 700;
	int pipeDistance3 = 1000;
	int incY1 = 0;
	int incY2 = 0;
	int incY3 = 0;
public:
	void GroundUpdate1();
	void GroundUpdate2();
	void Render(SDL_Renderer* ren);
	void GroundRender(SDL_Renderer* ren);
	void PipeRender(SDL_Renderer* ren);
	void Reset();
	bool PipeAbove1Update(int incY, int& score);
	bool PipeAbove2Update(int incY, int& score);
	bool PipeAbove3Update(int incY, int& score);
	bool PipeBelow1Update(int incY);
	bool PipeBelow2Update(int incY);
	bool PipeBelow3Update(int incY);

};

