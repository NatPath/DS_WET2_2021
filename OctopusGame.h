#ifndef _OCTOPUSGAME_H_
#define _OCTOPUSGAME_H_
#include <memory>
#include "Auxiliaries.h"
#include "library2.h"
#include "Avl.h"
#include "AVL_extra_functions.h"
#include "Group.h"
#include "Player.h"
#include "HashTable.h"
#include "UnionFind.h"

int global_scale=0;
int global_k=0;
class OctopusGame
{

    HashTable<Player> PlayersTable;
    UnionFind GroupsUF;
    AVL_Tree<PlayerSeat, PlayerSeat> PlayerByLevelTree;
    Score_structure* all_groups_ss;
    int all_players_zero_level_counter;
    int k;
    int scale;

    // help functions
public:
    int getK(){
        return k;
    }

    int getScale(){
        return scale;
    }

    OctopusGame() = default;

    OctopusGame(int k, int scale);

    ~OctopusGame() = default;

    StatusType MergeGroups(int GroupID1, int GroupdID2);

    StatusType AddPlayer(int PlayerID, int GroupID, int score);

    StatusType RemovePlayer(int PlayerID);

    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);

    StatusType ChangePlayerIDScore(int PlayerID, int NewScore);

    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double *players);

    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * avgLevel);
// bonus
    StatusType GetPlayersBound(int GroupID, int score, int m, int *LoverBoundPlayers, int *HigherBoundPlayers);



};

#endif
