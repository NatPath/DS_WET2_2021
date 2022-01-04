#include "Player.h"

int Player::getPlayerID() const
{
    return playerID;
}

Group *Player::getGroupPointer() const
{
    return group;
}

int Player::getLevel()
{
    return level;
}

void Player::setGroup(Group *new_group_p)
{
    group = new_group_p;
    groupID = new_group_p->getID();
}

void Player::setLevel(int new_level)
{
    level = new_level;
}

bool operator<(Player const &player_1, Player const &player_2)
{
    if (player_1.level < player_2.level)
    {
        return true;
    }
    else if ((player_1.level == player_2.level) && (player_2.playerID < player_1.playerID))
    {
        return true;
    }

    return false;
}
bool operator<=(Player const &player_1, Player const &player_2)
{
    return !(player_1 > player_2);
}
bool operator>(Player const &player_1, Player const &player_2)
{
    if (player_1.level > player_2.level)
    {
        return true;
    }
    else if ((player_1.level == player_2.level) && (player_2.playerID > player_1.playerID))
    {
        return true;
    }

    return false;
}
bool operator>=(Player const &player_1, Player const &player_2)
{
    return !(player_1 < player_2);
}

bool operator==(Player const &player_1, Player const &player_2)
{
    if ((player_1.level == player_2.level) && (player_2.playerID == player_1.playerID))
    {
        return true;
    }
    return false;
}
bool operator!=(Player const &player_1, Player const &player_2)
{
    return !(player_1 == player_2);
}

/*
bool operator<(const Player &player_1, const Player &player_2)
{
    if (player_1.level < player_2.level)
    {
        return true;
    }
    else if ((player_1.level == player_2.level) && (player_2.playerID < player_1.playerID))
    {
        return true;
    }

    return false;
}
bool operator<=(const Player &player_1, const Player &player_2){
    return !(player_1>player_2);
}
bool operator>(const Player &player_1, const Player &player_2)
{
    if (player_1.level > player_2.level)
    {
        return true;
    }
    else if ((player_1.level == player_2.level) && (player_2.playerID > player_1.playerID))
    {
        return true;
    }

    return false;
}
bool operator>=(const Player &player_1, const Player &player_2){
    return !(player_1<player_2);
}

bool operator==(const Player &player_1, const Player &player_2)
{
    if ((player_1.level == player_2.level) && (player_2.playerID == player_1.playerID))
    {
        return true;
    }
    return false;
}
bool operator!=(const Player &player_1, const Player &player_2){
    return !(player_1==player_2);
}
*/