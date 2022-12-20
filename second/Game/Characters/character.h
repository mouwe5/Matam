#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../Game/Auxiliaries.h"
#include "vector"
#include <memory>
#include "../Game/Exceptions.h"

namespace mtm{

    //template<class T>
    class Character
    {
        private:
        
        protected:
        int health;
        int ammo;
        int range;
        int power;
        Team team;
        CharacterType type;
        Character() = default;
        Character( int health , int ammo, int range , int power ,  Team team ,  CharacterType type);
        virtual ~Character() = default;
        
        
        public:
        virtual Character*  clone() const= 0;
        virtual void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        virtual void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        virtual void reload(const GridPoint& coordinates);
        virtual int getSteps() const;
        virtual int getReloadAmmo() ;
        virtual void lostAmmo() ;
        virtual void updateHealth(int); 
        virtual int getHealth()const;
        virtual int getAmmo()const;
        virtual int getRange()const;
        virtual int getAmmoPerAttack()const;
        virtual int getPower()const;
        virtual Team getTeam()const;
        virtual CharacterType getType()const;
        virtual bool possibleAttack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)const; 
        virtual void attackByCharacter(std::vector<std::vector<std::shared_ptr<Character>>>& first,const GridPoint& src_coordinates, const GridPoint& dst_coordinates);


    };


};


#end


