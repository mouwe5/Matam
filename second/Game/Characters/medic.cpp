 
#include "medic.h"

#define STEPS 5
#define AMMO_TO_RELOAD 5
#define AMMO_USED 1
#define POWER_SCALE 3

using namespace mtm ;
using namespace std ;
    Medic::Medic(const int health ,const int ammo,const int range ,const int power , const Team team ,const CharacterType type):
    Character(health ,ammo ,range ,power, team , type)
    {
    
    }

    int Medic::getSteps() const
    {
        return STEPS;
    }

    int Medic::getReloadAmmo()
    {
        return AMMO_TO_RELOAD;
    }

    void Medic::lostAmmo() 
    {
        this->ammo-=AMMO_USED;
    }

    //if character damaged point<0 , if healed points>0
    void Medic::updateHealth(int points) 
    {
        this->health+=points;
    }

    int Medic::getHealth() const
    {
        return this->health;
    }

    int Medic::getAmmo()const
    {
        return this->ammo;
    }

    int Medic::getRange()const
    {
        return this->range;
    }

    int Medic::getPower()const
    {
        return this->power;
    }

    Team Medic::getTeam()const
    {
        return this->team;
    }

    CharacterType Medic::getType()const
    {
        return this->type;
    }

    bool Medic::possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const
    {
        int distance = src_coordinates.distance(src_coordinates,dst_coordinates);
        return (distance<=range && distance>0) ;
    }
    Medic::Medic(const Medic& other):
    Character(health ,ammo ,range ,power, team , type)
    {

    }

    Character* Medic::clone() const 
    {
        return new Medic(*this);
    }
    int Medic::getAmmoPerAttack()const
    {
        return AMMO_USED;
    }
    void Medic::attackByCharacter(vector<vector<shared_ptr<Character>>>& board , const GridPoint& src_coordinates, const GridPoint& dst_coordinates )
    {
        shared_ptr<Character> target = board.at(dst_coordinates.col).at(dst_coordinates.row);
        if(target->getTeam() != this->getTeam())
        {
            this->lostAmmo();
            target->updateHealth(-power);

        }
        if(target->getTeam() == this->getTeam())
        {
            target->updateHealth(+power);
        }
        if(target->getHealth()<=0)
        {
            delete &target;
            target=nullptr;
        }
    }