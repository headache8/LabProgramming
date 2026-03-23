#include<SDL.h>
#include<stdio.h>
#include<math.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define BOTTOM 600
#define GRAVITY 0.8
#define MIN_OTSKOK 5.0


struct Ball
{
	int x, y;
	double Vy;
	double radius;
};

void DrawBall(SDL_Renderer* renderer, Ball ball)
{
	double step = 0.1;
	for (double i = 0.0; i < 360; i+=step)
	{
		double rad = i * M_PI / 180.0;
		int x = ball.x+(int)(cos(rad)*ball.radius);
		int y = ball.y + (int)(sin(rad)*ball.radius);

		SDL_SetRenderDrawColor(renderer, 255, 10, 10, 0);
		SDL_RenderDrawLine(renderer, ball.x, ball.y, x, y);
	}

}


int main(int argv, char* argc[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error:%s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Ball",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Error:%s", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		printf("Error:%s", SDL_GetError());
		return 1;
	}

	int x = WINDOW_WIDTH / 2;
	int y = WINDOW_HEIGHT / 2-100;

	Ball ball;
	ball.x = x;
	ball.y = y;
	ball.Vy = 0.0;
	ball.radius = 60.0;



	SDL_Event e;
	int run = 0;

	while (!run)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				run = 1;
			}
		}
		SDL_SetRenderDrawColor(renderer, 101, 210, 235, 0);
		SDL_RenderClear(renderer);
		

		ball.Vy += GRAVITY;
		ball.y += ball.Vy;

		if (ball.y+ball.radius >= BOTTOM)
		{
			ball.y = BOTTOM - ball.radius;
			if (fabs(ball.Vy) < MIN_OTSKOK)
			{
				ball.Vy = 0;
			}
			else
				ball.Vy = -ball.Vy*GRAVITY;
		}

		SDL_SetRenderDrawColor(renderer, 60, 189, 65, 0);
		SDL_Rect ground = { 0,BOTTOM,WINDOW_WIDTH,BOTTOM};
		SDL_RenderFillRect(renderer,&ground);

		
		DrawBall(renderer, ball);

		

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}