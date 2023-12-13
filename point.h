#ifndef point_guard
#define point_guard
#include <iostream>
#include <cmath>
#include "useful_functions.h"

class point{
    public:
        double x,y;
        double vx, vy;

        point(){ 
            this->x = this->y = this->vx = this->vy = 0;
        };

        point(double x,double y){ 
            this->x = x; this->y = y;
            this->vx = this->vy = 0;
        };

        void get_unit_vvec(double &vhat_x, double &vhat_y) const{
            double mag = norm(this->vx, this->vy);

            vhat_x = ( mag > 1e-7) ? this->vx / mag : 0;
            vhat_y = ( mag > 1e-7) ? this->vy / mag : 0;
        };

        void set_pos(double x, double y){
            this->x = x; this->y = y;
        }

        void set_vel(double vx, double vy){
            this->vx = vx; this->vy = vy;

        }

        friend std::ostream& operator << (std::ostream &f, const point &p){
            f << "⟨" << p.x << ", " << p.y << "⟩";
            double vhat_x, vhat_y;
            p.get_unit_vvec(vhat_x,vhat_y);
            f << ", in ⟨" << vhat_x << ", " << vhat_y << "⟩ direction";
            return f;
        }

};
#endif
