#ifndef VISOR_IN_VISOR_IN_H
# define VISOR_IN_VISOR_IN_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# include "SDL2/SDL.h"
//# include "SDL_image.h"
# include "Utils.h"

typedef struct			s_texture
{
	int					width;
	int					height;
	SDL_Texture			*data;
}						t_texture;

typedef struct			s_view
{
	double				zoom;
}						t_view;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*src;
	SDL_Renderer		*ren;
	t_texture			txt;
	t_view				view;
}						t_sdl;

typedef struct		s_stroke
{
	SDL_Point		p1;
	SDL_Point		p2;
}					t_stroke;

typedef struct		s_node
{
	char			*name;
	SDL_Point		point;
}					t_node;

typedef struct		s_graph
{
	int				lem_count;
	t_list			*strokes;
	t_list			*node;
	t_list			*str;
}					t_graph;

void				sdl_init(t_sdl *sdl);
void				sdl_quit(t_sdl *sdl);

void				texture_render(int x, int y, t_texture *texture, t_sdl *sdl);
void				texture_set_colour(Uint8 red, Uint8 green, Uint8 blue, t_texture *texture, t_sdl *sdl);
void				texture_load(char *path, t_texture *texture, t_sdl *sdl);

void				init_graph(t_graph *graph);
t_node				*create_node(char *str);
int					check_type(char *str);
t_stroke			*create_stroke(char *a, char *b, t_graph *graph);
void				check_all(t_graph *graph);
void				fill_stroke(t_node *sae[2], t_graph *graph);
void				fill_node(t_graph *graph);
void				read_all(t_graph *graph);

#endif
