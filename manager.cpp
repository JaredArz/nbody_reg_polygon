#include <SDL2/SDL.h>
#include <cassert>
#include <iostream>

#include "manager.h"
#include "timer.h"
#include "point.h"
#include "drawing.h"

#define SCREEN_WIDTH  601
#define SCREEN_HEIGHT 601
#define POINT_RADIUS 4
#define POINT_R 0
#define POINT_G 0
#define POINT_B 255
#define POINT_A 0

void Manager::init_SDL(void){
    if (this->SDL_flag) //init only once
        return;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        this->SDL_flag = 2;
    }

    //Set texture filtering to linear
    if( SDL_flag != 2 && !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) ){
        std::cout << "Warning: Linear texture filtering not enabled!\n";
        this->SDL_flag = 2;
    }

    if( SDL_flag != 2 && (this->window = SDL_CreateWindow( "bottom text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN )) == nullptr ){
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        this->SDL_flag = 2;
    }

    if( SDL_flag != 2 && (this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC )) == nullptr ){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        this->SDL_flag = 2;
    }

    //FIXME: add errors for these
    SDL_RenderSetLogicalSize(this->renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(this->renderer,0,0,0,0);

    assert(this->SDL_flag != 2);

    // pass assert -> success
    this->SDL_flag = 1;
    return;
}

void Manager::kill_SDL(void){
    if (!this->SDL_flag) //dont kill if not active
        return;
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    this->window   = nullptr;
    this->renderer = nullptr;
    //Quit SDL subsystems
    SDL_Quit();
    return;
}

void Manager::add_point(Point p){
    assert( this->points.size() < this->max_points );
    this->points.push_back(p);
    return;
}

void Manager::draw_points(void){
    if (!this->SDL_flag)
        return;

    SDL_SetRenderDrawColor(this->renderer, POINT_R, POINT_G, POINT_B, POINT_A);

    for (Manager::iter it = this->points.begin(); it < this->points.end(); it++)
        SDL_RenderDrawDot(this->renderer, it->x, it->y, POINT_RADIUS);

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    return;
}

void Manager::draw_regular_polygon(unsigned int n, double L){
    if (!this->SDL_flag)
        return;

    assert( n >= 3 );

    SDL_SetRenderDrawColor(this->renderer, POINT_R, POINT_G, POINT_B, POINT_A);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    double x_0 = w/2.f;
    double y_0 = h/2.f;

    double theta = 2*PI/n;
    double theta_0;

    if(n == 3)
        theta_0 = 0;
    else
        theta_0 = PI / (4 * (n-3));

    double theta_last = theta_0;
    for(int i = 1; i <= n; i++){
        double theta_i = theta_last + theta;
        double x_i = x_0 + L*sin(theta_i); 
        double y_i = y_0 - L*cos(theta_i); 
        SDL_RenderDrawDot(this->renderer, x_i, y_i, POINT_RADIUS);
        theta_last = theta_i;
    }

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    return;
}

void Manager::gen_regular_polygon(unsigned int n, double L){
    assert( n >= 3 );

    int w,h;
    SDL_GetWindowSize(window, &w, &h);

    double x_0 = w/2.f;
    double y_0 = h/2.f;

    double theta = 2*PI/n;
    double theta_0;

    if(n == 3)
        theta_0 = 0;
    else
        theta_0 = PI / (4 * (n-3));

    double theta_last = theta_0;
    for(int i = 1; i <= n; i++){
        double theta_i = theta_last + theta;
        double x_i = x_0 + L*sin(theta_i); 
        double y_i = y_0 - L*cos(theta_i); 
        this->points.push_back(Point(x_i,y_i));
        theta_last = theta_i;
    }

    return;
}

void Manager::draw_test(void){
    if (!this->SDL_flag)
        return;

    SDL_DrawWrap(this->renderer);
    return;
}

void Manager::update_positions(void){
    // NOTE: timer updated here since pos is only time-dependent system
    this->timer.update();
    double dt = this->timer.get_dt();
    for (Manager::iter it = this->points.begin(); it < this->points.end(); it++)
        it->update_pos(dt);
    return;
}

void Manager::update_renderer(void){
    if (!this->SDL_flag)
        return;
    SDL_RenderPresent(this->renderer);
    return;
}

void Manager::clear_renderer(void){
    if (!this->SDL_flag)
        return;
    SDL_RenderClear(this->renderer);
    return;
}

int Manager::get_SDL_status(void){
    return this->SDL_flag;
}

Point& Manager::operator[](size_t idx){
    return this->points[ idx ];
}
