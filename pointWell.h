#pragma once
#include "types.h"
#include <iostream>
#include <cstdint>

class pointWell
{
public:
    bool setMax(welltype newMax){
        if(newMax < 1){
            return false;
        }
            
        MaxWell = newMax;

        if(CurrentFullness > MaxWell){
            CurrentFullness = MaxWell;

            return true;
        }
    }

    welltype getMax(){
        return MaxWell;
    }

    welltype getCurrent(){
        return CurrentFullness;
    }

    bool isFull() { return (CurrentFullness == MaxWell); }

    void reduceCurrent(welltype dmg){
        if(dmg > CurrentFullness){
            CurrentFullness = 0;
            return;
        }

        CurrentFullness  -= dmg;
    }

    void increaseCurrent(welltype increaseAmount){
        if(increaseAmount + CurrentFullness > MaxWell){
            CurrentFullness  = MaxWell;
            return;
        }

        CurrentFullness += increaseAmount;
    }

    pointWell() { CurrentFullness = 1; MaxWell  = 1; }
     
    pointWell(welltype c, welltype m){
        CurrentFullness  = c;
        MaxWell  = m;
        if(CurrentFullness > MaxWell){
            CurrentFullness = MaxWell;
        }
    }

private:
    welltype CurrentFullness; // current increaseth points
    welltype MaxWell; // maximum increaseth points
    //welltype ShieldPts; // shield points
};