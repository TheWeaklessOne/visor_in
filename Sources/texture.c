/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:40 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 17:25:41 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			texture_render(SDL_Point p, t_texture *texture, t_sdl *sdl)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){p.x, p.y, texture->width, texture->height};
	SDL_RenderCopy(sdl->ren, texture->data, NULL, &rect);
}

void			texture_render_ex(SDL_Point p, double a, t_texture *t, t_sdl *s)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){p.x - 45, p.y - 20, t->width, t->height};
	SDL_RenderCopyEx(s->ren, t->data, NULL, &rect, a, NULL, SDL_FLIP_NONE);
}
