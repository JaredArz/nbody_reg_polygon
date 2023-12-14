#ifndef manager_guard
#define manager_guard
#include <SDL2/SDL.h>
#include <cassert>
#include <iostream>

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

class Manager{
    public:
        Manager(void){
            this->window   = nullptr;
            this->renderer = nullptr;
            this->SDL_flag = 0;
        }

        ~Manager(void){
            if (this->SDL_flag)
                kill_SDL();
        }

        void update_positions(void){
            this->timer.update();
            double dt = this->timer.get_dt();
            for (iter it = this->points.begin(); it < this->points.end(); it++)
                it->update_pos(dt);
        }

        int draw_points(void){
            SDL_SetRenderDrawColor(this->renderer, POINT_R, POINT_G, POINT_B, POINT_A);

            for (iter it = this->points.begin(); it < this->points.end(); it++)
                SDL_RenderDrawDot(this->renderer, it->x, it->y, POINT_RADIUS);

            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
            return 0;
        }

        void init_SDL(){
            if (this->SDL_flag) //init once
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

            this->SDL_flag = 1;
        }

        void kill_SDL(){
            SDL_DestroyRenderer( this->renderer );
            SDL_DestroyWindow( this->window );
            this->window   = nullptr;
            this->renderer = nullptr;
            //Quit SDL subsystems
            SDL_Quit();
        }

        Point& operator[](size_t idx){
            return this->points[ idx ];
        }

        void add_point(Point p){ this->points.push_back(p); }

        void update_global_timer(void){ this->timer.update(); }

        void update_renderer(void){ SDL_RenderPresent(this->renderer); }

        void clear_renderer(void){ SDL_RenderClear(this->renderer); }

        SDL_Renderer *get_renderer(void){ return this->renderer; }

        SDL_Window *get_window(void){ return this->window; }

        double get_dt(void){ return this->timer.get_dt(); }

        int get_SDL_status(void){ return this->SDL_flag; }

    private:
        SDL_Renderer *renderer;
        SDL_Timer timer;
        SDL_Window *window;
        int SDL_flag; //0: disabled, 1: enabled, 2: error
        std::vector<Point> points;
        typedef std::vector<Point>::iterator iter;
};
#endif
