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
#include "Scores_structure.h"

class OctopusGame
{

    int k;
    int scale;
    HashTable<Player> PlayersTable;
    UnionFind GroupsUF;
    //This part was moved to GroupsUF[0]
    /*
    Score_structure* all_groups_ss;
    */
    /*
    AVL_Tree<PlayerSeat, PlayerSeat> PlayerByLevelTree;
    int all_players_zero_level_counter;
    */

    // help functions
    double calculate_number_of_players_in_bound(int GroupID, int lowerLevel,int higherLevel,int score);
public:

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
