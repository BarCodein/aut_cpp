#ifndef Q4_H
#define Q4_H
#include<vector>
namespace q4{
    struct Vector2D{
        double x{};
        double y{};
    };

    struct Sensor{
        Vector2D pos;
        double accuracy;
    };

    Vector2D kalman_filter(std::vector<Sensor> sensors){
        double we_sum=0;
        struct Vector2D v;
        for(const auto& i:sensors){
            v.x+=i.pos.x * i.accuracy;
            v.y+=i.pos.y * i.accuracy;
            we_sum +=i.accuracy;
        }
        v.x = v.x / we_sum;
        v.y = v.y / we_sum;
        return v;
    }
}

#endif //Q4_H