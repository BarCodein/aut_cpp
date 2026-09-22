#ifndef Q3_H
#define Q3_H
#include<string>
#include<queue>
#include<fstream>
#include<iostream>
#include<sstream>

size_t calc_time(std::string s){
    size_t h,m=0;
    std::string v;
    std::stringstream ss(s);
    ss>>h>>v;
    if(!ss.eof()){
        ss>>m;
    }
    m+= h *60;
    return m;
}

size_t tonum(std::string s){
    std::stringstream ss(s);
    size_t re;
    ss>>re;
    return re;
}

size_t calc_con(std::string s,size_t t){
    size_t re=0;
    std::stringstream ss(s);
    for(size_t i=0;i<t;i++){
        std::string sct;
        std::getline(ss,sct,',');
        re+=calc_time(sct);
    }
    return re;
}
namespace q3{
    struct Flight{
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;

        bool operator<(const Flight& other)const{
            return ((duration+connection_times+3*price)>
        (other.duration+other.connection_times+3*other.price));
        }
    };
    std::priority_queue<Flight> gather_flights(std::string filename){
        std::priority_queue<Flight> qf;
        std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr<<"fail to openfile "<<filename<<std::endl;
            return qf;
        }
        std::string line;
        while(std::getline(file,line)){
            Flight f;
            if(line.empty())continue;
            std::stringstream ss(line);
            std::string s;
            ss>>s; // remove head
            ss>>s;
            f.flight_number = s.substr(14);
            ss>>s; //-
            ss>>s;
            f.duration = calc_time( s.substr(9));
            ss>>s; //-
            ss>>s;
            f.connections = tonum(s.substr(12));
            ss>>s; //-
            ss>>s;
            f.connection_times = calc_con(s.substr(17),f.connections);
            ss>>s; //-
            ss>>s;
            f.price = tonum(s.substr(6));
            qf.push(f);
        }
        return qf;
    }
}

#endif //Q3_H