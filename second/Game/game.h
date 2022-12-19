#include <vector>
#include <memory>
#include "../Characters/character.h"
#include "../Characters/soldier.h"
#include "../Characters/medic.h"
#include "../Characters/sniper.h"
#include "Auxiliaries.h"

namespace mtm{
    class Game {

        private:
        int row;
        int col;
        std::vector<std::vector<std::shared_ptr<Character>>> Board;
        std::vector<std::vector<std::shared_ptr<Character>>> createBoard(int , int);
        void copyAndAllocate (std::vector<std::vector<std::shared_ptr<Character>>>& first, const std::vector<std::vector<std::shared_ptr<Character>>>& second);
        void deleteBoard ();
        void attackBySoldier(const GridPoint & src_coordinates,const GridPoint & dst_coordinates);
        void attackByMedic(const CharacterType MEDIC,const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void attackBySniper(const CharacterType SNIPER,const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        public:
        Game(int row , int col); 
        ~Game();
        Game(const Game& other);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,units_t health,units_t ammo,units_t range,units_t power);
        void addCharacter(const GridPoint coordinates, std::shared_ptr<Character> character);
        Game& operator=(const Game& other) ;
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint& coordinates);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        bool isOver(Team* winningTeam=NULL) const;
        friend std::ostream &operator<<(std::ostream& , const Game&);
    };  
};