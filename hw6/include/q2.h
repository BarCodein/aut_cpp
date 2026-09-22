#ifndef Q2_H
#define Q2_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
namespace q2{
    struct Patient{
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;

        bool operator<(const struct Patient& other){
            return ((3*age+5*smokes+2*area_q+4*alkhol) >
            (3*other.age+5*other.smokes+2*other.area_q+4*other.alkhol));
        }
    };
    size_t convert(std::string s){
        std::stringstream ss(s);
        size_t re;
        ss>>re;
        return re;
    }

    std::vector<Patient> read_file(std::string filename){

        std::vector<Patient> vp;
        std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr<< "无法打开文件"<<filename<<std::endl;
            return  vp;
        }

        std::string line;
        std::getline(file,line);//title
        std::getline(file,line);//colon
        while(getline(file,line)){
            if(line.empty())continue;
            std::stringstream ss(line);
            std::string name,surname,sage,ssmokes,sarea_q,s_alkhol;
            size_t age,smokes,area_q,alkhol;
            std::getline(ss,name,',');
            std::getline(ss,surname,',');
            std::getline(ss,sage,',');
            std::getline(ss,ssmokes,',');
            std::getline(ss,sarea_q,',');
            std::getline(ss,s_alkhol,',');
            std::stringstream ssname(name),sssurename(surname);
            ssname>>name;
            sssurename>>surname;
            age = convert(sage);
            smokes = convert(ssmokes);
            area_q = convert(sarea_q);
            alkhol = convert(s_alkhol);
            Patient p={name+" "+surname,age,smokes,area_q,alkhol};
            vp.push_back(p);
        }
        return vp;
    }

    void sort(std::vector<Patient>& vp){
        std::sort(vp.begin(),vp.end());
    }
};
#endif //Q2_H