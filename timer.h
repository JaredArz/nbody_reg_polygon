#ifndef timer_guard
#define timer_guard
#include <SDL2/SDL.h>

class SDL_Timer{
    public:
        double get_dt(){
            double dt = (this->current_tick - this->last_tick) / (double)SDL_GetPerformanceFrequency();
            return (dt > 1) ? 1 : dt;
        }
        void update(){
            this->last_tick = this->current_tick;
            this->current_tick = SDL_GetPerformanceCounter();
        };

    private:
        uint64_t last_tick, current_tick;

};
#endif
