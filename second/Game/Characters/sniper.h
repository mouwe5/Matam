#ifndef SNIPER_H_
#define SNIPER_H_
#include "character.h"
    
namespace mtm{    
    
    class Sniper : public Character
    {
        private:
        int strike_attack;

        public:
        Sniper(const Sniper& other);
        Character* clone() const override;
        Sniper(const int health ,const int ammo,const int range ,const int power , const Team team ,const CharacterType type);
        ~Sniper()= default;
        int getSteps() const; 
        int getReloadAmmo() ; 
        void lostAmmo() ; 
        void updateHealth(int); 
        int getHealth()const;
        int getAmmoPerAttack()const;
        int getAmmo()const;
        int getRange()const;
        int getPower()const;
        Team getTeam()const;
        CharacterType getType()const;
        bool possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const;
        bool damagedByAttack(const GridPoint& attack_coordinates, const GridPoint& character_coordinates)const;
        void attackOccurred();
        void attackByCharacter(std::vector<std::vector<std::shared_ptr<Character>>>& board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

    };

    
};

#endif
