#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "point.h"
#include "manager.h"

void update_vhats(Point *current, Point *next){
    double r_x = next->x - current->x;
    double r_y = next->y - current->y;
    double distance = sqrt((next->x - current->x)*(next->x - current->x) +
                      (current->y - next->y)*(current->y - next->y));
    current->vhat_x = r_x / distance;
    current->vhat_y = r_y / distance;
}

int main( int argc, char* args[] ){
    Manager mgr;
    mgr.init_SDL();

    SDL_Event event;
    bool exit_flag = false;
    double v = 30;

    mgr.gen_regular_polygon(100, 300);
    mgr.set_velocity(v);

    while( !exit_flag ){
        while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT ){ exit_flag = true; }
        }
        mgr.clear_renderer();

        //mgr.gen_regular_polygon(3, 250);
        mgr.update_vhats();
        mgr.update_positions();
        mgr.draw_points();

        mgr.update_renderer();
    }

	return 0;
}
