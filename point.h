#ifndef point_guard
#define point_guard
#include <iostream>
#include <cmath>
#include <cassert>
#include "helper_funcs.h"

class Point{
    public:
        double x,y;
        double v, vhat_x, vhat_y;

        Point(){ 
            this->x = this->y = 0;
            this->v = this->vhat_x = this->vhat_y = 0;
        };

        Point(double x, double y){ 
            this->x = x; this->y = y;
            this->v = this->vhat_x = this->vhat_y = 0;
        };

        Point(double x, double y,
                double v, double vhat_x, double vhat_y){ 
            this->x = x; this->y = y;
            this->v = v;
            this->vhat_x = vhat_x;
            this->vhat_y = vhat_y;
        };


        void set_pos(double x, double y){
            this->x = x; this->y = y;
        }

        void set_vhat(double vhat_x, double vhat_y){
            this->vhat_x = vhat_x; this->vhat_y = vhat_y;
        }

        void get_vhat(double &vhat_x, double &vhat_y) const{
            assert( abs(norm(this->vhat_x, this->vhat_y) - 1 ) < 1e-7 ); 
            vhat_x = this->vhat_x;
            vhat_y = this->vhat_y;
        };

        void update_pos(double dt){
            this->x += this->v * this->vhat_x * dt;
            this->y += this->v * this->vhat_y * dt;
        }

        friend std::ostream& operator << (std::ostream &f, const Point &p){
            f << "⟨" << p.x << ", " << p.y << "⟩";
            f << ", in the ⟨" << p.vhat_x << ", " << p.vhat_y << "⟩ direction";
            return f;
        }

};
#endif
