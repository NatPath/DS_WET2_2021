#ifndef _Player_H_
#define _Player_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library2.h"
#include "Avl.h"
#include "Group.h"
#include "PlayerSeat.h"
#include "List.h"

class Player
{
    int playerID;
    int groupID;
    int level;
    int score;


public:
    /***********************************************************
         * Player: constructor for Player
         * 
         * @param playerID the player's ID
         * @param groupID the player's Group ID
         * @param level the player's level
         ***********************************************************/
    Player(int playerID, int groupID, int score);


    int getPlayerID() const;

    int getLevel();
    void setLevel(int new_level);
    void increaseLevel(int increase_by);

    int getScore();
    void setScore(int new_score);



    friend bool operator<(Player const&player_1, Player const&player_2);
    friend bool operator<=(Player const&player_1, Player const&player_2);
    friend bool operator>(Player const&player_1, Player const&player_2);
    friend bool operator>=(Player const&player_1, Player const&player_2);
    friend bool operator==(Player const&player_1, Player const&player_2);
    friend bool operator!=(Player const&player_1, Player const&player_2);



};
bool operator<(Player const&player_1, Player const&player_2);
bool operator<=(Player const&player_1, Player const&player_2);
bool operator>(Player const&player_1, Player const&player_2);
bool operator>=(Player const&player_1, Player const&player_2);
bool operator==(Player const&player_1, Player const&player_2);
bool operator!=(Player const&player_1, Player const&player_2);

#endif
