#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <cmath>

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define PI 3.14159265358979323846264

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init(void){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) )
        std::cout << "Warning: Linear texture filtering not enabled!\n";

    SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    if( (window = SDL_CreateWindow( "N body N gon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN )) == nullptr ){
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    
    if( (renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED )) == nullptr ){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,0);

	return true;
}

void exit(void){
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
    while( !exit_flag ){
        while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT ){ exit_flag = true; }
        }
        
        SDL_RenderClear( renderer );
        SDL_RenderPresent( renderer );
        SDL_Delay(150);
    }

    exit();

	return 0;
}
