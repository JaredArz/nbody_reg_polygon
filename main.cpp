#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "point.h"
#include "useful_functions.h"
#include "timer.h"

#define SCREEN_WIDTH  601
#define SCREEN_HEIGHT 601
#define PI 3.14159265358979323846264


void update_positions(std::vector<point> *points, double dt){
    for (std::vector<point>::iterator it = points->begin(); it < points->end(); it++)
        it->update_pos(dt);
}

void update_vhats(point *current, point *next){
    double r_x = next->x - current->x;
    double r_y = next->y - current->y;
    double distance = sqrt((next->x - current->x)*(next->x - current->x) +
                      (current->y - next->y)*(current->y - next->y));
    current->vhat_x = r_x / distance;
    current->vhat_y = r_y / distance;
}

int draw_points(SDL_Renderer *renderer, std::vector<point> *points){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

    for (std::vector<point>::iterator it = points->begin(); it < points->end(); it++)
        SDL_RenderDrawDot(renderer, it->x, it->y, 4);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 0;
}

bool init(SDL_Renderer **renderer, SDL_Window **window){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) ){
        std::cout << "Warning: Linear texture filtering not enabled!\n";
    }

    if( (*window = SDL_CreateWindow( "bottom text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN )) == nullptr ){
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if( (*renderer = SDL_CreateRenderer( *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC )) == nullptr ){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_RenderSetLogicalSize(*renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(*renderer,0,0,0,0);

	return true;
}

void exit(SDL_Renderer **renderer, SDL_Window **window){
	SDL_DestroyRenderer( *renderer );
	SDL_DestroyWindow( *window );
	*window   = nullptr;
	*renderer = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] ){
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Timer timer;

    bool exit_flag = false;
    double v = 30;
    double dt;
    std::vector<point> points;

	if( !init(&renderer, &window) ){
        std::cout << "Failed to initialize!\n";
        return 0;
	}

    point A(300, 100, v, -1/2, sqrt(3)/2);
    point B(100, 400, v, 1, 0);
    point C(500, 400, v, -1/2, -1/sqrt(2));
    points.push_back(A);
    points.push_back(B);
    points.push_back(C);

    while( !exit_flag ){
        while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT ){ exit_flag = true; }
        }
        SDL_RenderClear( renderer );

        timer.update();
        dt = timer.get_dt();
        update_positions(&points, dt);
        update_vhats(&points[0], &points[1]);
        update_vhats(&points[1], &points[2]);
        update_vhats(&points[2], &points[0]);
        draw_points(renderer, &points);

        SDL_RenderPresent( renderer );
    }

    exit(&renderer, &window);

	return 0;
}
