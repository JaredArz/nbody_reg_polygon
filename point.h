#ifndef point_guard
#define point_guard
#include <iostream>
#include <cmath>
#include "useful_functions.h"

class point{
    private:
        double x,y,z;
        double vx, vy;

    public:

        point(){ 
            this->x = this->y = this->z = this->vx = this->vy = 0;
        };

        point(double x,double y,double z){ 
            this->x = x; this->y = y; this->z = z;
            this->vx = this->vy = 0;
        };

        void get_unit_vvec(double &vx_n, double &vy_n) const{
            vx_n = this->vx / norm(vx_n, vy_n);
            vy_n = this->vy / norm(vx_n, vy_n);
        };

        friend std::ostream& operator << (std::ostream &f, const point &p){
            f << "⟨" << p.x << ", " << p.y << ", " << p.z << "⟩";
            double vx_n, vy_n;
            p.get_unit_vvec(vx_n,vy_n);
            f << "moving in ⟨" << vx_n << "," << vy_n << "⟩ direction";
            return f;
        }

};
#endif
