#include "sniper.h"


#define STEPS 4  
#define AMMO_TO_RELOAD 2
#define AMMO_USED 1
#define POWER_SCALE 2
#define STRIKE_COMBO 3
#define STRIKE_DAMEGE 2

using namespace mtm;
using namespace std;

    Sniper::Sniper(const int health ,const int ammo,const int range ,const int power , const Team team ,const CharacterType type):
    Character(health ,ammo ,range ,power, team , type)
    {
        strike_attack=0;
    }

    int Sniper::getSteps() const
    {
        return STEPS;
    }

    int Sniper::getReloadAmmo()
    {
        return AMMO_TO_RELOAD;
    }

    void Sniper::lostAmmo() 
    {
        this->ammo-=AMMO_USED;
    }

    //if character damaged point<0 , if healed points>0
    void Sniper::updateHealth(int points) 
    {
        this->health+=points;
    }

    int Sniper::getHealth() const
    {
        return this->health;
    }

    int Sniper::getAmmo()const
    {
        return this->ammo;
    }

    int Sniper::getRange()const
    {
        return this->range;
    }

    int Sniper::getPower()const
    {
        return this->power;
    }

    Team Sniper::getTeam()const
    {
        return this->team;
    }

    CharacterType Sniper::getType()const
    {
        return this->type;
    }

    bool Sniper::possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const
    {
        int distance = src_coordinates.distance(src_coordinates,dst_coordinates);
        int minimum_distance = ceil((double)range/(double)POWER_SCALE);
        return (distance<=range && distance>=minimum_distance);
    }

    void Sniper::attackOccurred()
    {
        strike_attack++;
        if(strike_attack%STRIKE_COMBO==0)
        {
            power=power*STRIKE_DAMEGE;
        }
        if(strike_attack%STRIKE_COMBO==1 && strike_attack!=1)
        {
            power=power/STRIKE_DAMEGE;
        }
    }

    Sniper::Sniper(const Sniper& other):
    Character(health ,ammo ,range ,power, team , type)
    {

    }

    Character* Sniper::clone() const 
    {
        return new Sniper(*this);
    }
    int Sniper::getAmmoPerAttack()const
    {
        return AMMO_USED;
    }

    void Sniper::attackByCharacter(vector<vector<shared_ptr<Character>>>& board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
    {
        shared_ptr<Character> target = board.at(dst_coordinates.col).at(dst_coordinates.row);
        if(target==nullptr || target->getTeam() == team )
        {
            throw IllegalTarget();
        }
        this->attackOccurred();
        this->lostAmmo();
        target->updateHealth(this->getPower());
        if(target->getHealth()<=0)
        {
            delete &target;
            target=nullptr;
        }
    }
