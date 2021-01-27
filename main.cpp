#include <SDL.h>
#include <iostream>
#include <string>

struct Circle { int x, y, r; };

SDL_Window* g_window;
SDL_Renderer* g_renderer;

bool InitializeWindow(int windowWidth, int windowHeight);
void RenderCircle(const Circle& circle);
void Destroy();

int main(int argc, char* argv[])
{
	if (InitializeWindow(800, 600))
	{
		Circle circle = { 400, 300, 100 };
		RenderCircle(circle);
		SDL_Delay(2000);
	}

	Destroy();

	return 0;
}

bool InitializeWindow(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << std::string("Could not initialize SDL. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	g_window = SDL_CreateWindow("Efficient Circle Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (g_window == nullptr)
	{
		std::cout << std::string("Could not create SDL window. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	if (g_renderer == nullptr)
	{
		std::cout << std::string("Could not get create SDL Renderer. SDL Error: ") + SDL_GetError() << "\n";
		return false;
	}

	return true;
}

void RenderCircle(const Circle& circle)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

	int x = circle.r;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		SDL_RenderDrawPoint(g_renderer, circle.x + x, circle.y + y);
		SDL_RenderDrawPoint(g_renderer, circle.x + y, circle.y + x);
		SDL_RenderDrawPoint(g_renderer, circle.x - y, circle.y + x);
		SDL_RenderDrawPoint(g_renderer, circle.x - x, circle.y + y);
		SDL_RenderDrawPoint(g_renderer, circle.x - x, circle.y - y);
		SDL_RenderDrawPoint(g_renderer, circle.x - y, circle.y - x);
		SDL_RenderDrawPoint(g_renderer, circle.x + y, circle.y - x);
		SDL_RenderDrawPoint(g_renderer, circle.x + x, circle.y - y);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}

	SDL_RenderPresent(g_renderer);
}

void Destroy()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}
