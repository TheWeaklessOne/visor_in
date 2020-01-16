#include "../Includes/visor_in.h"

void			texture_load(char *path, t_texture *texture, t_sdl *sdl)
{
	SDL_Surface	*surf;

	if (!(surf = IMG_Load(path)))
		return (ft_error(SDL_GetError()));
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0xFF, 0xFF));
	if (!(texture->data = SDL_CreateTextureFromSurface(sdl->ren, surf)))
		return (ft_error(SDL_GetError()));
	texture->height = surf->h;
	texture->width = surf->w;
	SDL_FreeSurface(surf);
}

void			texture_render(int x, int y, t_texture *texture, t_sdl *sdl)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){x, y, texture->width + texture->width * sdl->view.zoom,
				   texture->height + texture->height * sdl->view.zoom};
	SDL_RenderCopy(sdl->ren, texture->data, NULL, &rect);
}