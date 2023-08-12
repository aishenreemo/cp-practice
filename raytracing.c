#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "pallete.h"
#include "vec3d.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define VIEWPORT_WIDTH 1.0
#define VIEWPORT_HEIGHT 1.0

struct sphere_t {
	float center[3];
	float radius;
	const char color[8];
};

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

uint8_t color[4];
bool running;

struct sphere_t spheres[] = {
	{
		.center = { 0, -1, 3 },
		.radius = 1,
		.color = COLOR_RED,
	 },
	{
		.center = { 2, 0, 4 },
		.radius = 1,
		.color = COLOR_BLUE,
	 },
	{
		.center = { -2, 0, 4 },
		.radius = 1,
		.color = COLOR_GREEN,
	 },
	{
		.center = { 0, -5001, 0 },
		.radius = 5000,
		.color = COLOR_YELLOW,
	 },
};

void listen();
void render();

void trace_ray(float o[3], float d[3]);
void intersect_ray_sphere(float o[3], float d[3], struct sphere_t *sphere, float *t_1, float *t_2);

int main(void) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow(
		"Raycasting",
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_UTILITY
	);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	running = true;
	color[3] = UINT8_MAX;

	COLOR_WRITE(COLOR_BACKGROUND, color);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (running) {
		listen();
		render();

		SDL_Delay(1000 / 60);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void listen() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}

void render() {
	float origin[3] = { 0, 0, 0 };

	for (uint i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
		int window_x = i % WINDOW_WIDTH;
		int window_y = i / WINDOW_WIDTH;
		int canvas_x = window_x - (WINDOW_WIDTH / 2);
		int canvas_y = (WINDOW_HEIGHT / 2) - window_y;

		COLOR_WRITE(COLOR_BACKGROUND, color);

		float viewport_x = canvas_x * (VIEWPORT_WIDTH / WINDOW_WIDTH);
		float viewport_y = canvas_y * (VIEWPORT_HEIGHT / WINDOW_HEIGHT);
		float viewport_z = 1.0;
		float viewport[3] = { viewport_x, viewport_y, viewport_z };

		trace_ray(origin, viewport);

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
		SDL_RenderDrawPoint(renderer, window_x, window_y);
	}

	SDL_RenderPresent(renderer);
}

void trace_ray(float o[3], float d[3]) {
	float closest = FLT_MAX;
	struct sphere_t *closest_sphere = NULL;

	for (uint i = 0; i < 4; i++) {
		struct sphere_t *cur_sphere = spheres + i;

		float t_1;
		float t_2;

		intersect_ray_sphere(o, d, cur_sphere, &t_1, &t_2);

		if (t_1 > d[2] && t_1 < closest) {
			closest = t_1;
			closest_sphere = cur_sphere;
		}

		if (t_2 > d[2] && t_2 < closest) {
			closest = t_2;
			closest_sphere = cur_sphere;
		}
	}

	if (closest_sphere == NULL)
		return;

	COLOR_WRITE(closest_sphere->color, color);
}

void intersect_ray_sphere(float o[3], float d[3], struct sphere_t *sphere, float *t_1, float *t_2) {
	if (sphere == NULL)
		return;

	float r = sphere->radius;
	float co[3] = VEC3D_SUB(o, sphere->center);

	float a = VEC3D_DOT(d, d);
	float b = VEC3D_DOT(co, d) * 2;
	float c = VEC3D_DOT(co, co) - r * r;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		*t_1 = 0;
		*t_2 = 0;
		return;
	}

	*t_1 = (-b + sqrt(discriminant)) / (2 * a);
	*t_2 = (-b - sqrt(discriminant)) / (2 * a);
}
