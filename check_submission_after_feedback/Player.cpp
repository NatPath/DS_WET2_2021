#include "Player.h"

Player::Player(int playerID, int groupID, int score) : playerID(playerID), groupID(groupID), level(0),score(score){}

int Player::getGroupID() const{
    return groupID;
}
int Player::getPlayerID() const
{
    return playerID;
}

int Player::getLevel()
{
    return level;
}
void Player::setLevel(int new_level)
{
    level = new_level;
}
void Player::increaseLevel(int increase_by){
    level=level+increase_by;
}

int Player::getScore(){
    return score;
}
void Player::setScore(int new_score){
    score= new_score;
}


bool operator<(Player const &player_1, Player const &player_2)
{
    if (player_1.level < player_2.level)
    {
        return true;
    }
    else if(player_1.level == player_2.level){
        if (player_1.playerID==player_2.playerID || player_1.playerID==-1 || player_2.playerID==0){
            return false;
        }
        if (player_1.playerID==0 || player_2.playerID==-1 || player_1.playerID < player_2.playerID){
            return true;
        }
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
    else if(player_1.level == player_2.level){
        if (player_1.playerID==player_2.playerID || player_1.playerID==0 || player_2.playerID==-1){
            return false;
        }
        if (player_1.playerID==-1 || player_2.playerID==0 || player_1.playerID > player_2.playerID){
            return true;
        }
    }
    return false;
}
bool operator>=(Player const &player_1, Player const &player_2)
{
    return !(player_1 < player_2);
}

bool operator==(Player const &player_1, Player const &player_2)
{

    //if ((player_1.level == player_2.level) && (player_2.playerID == player_1.playerID))
    if (player_2.playerID == player_1.playerID)
    {
        return true;
    }
    return false;
}
bool operator!=(Player const &player_1, Player const &player_2)
{
    return !(player_1 == player_2);
}
