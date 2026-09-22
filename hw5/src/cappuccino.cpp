#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino(){
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap){
    name = cap.name;
    ingredients.clear();
    side_items.clear();
    for(const auto& i:cap.ingredients)
        ingredients.push_back(i->clone());
    for(const auto& i:cap.side_items)
        side_items.push_back(i->clone());
}

void Cappuccino::operator=(const Cappuccino& cap){
    if(this == &cap)return;
    name = cap.name;
    
    ingredients.clear();
    side_items.clear();
    for(const auto& i:cap.ingredients)
        ingredients.push_back(i->clone());
    for(const auto& i:cap.side_items)
        side_items.push_back(i->clone());
}

Cappuccino::~Cappuccino(){
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

std::string Cappuccino::get_name(){
    return name;
}

double Cappuccino::price(){
    double sum=0;
    for(const auto& i:ingredients)
        sum += i->price();
    for(const auto& i:side_items)
        sum+= i->price();
    return sum;
}

void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}