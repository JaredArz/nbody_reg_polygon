#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "point.h"
#include "manager.h"

#define PI 3.14159265358979323846264

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

    Point A(300, 100, v, -1/2, sqrt(3)/2);
    Point B(100, 400, v, 1, 0);
    Point C(500, 400, v, -1/2, -1/sqrt(2));
    mgr.add_point(A);
    mgr.add_point(B);
    mgr.add_point(C);

    while( !exit_flag ){
        while( SDL_PollEvent( &event ) != 0 ){
            if( event.type == SDL_QUIT ){ exit_flag = true; }
        }
        mgr.clear_renderer();

        mgr.update_positions();
        update_vhats(&mgr[0], &mgr[1]);
        update_vhats(&mgr[1], &mgr[2]);
        update_vhats(&mgr[2], &mgr[0]);
        mgr.draw_points();

        mgr.update_renderer();
    }

	return 0;
}
