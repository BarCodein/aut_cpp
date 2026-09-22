#include "mocha.h"
#include "espresso_based.h"
#include "sub_ingredients.h"
#include <vector>
#include <string>

Mocha::Mocha(){
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& moc){
    name = moc.name;
    ingredients.clear();
    side_items.clear();
    for(const auto& i:moc.ingredients)
        ingredients.push_back(i->clone());
    for(const auto& i:moc.side_items)
        side_items.push_back(i->clone());
}

void Mocha::operator=(const Mocha& moc){
    if(this == &moc)return;
    name = moc.name;
    ingredients.clear();
    side_items.clear();
    for(const auto& i:moc.ingredients)
        ingredients.push_back(i->clone());
    for(const auto& i:moc.side_items)
        side_items.push_back(i->clone());
}

Mocha::~Mocha(){
    for(const auto& i :side_items)
        delete i;
    side_items.clear();
}

std::string Mocha::get_name(){
    return name;
}

double Mocha::price(){
    double sum=0;
    for(const auto& i:ingredients)
        sum += i->price();
    for(const auto& i:side_items)
        sum+= i->price();
    return sum;
}

void Mocha::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items(){
    return side_items;
}