/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visor_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:24:21 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 19:24:22 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISOR_IN_VISOR_IN_H
# define VISOR_IN_VISOR_IN_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define ANIM_S 2500

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

# include "util.h"

typedef struct		s_texture
{
	int				width;
	int				height;
	SDL_Texture		*data;
}					t_texture;

typedef struct		s_view
{
	float			zoom;
	int				x_max;
	int				x_min;
	int				y_max;
	int				y_min;
}					t_view;

typedef struct		s_mouse
{
	SDL_Point		curr_pos;
	SDL_Point		old_pos;
	int				pressed;
}					t_mouse;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*message;
	TTF_Font		*font;
	t_texture		ant;
	t_texture		house;
	t_view			view;
	t_mouse			mouse;
	Uint32			curr_time;
	Uint32			start_time;
	double			factor;
	int				moving;
	int				running;
}					t_sdl;

typedef struct		s_ant
{
	SDL_Point		*start_pos;
	SDL_Point		curr_pos;
	SDL_Point		*end_pos;
	int				moving;
}					t_ant;

typedef struct		s_stroke
{
	SDL_Point		*p1;
	SDL_Point		*p2;
}					t_stroke;

typedef struct		s_node
{
	char			*name;
	SDL_Point		point;
}					t_node;

typedef struct		s_move
{
	int				nb;
	char			*node;
}					t_move;

typedef struct		s_graph
{
	int				lem_count;
	t_list			*str_head;
	t_list			*movement;
	t_list			*strokes;
	t_list			*node;
	t_list			*str;
	t_ant			*ants;
}					t_graph;

void				sdl_init(t_sdl *sdl);
void				sdl_quit(t_sdl *sdl);

void				create_ants(t_graph *graph);

void				translate_point(SDL_Point *p, SDL_Point s,
						SDL_Point end, double f);
void				translate_to_screen(t_graph *graph, t_sdl *sdl);
void				translate_pos(int x, int y, t_graph *graph);

void				put_ants(t_graph *g, t_sdl *s);
void				draw_strokes(t_graph *graph, t_sdl *sdl);
void				put_text(int x, int y, const char *text, t_sdl *sdl);
void				build_houses(t_texture *txt, t_graph *graph, t_sdl *sdl);

void				texture_render_ex(SDL_Point p, double a,
						t_texture *t, t_sdl *s);
void				texture_render(SDL_Point p, t_texture *texture, t_sdl *sdl);
void				texture_load(char *path, t_texture *texture, t_sdl *sdl);

void				init_graph(t_graph *graph);
t_node				*create_node(char *str);
int					check_type(char *str);
t_stroke			*create_stroke(char *a, char *b, t_graph *graph);
void				check_all(t_graph *graph);
void				fill_stroke(t_node *sae[2], t_graph *graph);
void				fill_node(t_graph *g);
void				fill_movement(t_graph *g);
void				read_all(t_graph *graph);

int					gnl(int fd, char **str);
t_list				*free_and_next(t_list *list);
double				calc_angle(SDL_Point p1, SDL_Point p2);
SDL_Point			*find_by_name(char *name, t_graph *graph);

#endif
