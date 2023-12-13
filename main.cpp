#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "point.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define PI 3.14159265358979323846264

using std::vector;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int SDL_RenderDrawDot(SDL_Renderer *renderer, int x, int y, int radius){
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);
        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int update_position(vector<point> *points){
    for (vector<point>::iterator it = points->begin(); it < points->end(); it++)
        it->x += 3;
    return 0;
}

int draw_points(SDL_Renderer *renderer, vector<point> *points){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    for (vector<point>::iterator it = points->begin(); it < points->end(); it++){
        SDL_RenderDrawDot(renderer, it->x, it->y, 4);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 0;
}

bool init(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) )
        std::cout << "Warning: Linear texture filtering not enabled!\n";

    SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    if( (window = SDL_CreateWindow( "bottom text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN )) == nullptr ){
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if( (renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED )) == nullptr ){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,0);

	return true;
}

void exit(){
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window   = nullptr;
	renderer = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] ){
	if( !init() ){
        std::cout << "Failed to initialize!\n";
        return 0;
	}
    SDL_Event event;
    bool exit_flag = false;
    vector<point> points;

    point A;
    A.set_pos(100,200);
    points.push_back(A);

    while( !exit_flag ){
        while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT ){ exit_flag = true; }
        }
        SDL_RenderClear( renderer );

        update_position(&points);
        draw_points(renderer, &points);

        SDL_RenderPresent( renderer );
        SDL_Delay(150);
    }

    exit();

	return 0;
}
