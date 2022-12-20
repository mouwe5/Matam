#ifndef SOLDIER_H_
#define SOLDIER_H_
#include "character.h"
    
namespace mtm{    
    
    class Soldier : public Character
    {
        public:
        Soldier(const Soldier& other);
        Character *clone() const override;
        Soldier( int health , int ammo, int range , int power ,  Team team , CharacterType type);
        ~Soldier()= default;
        int getSteps() const; 
        int getReloadAmmo() ; 
        void lostAmmo() ; 
        void updateHealth(int); 
        int getHealth()const;
        int getAmmo()const;
        int getRange()const;
        int getAmmoPerAttack()const;
        int getPower()const;
        Team getTeam()const;
        CharacterType getType()const;
        bool possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const;
        void attackByCharacter(std::vector<std::vector<std::shared_ptr<Character>>>& first,const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        bool damagedByAttack(const GridPoint& attack_coordinates, const GridPoint& character_coordinates)const;

    };

    

};

#endif //CHARACTER_H_
