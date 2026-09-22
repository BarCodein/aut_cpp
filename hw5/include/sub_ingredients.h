#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H


class Cinnamon : public Ingredient {
    public:
        Cinnamon(size_t units) : Ingredient{5,units}{
            this->name = "Cinnamon";
        }
        Ingredient* clone()override{
            return new Cinnamon(this->units);
        }
        virtual std::string get_name(){return this->name;}
};

class Chocolate : public Ingredient {
    public:
        Chocolate(size_t units) : Ingredient{5,units}{
            this->name = "Chocolate";
        }
        Ingredient* clone()override{
            return new Chocolate(this->units);
        }
        virtual std::string get_name(){return this->name;}
};

class Sugar :public Ingredient {
    public:
        Sugar(size_t units) : Ingredient{1,units}{
            this->name = "Sugar";
        }
        Ingredient* clone()override{
            return new Sugar(this->units);
        }
        std::string get_name()override{return this->name;}
};

class Cookie : public Ingredient {
    public:
        Cookie(size_t units) : Ingredient{10,units}{
            this->name = "Cookie";
        }
        Ingredient* clone()override{
            return new Cookie(this->units);
        }
        std::string get_name()override{return this->name;}
};

class Espresso : public Ingredient{
    public :
        Espresso(size_t units) : Ingredient{15,units}{
            this->name = "Espresso";
        }
        Ingredient* clone()override{
            return new Espresso(this->units);
        }
        std::string get_name() override{return this->name;}
};

class Milk : public Ingredient{
    public :
        Milk(size_t units) : Ingredient{10,units}{
            this->name = "Milk";
        }
        Ingredient* clone()override{
            return new Milk(this->units);
        }
        std::string get_name() override{return this->name;}
};

class MilkFoam : public Ingredient{
    public :
        MilkFoam(size_t units) : Ingredient{5,units}{
            this->name = "MilkFoam";
        }
        Ingredient* clone()override{
            return new MilkFoam(this->units);
        }
        std::string get_name() override{return this->name;}
};

class Water : public Ingredient{
    public :
        Water(size_t units) : Ingredient{1,units}{
            this->name = "Water";
        }
        Ingredient* clone()override{
            return new Water(this->units);
        }
        std::string get_name() override{return this->name;}
};

#endif // SUB_INGREDIENTS_H