#ifndef MEDIC_H_
#define MEDIC_H_


#include "character.h"
    
namespace mtm{    
    
    class Medic : public Character
    {
        public:
        Medic(const Medic& other);
        Character* clone() const override;
        Medic(const int health ,const int ammo,const int range ,const int power , const Team team ,const CharacterType type);
        ~Medic()= default;
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
        void attackByCharacter(std::vector<std::vector<std::shared_ptr<Character>>>& board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates);

    };

};

#endif