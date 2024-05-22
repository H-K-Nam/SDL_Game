#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Background.h"
#include "Collision.h"
#include "MainMenu.h"
#include "TextManager.h"
#include "Sound.h"
#include "DeadScene.h"

class GameLoop
{
private:
	Player p;
	Background b;
	Background ground1,ground2;
	const int HEIGHT = 600;
	const int WIDTH = 800;
	bool GameState;
	bool GameOver = false;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;
	Background PipeAbove1;
	Background PipeAbove2;
	Background PipeAbove3;
	Background PipeBelow1;
	Background PipeBelow2;
	Background PipeBelow3;
	SoundManager themeMusic;
	SoundManager hitSound;
	SoundManager pointSound;
	SoundManager flapSound;
	MainMenu menu;
	DeadScene afterScene;
	TextManager score;
	int variance1 = rand() % 201 - 100;
	int variance2 = rand() % 201 - 100;
	int variance3 = rand() % 201 - 100;
	int point = 0;
public:
	GameLoop();
	void MainMenu();
	bool getGameState();
	bool getGameOver();
	void Update();
	void Initialize();
	void Event();
	bool checkCollision();
	void CollisionDetection();
	void gameOverManager();
	void Reset();
	void Render();
	void FreeTexture();
	void Clear();
};
