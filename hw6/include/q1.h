#ifndef Q1_H
#define Q1_H



template<typename T,typename Func>
double update(T start,T step_size,
Func func){
    double dmin=func(start),imin =start;
    if(func(start-step_size)<func(start)){
        imin = start-step_size;
        dmin = func(imin);
    }
    if(func(start+step_size)<dmin){
        imin = start+step_size;
        dmin = func(imin);
    }
    return imin;
}

namespace q1{
    template<typename T,typename Func>
    T gradient_descent(T initv,T step_size,Func func=Func{}){
        T ivar=initv,dvar = func(initv);
        while(update(ivar,step_size,func)!=ivar){
            ivar = update(ivar,step_size,func);
            dvar = func(ivar);
        }
        return ivar;
    }
    
}

#endif //Q1_H