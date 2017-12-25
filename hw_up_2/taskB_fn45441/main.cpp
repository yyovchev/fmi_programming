#include "geometry.h"
#include <iostream>

using namespace std;

void round(point starting_point, point direction_poin, int round_n = 1);


struct GameConfig {
    int width;
    int height;
    point target;
    double targetRadius;
    int maxReflect;
    int mirrorCount;
    line mirrors[14];
} room;

int main()
{
    double input[]  = {10, 6, 1, 3, 1, 6, 6, 6, 5, 50, 1, 7, 4, 5, 2};

    point starting_point;
    point direction_poin;

    room.width = input[0];
    room.height = input[1];

    room.target.x = input[2];
    room.target.y = input[3];

    room.targetRadius = input[4];

    starting_point.x = input[5];
    starting_point.y = input[6];

    direction_poin.x = input[7];
    direction_poin.y = input[8];

    room.maxReflect = input[9];
    room.mirrorCount = input[10]+4;

    room.mirrors[0].set_value(0,0,room.width,0);
    room.mirrors[1].set_value(0,0,0,room.height);
    room.mirrors[2].set_value(0,room.height,room.width,room.height);
    room.mirrors[3].set_value(room.width,0,room.width,room.height);

    for (int i = 0, br = 0, mr_br = 0; i<input[10] ; i++,br+=4,mr_br++){

        if (input[10+br+1] == input[10+br+3] && input[10+br+2] == input[10+br+4]){
            mr_br --;
            room.mirrorCount--;
        }
        else
            room.mirrors[3+br].set_value(input[10+br+1],input[10+br+2],input[10+br+3],input[10+br+4]);
    }

    round(starting_point, direction_poin);

    return 0;
}

void round(point starting_point, point direction_poin, int round_n){

    if (round_n > room.maxReflect){
        cout<<"sorry you didnt hit the target\n";
        return;
    }

    cout<<"round "<<round_n<<endl;
    cout<<"starting point  (x,y) : "<<starting_point.x<<"  "<<starting_point.y<<endl;
    cout<<"direction point (x,y) : "<<direction_poin.x<<"  "<<direction_poin.y<<endl;

    line ray(starting_point, direction_poin);

    double min_distance = room.height * room.width;

    point n_starting_point, n_direction_poin;

    for(int i = 0; i<room.mirrorCount; i++){
        point cpoint;

        if (parallel(ray,room.mirrors[i])) continue;

        cpoint = cross_point(ray, room.mirrors[i]);
        double distance_to_line = distance(cpoint,ray);

        if (distance_to_line > 0 && distance_to_line < min_distance){
            min_distance = distance_to_line;
            n_starting_point = cpoint;
            n_direction_poin = symmetrical_point(ray, room.mirrors[i]);
        }

    }

    double r_dis = distance_point_to_line(room.target, ray);
    if (r_dis < room.targetRadius ){
        point hit = point_on_c(room.target,room.targetRadius,ray);
        double dis = distance(hit, ray);

        if (dis > 0 && dis < min_distance){
            cout<<"You hit the target at point x:"<<hit.x<<" y:"<<hit.y<<endl;
            return;
        }
    }

    round(n_starting_point, n_direction_poin, ++round_n);

}

