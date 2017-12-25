#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <math.h>
#include <iostream>

using namespace std;

//----- Стуктури -----------------------------------------

struct point{
    double x;
    double y;
    point(double x, double y): x(x), y(y) {}
    point() {}
};

struct line{
    point start_p;
    point end_p;
    double A;
    double B;
    double C;
    line(point start_p, point end_p): start_p(start_p), end_p(end_p){
        this->A = start_p.y - end_p.y;
        this->B = end_p.x - start_p.x;
        this->C = start_p.x*end_p.y - end_p.x*start_p.y;
    }
    line(){}

    void set_value(point start_p, point end_p){
        this->start_p = start_p;
        this->end_p = end_p;
        this->A = start_p.y - end_p.y;
        this->B = end_p.x - start_p.x;
        this->C = start_p.x*end_p.y - end_p.x*start_p.y;
    }
    void set_value(double x1, double y1, double x2, double y2){
        point st_p(x1,y1);
        this->start_p = st_p;
        point end_p(x2,y2);
        this->end_p = end_p;
        this->A = start_p.y - end_p.y;
        this->B = end_p.x - start_p.x;
        this->C = start_p.x*end_p.y - end_p.x*start_p.y;
    }
};
//----- Формули -----------------------------------------

bool parallel(line a , line b){
    bool flag;
    flag = a.A/b.A == a.B/b.B;
    return flag;
}

bool in_same_subplane(line l, point A, point B){
    double A_res = (l.A * A.x) + (l.B * A.y) + l.C;
    double B_res = (l.A * B.x) + (l.B * B.y) + l.C;

    bool return_value = (A_res * B_res) >= 0;
    return return_value;
}

point cross_point (line a, line b){
    point cr_point;

    double y = (-b.C + (a.C * (b.A / a.A)))/(b.B - (a.B * (b.A / a.A)));

    double x = (-a.B * y - a.C) / a.A;

    cr_point.x = x;
    cr_point.y = y;

    return cr_point;
}

point symmetrical_point(line a, line b){
    line normal_line;
    normal_line.A = -b.B;
    normal_line.B = b.A;

    point cr = cross_point(a,b);

    normal_line.C = -(normal_line.A*cr.x + normal_line.B*cr.y);

    line new_b;

    new_b.A = b.A;
    new_b.B = b.B;
    new_b.C = -(new_b.A*a.end_p.x + new_b.B*a.end_p.y);

    point mid_p = cross_point(new_b, normal_line);

    point sim;
    sim.x = 2*mid_p.x - a.end_p.x;
    sim.y = 2*mid_p.y - a.end_p.y;

    return sim;
}

line symmetrical_line(line a, line b){
    line r(cross_point(a,b),symmetrical_point(a,b));
    return r;
}

double distance(point a, line b){

    double dis ;

    if (b.end_p.x-b.start_p.x == 0)
        dis = (a.y - b.start_p.y) / (b.end_p.y-b.start_p.y);
    else
        dis = (a.x - b.start_p.x) / (b.end_p.x-b.start_p.x);


    return dis;

}

double distance_point_to_line(point a, line b){

    double p = b.A * a.x + b.B * a.y + b.C;

    p = (p<0)? -p : p;

    double q = sqrt(b.A * b.A + b.B * b.B);

    double res = p/q;
    return res;
}


point point_on_c(point m, double r, line a){

    double p, b, c;

    p  = (a.end_p.x - a.start_p.x)*(a.end_p.x - a.start_p.x) ;
    p -= (a.end_p.y - a.start_p.y)*(a.end_p.y - a.start_p.y);

    b  = 2*(a.end_p.x - a.start_p.x)*(a.start_p.x - m.x);
    b += 2*(a.end_p.y - a.start_p.y)*(a.start_p.y - m.y);

    c  = (a.start_p.x - m.x)*(a.start_p.x - m.x);
    c += (a.start_p.y - m.y)*(a.start_p.y - m.y);
    c -= r*r;

    double t =0;

    int d =b*b - 4*p*c ;
    double sqrtD = sqrt(d);

    t = (-b + sqrtD)/(2*p);
    point hit;
    hit.x = (a.end_p.x - a.start_p.x) * t + a.start_p.x;
    hit.y = (a.end_p.y - a.start_p.y) * t + a.start_p.y;

    t = (-b - sqrtD)/(2*p);
    point hit2;
    hit2.x = (a.end_p.x - a.start_p.x) * t + a.start_p.x;
    hit2.y = (a.end_p.y - a.start_p.y) * t + a.start_p.y;

    double dis1 = distance(hit, a);
    double dis2 = distance(hit2, a);

    if (dis1 < dis2) return hit;
    else return hit2;
}


#endif // GEOMETRY_H_INCLUDED
