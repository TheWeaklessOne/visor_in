#include "../Includes/visor_in.h"
#include <time.h>

void			set_w_h(int *w, int *h, t_sdl *sdl)
{
	static		int rnd_w;
	static		int rnd_h;
	int			gavno[10] = {10, 50, 40, 80, 30, 20, 55, 11, 28, 66};
	static		int 	i;

	if (!rnd_w)
		rnd_w = SCREEN_WIDTH / gavno[i++];
	if (!rnd_h)
	{
		rnd_h = gavno[i] * 10;
		*h = rnd_h;
	}
	*w += rnd_w;
	if (*w > SCREEN_WIDTH)
	{
		rnd_w = 0;
		rnd_h = 0;
		*w = -sdl->txt.width;
	}
	if (i == 9)
		i = 0;
}

int				main()
{
	int			running;
	t_graph		graph;
	t_sdl		sdl;
	SDL_Event	e;

//	init_graph(&graph);
	sdl_init(&sdl);
	//texture_load("../ant.png", &sdl.txt, &sdl);
	running = 1;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y > 0)
					sdl.view.zoom -= 0.05;
				else if (e.wheel.y < 0)
					sdl.view.zoom += 0.05;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
			}
			if (e.type == SDL_QUIT)
				running = 0;
		}
		SDL_SetRenderDrawColor(sdl.ren, 0x30, 0x30, 0x30, 0xFF);
		SDL_RenderClear(sdl.ren);
		//texture_render(0, 0, &sdl.txt, &sdl);
		SDL_RenderPresent(sdl.ren);
	}
	sdl_quit(&sdl);
	exit(0);
}
