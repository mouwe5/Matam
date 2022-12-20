#include "soldier.h"
#define STEPS 3
#define AMMO_TO_RELOAD 3
#define AMMO_USED 1
#define POWER_SCALE 3
#define DAMAGE_SCALE 2

using namespace mtm;
using namespace std;

    Soldier::Soldier( int health , int ammo, int range , int power ,  Team team , CharacterType type):
    Character(health ,ammo ,range ,power, team , type)
    {
    
    }

    int Soldier::getSteps() const
    {
        return STEPS;
    }

    int Soldier::getReloadAmmo()
    {
        return AMMO_TO_RELOAD;
    }

    void Soldier::lostAmmo() 
    {
        this->ammo-=AMMO_USED;
    }

    //if character damaged point<0 , if healed points>0
    void Soldier::updateHealth(int points) 
    {
        this->health+=points;
    }

    int Soldier::getHealth() const
    {
        return this->health;
    }

    int Soldier::getAmmo()const
    {
        return this->ammo;
    }

    int Soldier::getRange()const
    {
        return this->range;
    }

    int Soldier::getPower()const
    {
        return this->power;
    }

    Team Soldier::getTeam()const
    {
        return this->team;
    }

    CharacterType Soldier::getType()const
    {
        return this->type;
    }

    bool Soldier::possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const
    {
        if(src_coordinates.row == dst_coordinates.row || src_coordinates.col == dst_coordinates.col)
        {
            return src_coordinates.distance(src_coordinates,dst_coordinates)<=range;
        }
        
        return false;
    }

    bool Soldier::damagedByAttack(const GridPoint& attack_coordinates, const GridPoint& character_coordinates)const
    {
        int new_range = ceil((double)range/(double)POWER_SCALE);
        return attack_coordinates.distance(attack_coordinates,character_coordinates)<=new_range;
    }

    Soldier::Soldier(const Soldier& other):
    Character(health ,ammo ,range ,power, team , type)
    {

    }

    Character* Soldier::clone() const 
    {
        return new Soldier(*this);
    }
    int Soldier::getAmmoPerAttack()const
    {
        return AMMO_USED;
    }


void Soldier::attackByCharacter(vector<vector<shared_ptr<Character>>>& board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
{
    int area_damage = ceil((double)power/(double)DAMAGE_SCALE);
    for(int i=0; i<board.size() ; i++)
        {
        for(int j=0 ; j<board[i].size() ; j++)
        {
            if(board.at(i).at(j)!= nullptr && board.at(i).at(j)->getTeam()!=team) // not empty cell and not a teammate
            {
                GridPoint enemy(i,j);
                if(this->damagedByAttack(dst_coordinates,enemy))
                {
                    if(enemy==dst_coordinates) // strike attack
                    {
                        board.at(i).at(j)->updateHealth(-power);
                    }
                    else //area attack
                    {
                        board.at(i).at(j)->updateHealth(-area_damage);
                    }
                    if(board.at(i).at(j)->getHealth()<=0)
                    {
                        delete& board.at(i).at(j);
                        board.at(i).at(j) =nullptr;
                    }
                }
            }
        }
    }
    }
    