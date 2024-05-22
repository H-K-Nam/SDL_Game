#include"GameLoop.h"

GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;
	GameState = false;
	p.setSrc(0, 0, 24, 32);
	p.setDest(25, HEIGHT/2, 28, 38);
	ground1.setSrc(0, 0, 112, 336);
	ground1.setDest(0, 420, 112, 336);
	ground2.setSrc(0, 0, 112, 336);
	ground2.setDest(336, 420, 112, 336);
	PipeAbove1.setSrc(0, 0, 320, 52);
	PipeAbove1.setDest(400, -200, 400, 52);
	PipeBelow1.setSrc(0, 0, 320, 52);
	PipeBelow1.setDest(400, 350, 400, 52);
	PipeAbove2.setSrc(0, 0, 320, 52);
	PipeAbove2.setDest(700, -200, 400, 52);
	PipeBelow2.setSrc(0, 0, 320, 52);
	PipeBelow2.setDest(700, 350, 400, 52);
	PipeAbove3.setSrc(0, 0, 320, 52);
	PipeAbove3.setDest(1000, -200, 400, 52);
	PipeBelow3.setSrc(0, 0, 320, 52);
	PipeBelow3.setDest(1000, 350, 400, 52);
}

void GameLoop::MainMenu()
{
    menu.Initialize(renderer);
    while(!menu.getClicked())
    {
        if(menu.EventHandling(event1) == -1)
        {
            GameState = false;
            break;
        }
        SDL_RenderClear(renderer);
        menu.Render(renderer);
        SDL_RenderPresent(renderer);
    }
}

bool GameLoop::getGameState()
{
	return GameState;
}

bool GameLoop::getGameOver()
{
    return GameOver;
}

void GameLoop::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << Mix_GetError() << std::endl;
    }
	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Succeeded!" << std::endl;
			GameState = true;
			p.CreateTexture("Image/yellowbird1.png", renderer);
			p.CreateTexture1("Image/yellowbird2.png", renderer);
			p.CreateTexture2("Image/yellowbird3.png", renderer);
			b.CreateTexture("Image/background.png", renderer);
			ground1.CreateTexture("Image/base.png", renderer);
			ground2.CreateTexture("Image/base.png", renderer);
			PipeAbove1.CreateTexture("Image/pipe_Above.png", renderer);
			PipeBelow1.CreateTexture("Image/pipe_Below.png", renderer);
			PipeAbove2.CreateTexture("Image/pipe_Above.png", renderer);
			PipeBelow2.CreateTexture("Image/pipe_Below.png", renderer);
			PipeAbove3.CreateTexture("Image/pipe_Above.png", renderer);
			PipeBelow3.CreateTexture("Image/pipe_Below.png", renderer);
			themeMusic.loadMusic("theme", "soundtrack/themeSong.mp3");
			hitSound.loadSound("hit", "soundtrack/hit.wav");
			pointSound.loadSound("point", "soundtrack/point.wav");
			flapSound.loadSound("flap", "soundtrack/flap.wav");
			score.CreateFont("font/calibrib.ttf", 38);
			themeMusic.playMusic("theme");
		}
		else
		{
			std::cout << "Not created!" << std::endl;
		}
	}
	else
	{
		std::cout << "window not created!" << std::endl;
	}
}

void GameLoop::Event()
{
	p.GetJumpTime();
	SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT)
	{
		GameState = false;
	}
	if (event1.type == SDL_KEYDOWN)
	{
		if (event1.key.keysym.sym == SDLK_UP || event1.key.keysym.sym == SDLK_SPACE)
		{
			if (!p.JumpState())
			{
				p.Jump();
				flapSound.playSound("flap");
			}
			else
			{
				p.Gravity();
			}
		}
	}
	else
	{
		p.Gravity();
	}
}

void GameLoop::Update()
{
    if(!GameOver)
    {
    std::string s;
    s = "Score: " + std::to_string(point);
    score.Text(s, 255, 0, 0, renderer);

	ground1.GroundUpdate1();
	ground2.GroundUpdate2();

	bool flag1 = false, flag2 = false;
	flag1 = PipeAbove1.PipeAbove1Update(variance1, point);
	flag2 = PipeBelow1.PipeBelow1Update(variance1);
	if (flag1 && flag2)
	{
	    pointSound.playSound("point");
		srand(SDL_GetTicks());
		variance1 = rand() % 201 - 100;
		PipeAbove1.PipeAbove1Update(variance1, point);
		PipeBelow1.PipeBelow1Update(variance1);
	}
	flag1 = PipeAbove2.PipeAbove2Update(variance2, point);
	flag2 = PipeBelow2.PipeBelow2Update(variance2);
	if (flag1 && flag2)
	{
	    pointSound.playSound("point");
		srand(SDL_GetTicks());
		variance2 = rand() % 201 - 100;
		PipeAbove2.PipeAbove2Update(variance2, point);
		PipeBelow2.PipeBelow2Update(variance2);
	}
	flag1 = PipeAbove3.PipeAbove3Update(variance3, point);
	flag2 = PipeBelow3.PipeBelow3Update(variance3);
	if (flag1 && flag2)
	{
	    pointSound.playSound("point");
		srand(SDL_GetTicks());
		variance3 = rand() % 201 - 100;
		PipeAbove3.PipeAbove3Update(variance3, point);
		PipeBelow3.PipeBelow3Update(variance3);
	}

	CollisionDetection();
    }
}

void GameLoop::CollisionDetection()
{
    if(checkCollision())
    {
        GameOver = true;
        hitSound.playSound("hit");
        themeMusic.stopMusic();
        SDL_Delay(400);
        while(!afterScene.getClicked())
        {
            afterScene.Initialize(renderer);
            SDL_RenderClear(renderer);
            afterScene.Render(renderer);
            std::string s = "Your score: " + std::to_string(point);
            score.Text(s, 255, 0, 0, renderer);
            score.Render(renderer, 300, 10);
            SDL_RenderPresent(renderer);
            if(afterScene.EventHandling(event1) == -1)
            {
                GameState = false;
                break;
            }

        }
        Reset();
        afterScene.Free();
    }
}

bool GameLoop::checkCollision()
{
	if (CollisionManager::haveCollision(&p.getDest(), &PipeAbove1.getDest()) || CollisionManager::haveCollision(&p.getDest(), &PipeBelow1.getDest()) ||
		CollisionManager::haveCollision(&p.getDest(), &PipeAbove2.getDest()) || CollisionManager::haveCollision(&p.getDest(), &PipeBelow2.getDest()) ||
		CollisionManager::haveCollision(&p.getDest(), &PipeAbove3.getDest()) || CollisionManager::haveCollision(&p.getDest(), &PipeBelow3.getDest()) ||
        CollisionManager::haveCollision(&p.getDest(), &ground1.getDest()) || CollisionManager::haveCollision(&p.getDest(), &ground2.getDest()) || p.getYpos() < 0)
        {
            return true;
        }
    return false;
}

void GameLoop::Reset()
{
    if(GameOver)
    {
        GameOver = false;
        point = 0;
        variance1 = rand() % 201 - 100;
        variance2 = rand() % 201 - 100;
        variance3 = rand() % 201 - 100;
        p.Reset();
        PipeAbove1.Reset();
        PipeAbove2.Reset();
        PipeAbove3.Reset();
        PipeBelow1.Reset();
        PipeBelow2.Reset();
        PipeBelow3.Reset();
        themeMusic.playMusic("theme");
        afterScene.setClicked();
    }
}

void GameLoop::Render()
{
    if(!GameOver)
    {
	SDL_RenderClear(renderer);
	b.Render(renderer);
	PipeAbove1.PipeRender(renderer);
	PipeBelow1.PipeRender(renderer);
	PipeAbove2.PipeRender(renderer);
	PipeBelow2.PipeRender(renderer);
	PipeAbove3.PipeRender(renderer);
	PipeBelow3.PipeRender(renderer);
	ground1.GroundRender(renderer);
	ground2.GroundRender(renderer);
	score.Render(renderer, 350, 10);
	p.Render(renderer);
	SDL_RenderPresent(renderer);
    }
}

void GameLoop::FreeTexture()
{
    p.Destroy();
    p.FreeTexture();
    b.Destroy();
    ground1.Destroy();
    ground2.Destroy();
    PipeAbove1.Destroy();
    PipeAbove2.Destroy();
    PipeAbove3.Destroy();
    PipeBelow1.Destroy();
    PipeBelow2.Destroy();
    PipeBelow3.Destroy();
    themeMusic.freeMusic("theme");
    hitSound.freeSound("hit");
    flapSound.freeSound("flap");
    pointSound.freeSound("point");
}

void GameLoop::Clear()
{
    FreeTexture();
    score.CloseFont();
    TTF_Quit();
    Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
