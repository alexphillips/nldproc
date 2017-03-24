#include <iostream>
#include <vector>
#include <algorithm>
#include "waveshaper.h"

namespace nldproc {

    waveshaper::waveshaper() {
        this->id_seed = 0;
        this->add_point( -1.0, -1.0, 1.0 );
        this->add_point( 1.0, 1.0, -1.0 );
    }

    spl_point_ID waveshaper::add_point( double x, double y, double k ) {
        spl_point next = { x,y,k, this->id_seed };

        this->points.push_back( next );
        this->sort_points();

        return this->id_seed++;
    }

    void waveshaper::sort_points() {
        std::sort(  this->points.begin(),
                    this->points.end(),
                    []( spl_point &a, spl_point &b) {
                        return a.x < b.x;
                    });
    }

    spl_points waveshaper::get_copyof_points() {
        return spl_points( this->points );
    }

    void waveshaper::del_point( const spl_point_ID id) {
        spl_points new_points;
        auto ptr = &new_points;

        std::for_each( 
            this->points.begin(), 
            this->points.end(), 
            [ ptr, id ](auto point) { 
            if(point.id != id)  {
                ptr->push_back(point);
            }
        });
        this->points = new_points;
        this->sort_points();
    }

    double waveshaper::xs( spl_idx idx ) {
        return this->points[idx].x;
    }

    double waveshaper::ys( spl_idx idx ) {
        return this->points[idx].y;
    }

    double waveshaper::ks( spl_idx idx ) {
        return this->points[idx].k;
    }


    double waveshaper::eval(double x) {

        spl_idx i = 1;
        while( xs(i) < x) i++;

        auto t = (x - xs(i-1)) / (xs(i) - xs(i-1));
        auto a =  ks(i-1)*(xs(i)-xs(i-1)) - (ys(i)-ys(i-1));
        auto b = -ks(i  )*(xs(i)-xs(i-1)) + (ys(i)-ys(i-1));
        auto q = (1-t)*ys(i-1) + t*ys(i) + t*(1-t)*(a*(1-t)+b*t);

        return q;
    }

}
