#ifndef _Player_H_
#define _Player_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Group.h"
#include "PlayerSeat.h"

class Player
{
    int playerID;
    int groupID;
    int level;
    int scale;
    Group* group;

public:
    /***********************************************************
         * Player: constructor for Player
         * 
         * @param playerID the player's ID
         * @param groupID the player's Group ID
         * @param level the player's level
         ***********************************************************/
    Player(int playerID, int groupID, int level) : playerID(playerID), groupID(groupID), level(level) {}

    int getPlayerID() const;
    Group *getGroupPointer() const;
    // todo: operators

    void setGroup(Group *group_p);
    int getLevel();
    void setLevel(int new_level);
    void increaseLevel(int increase_by);
    /*
    friend bool operator<(const Player &player_1, const Player &player_2);
    friend bool operator<=(const Player &player_1, const Player &player_2);
    friend bool operator>(const Player &player_1, const Player &player_2);
    friend bool operator>=(const Player &player_1, const Player &player_2);
    friend bool operator==(const Player &player_1, const Player &player_2);
    friend bool operator!=(const Player &player_1, const Player &player_2);
    */
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
/*
bool operator<(Player const&player_1, const Player const&player_2);
bool operator<=(Player const&player_1, const Player &player_2);
bool operator>(Player const&player_1, const Player &player_2);
bool operator>=(Player const&player_1, const Player &player_2);
bool operator==(Player const&player_1, const Player &player_2);
bool operator!=(Player const&player_1, const Player &player_2);
*/
/*
bool operator<(const Player &player_1, const Player &player_2);
bool operator<=(const Player &player_1, const Player &player_2);
bool operator>(const Player &player_1, const Player &player_2);
bool operator>=(const Player &player_1, const Player &player_2);
bool operator==(const Player &player_1, const Player &player_2);
bool operator!=(const Player &player_1, const Player &player_2);
*/

#endif
