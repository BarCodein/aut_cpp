#include "espresso_based.h"
#include<iostream>

EspressoBased::EspressoBased(){
}

EspressoBased::EspressoBased(const EspressoBased& esp){
    name = esp.name;
    ingredients.clear();
    for(const auto& i:esp.ingredients)
        ingredients.push_back(i->clone());
}

void EspressoBased::operator=(const EspressoBased& esp){
    name = esp.name;
    ingredients.clear();
    for(const auto& i:esp.ingredients) 
        ingredients.push_back(i->clone());}

EspressoBased::~EspressoBased(){
    for(const auto& i:ingredients)
        delete i;
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

void EspressoBased::brew(){
    for(const auto& i: ingredients)
        std::cout<<i->get_name()<<std::endl;
}