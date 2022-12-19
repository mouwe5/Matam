#include "game.h"
#include "Exceptions.h"
using namespace mtm;
using namespace std;

#define CROSS_SOLDIER_SYMBOL 's'
#define CROSS_SNIPER_SYMBOL 'n'
#define CROSS_MEDIC_SYMBOL 'm'
#define POWER_SOLDIER_SYMBOL 'S'
#define POWER_SNIPER_SYMBOL 'N'
#define POWER_MEDIC_SYMBOL 'M'




Game::Game(int row , int col)
{
    if(row<1 || col<1)
    {
        throw IllegalArgument();
    }
    this->row=row;
    this->col=col;
    Board = createBoard(row,col);
}


vector<vector<shared_ptr<Character>>> Game::createBoard(int row, int col)
{

    vector<vector<shared_ptr<Character>>> Board;
    for(int i=0; i<row ; i++)
    {
        vector<shared_ptr<Character>> row(row);
        
        for(int j=0 ; j<col ; j++)
        {
            row[j] = nullptr;
        }
        Board.push_back(row);
    }
    /*
    for(int i=0 ; i<Board.size() ; i++)
    {
        for(int j=0 ; j<Board[i].size() ; j++)
        {
            cout << Board[i][j];
        }
        cout << endl; 
    }
    */
    return Board;
}

Game::~Game()
{
 this->deleteBoard();
}

void Game::deleteBoard ()
{
    for(int j=0 ; j<row ; j++)
    {
        //board[j].clear ????
        delete[] &Board[j];
    }
    
    delete[] &Board;
}
void Game::copyAndAllocate (vector<vector<shared_ptr<Character>>>& first,const vector<vector<shared_ptr<Character>>>& second)
{
   
    for(int i=0; i<row ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
            if(second[i][j] != nullptr)
            {
                Character* add = (second[i][j])->clone();
                first[i][j] = makeCharacter(add->getType(),add->getTeam(),add->getHealth(),add->getAmmo(),add->getRange(),add->getPower());

            }
        }
    }

}
    

Game::Game(const Game& other)
{
    row = other.row;
    col = other.col;
    Board = createBoard(row,col);
    copyAndAllocate(this->Board,other.Board);
}

shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,units_t health,units_t ammo,units_t range,units_t power)
{
    if(health<1||ammo<0||range<0||power<0)
    {
        throw IllegalArgument();
    }
    if(type==SOLDIER)
    {
        shared_ptr<Character> ptr(new Soldier(health,ammo,range,power,team,type));
        return ptr;
    }
    if(type==MEDIC)
    {
        shared_ptr<Character> ptr(new Medic(health,ammo,range,power,team,type));
        return ptr;
    }
    else //sniper
    {
        shared_ptr<Character> ptr(new Sniper(health,ammo,range,power,team,type));
        return ptr;
    }

}

Game& Game::operator=(const Game& other)
{
    if(this == &other)
    {
        return *this;
    }
    vector<vector<shared_ptr<Character>>> temp_board = createBoard(other.row,other.col);
    copyAndAllocate(temp_board,other.Board);
    this->deleteBoard();
    this->Board = temp_board;
    return *this;
}

void Game::addCharacter(const GridPoint coordinates, shared_ptr<Character> character)
{
    if(coordinates.col<0 || coordinates.col >= col ||coordinates.row<0 || coordinates.row>=row)
    {
        throw IllegalCell();
    }
    if(Board.at(coordinates.col).at(coordinates.row)!=NULL)
    {
        throw CellOccupied();
    }
    Board.at(coordinates.col).at(coordinates.row)= character;
    
}

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    if(src_coordinates.col<0 || src_coordinates.col >= col ||src_coordinates.row<0 || src_coordinates.row>=row ||
        dst_coordinates.col<0 || dst_coordinates.col >= col ||dst_coordinates.row<0 || dst_coordinates.row>=row)
    {
        throw IllegalCell();
    }
    if(Board.at(src_coordinates.col).at(src_coordinates.row)==NULL)
    {
        throw CellEmpty();
    }
   
    if(Board.at(src_coordinates.col).at(src_coordinates.row)->getSteps() > GridPoint::distance(src_coordinates,dst_coordinates))
    {
        throw MoveTooFar();
    }
    if(Board.at(dst_coordinates.col).at(dst_coordinates.row)!=NULL)
    {
        throw CellOccupied();
    }

    Board.at(dst_coordinates.col).at(dst_coordinates.row)=Board.at(src_coordinates.col).at(src_coordinates.row);
    Board.at(src_coordinates.col).at(src_coordinates.row)=nullptr;   
}

void Game::reload(const GridPoint& coordinates)
{
    if(coordinates.col<0 || coordinates.col >= col ||coordinates.row<0 || coordinates.row>=row)
    {
        throw IllegalCell();
    }
    if(Board.at(coordinates.col).at(coordinates.row)==NULL)
    {
        throw CellEmpty();
    }
    Board.at(coordinates.col).at(coordinates.row)->getReloadAmmo();
}

void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    shared_ptr<Character> character = Board.at(src_coordinates.col).at(src_coordinates.row);
     shared_ptr<Character> enemy = Board.at(dst_coordinates.col).at(dst_coordinates.row);
    if(src_coordinates.col<0 || src_coordinates.col >= col ||src_coordinates.row<0 || src_coordinates.row>=row ||
        dst_coordinates.col<0 || dst_coordinates.col >= col ||dst_coordinates.row<0 || dst_coordinates.row>=row)
    {
        throw IllegalCell();
    }
    if(character==NULL)
    {
        throw CellEmpty();
    }
    if(character->getRange()-GridPoint::distance(src_coordinates,dst_coordinates)<0)
    {
        throw OutOfRange();
    }
    if(character->getType()==SOLDIER||character->getType()==SNIPER)
    {
        if(character->getAmmo()-character->getAmmoPerAttack()<0)
        {
            throw OutOfAmmo();
        }
    }
    else //medic attack
    {
        if(enemy != nullptr && character->getTeam()!=enemy->getTeam()&&character->getAmmo()-character->getAmmoPerAttack()<0)
        {
           throw OutOfAmmo();
        }
    }
    if(character->possibleAttack(src_coordinates,dst_coordinates))
    {
        throw IllegalTarget();
    }
    character->attackByCharacter(Board,src_coordinates,dst_coordinates);

}

namespace mtm {
    ostream&  operator<<(ostream& os,const Game& game)
    {
        char board[game.row][game.col] = {};
        char* start = board[0],*end = board[0];
        for(int i=0;i<game.row;i++)
        {
            for(int j=0;j<game.col;j++)
            {
                if(game.Board.at(i).at(j)==nullptr)
                {
                    board[i][j]=' ';
                }
                else
                {
                    if(game.Board.at(i).at(j)->getTeam()==CROSSFITTERS)
                    {
                        if(game.Board.at(i).at(j)->getType()==SOLDIER)
                        {
                             board[i][j]=CROSS_SOLDIER_SYMBOL;
                        }
                        if(game.Board.at(i).at(j)->getType()==SNIPER)
                        {
                            board[i][j]=CROSS_SNIPER_SYMBOL;
                        }
                        if(game.Board.at(i).at(j)->getType()==MEDIC)
                        {
                            board[i][j]=CROSS_MEDIC_SYMBOL;
                        }
                    }
                    else
                    {
                    if(game.Board.at(i).at(j)->getType()==SOLDIER)
                        {
                             board[i][j]=POWER_SOLDIER_SYMBOL;
                        }
                        if(game.Board.at(i).at(j)->getType()==SNIPER)
                        {
                            board[i][j]=POWER_SNIPER_SYMBOL;
                        }
                        if(game.Board.at(i).at(j)->getType()==MEDIC)
                        {
                            board[i][j]=POWER_MEDIC_SYMBOL;
                        }
                    }

                }
                end++;
            }
        }
        return printGameBoard(cout,start,end,game.col);
    }
};

bool Game::isOver(Team* winningTeam)const
{
    bool powerLifters = false;
    bool crossFitters = false;
    for(int i=0; i<row ; i++)
    {
        for(int j=0 ; j<col ; j++)
        {
            if(Board.at(i).at(j)!=nullptr && Board.at(i).at(j)->getTeam()==CROSSFITTERS)
            {
                crossFitters=true;
            }
            if(Board.at(i).at(j)!=nullptr && Board.at(i).at(j)->getTeam()==POWERLIFTERS)
            {
                powerLifters=true;
            }
            if(powerLifters&&crossFitters)
            {
                return false;
            }
        }
    }
    if(powerLifters)
    {
        *winningTeam = POWERLIFTERS;
        return true;
    }
    if(crossFitters)
    {
        *winningTeam = CROSSFITTERS;
        return true;
    }
    return false;
}






