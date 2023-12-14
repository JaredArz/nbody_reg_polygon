#ifndef manager_guard
#define manager_guard
#include <SDL2/SDL.h>

#include "timer.h"
#include "point.h"

class Manager{
    public:
        Manager(void){
            this->window   = nullptr;
            this->renderer = nullptr;
            this->SDL_flag = 0;
        }

        ~Manager(void){
            if (this->SDL_flag)
                this->kill_SDL();
        }

        void init_SDL(void);

        void kill_SDL(void);

        void add_point(Point p);

        void draw_points(void);

        void update_positions(void);

        void update_renderer(void);

        void clear_renderer(void);

        int get_SDL_status(void);

        Point& operator[](size_t idx);

        // NOTE: not needed for now
        // void update_global_timer(void);
        // double get_dt(void);
        // SDL_Renderer *get_renderer(void);
        // SDL_Window *get_window(void);

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Timer timer;
        int SDL_flag; //0: Disabled, 1: Enabled, 2: Internal error
        unsigned int max_points = 1000;
        std::vector<Point> points;
        typedef std::vector<Point>::iterator iter;
};
#endif
