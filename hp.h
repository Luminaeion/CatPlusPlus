#include <iostream>
#include <cstdint>

typedef std::uint32_t hptype;

class hp
{
public:
    bool setMaxHP(hptype newMaxHP){
        if(newMaxHP < 1){
            return false;
        }
            
        MaxHP = newMaxHP;

        if(CurrentHP > MaxHP){
            CurrentHP = MaxHP;

            return true;
        }
    }

    hptype getMaxHP(){
        return MaxHP;
    }

    hptype getCurrentHP(){
        return CurrentHP;
    }

    /*hptype getShieldPts(){
        return ShieldPts;
    }*/

    void dmgTaken(hptype dmg){
        if(dmg > CurrentHP){
            CurrentHP = 0;
            return;
        }

        /*if(ShieldPts > 0)
        ShieldPts -= dmg;

        if(ShieldPts < 1)*/
        CurrentHP -= dmg;
    }

    void heal(hptype healAmount){
        if(healAmount + CurrentHP > MaxHP){
            CurrentHP = MaxHP;
            return;
        }

        CurrentHP += healAmount;
    }

    hp() { CurrentHP = 1; MaxHP = 1; }
    hp(hptype cHP, hptype mHP){
        CurrentHP = cHP;
        MaxHP = mHP;
        if(CurrentHP > MaxHP){
            CurrentHP = MaxHP;
        }
    }

private:
    hptype CurrentHP; // current health points
    hptype MaxHP; // maximum health points
    //hptype ShieldPts; // shield points
};