#include "OctopusGame.h"

OctopusGame::OctopusGame(int k , int scale):PlayersTable(2),GroupsUF(k),all_players_zero_level_counter(0),k(k),scale(scale){
    global_scale=scale;
    global_k=k;
    all_groups_ss= new Score_structure[scale+1];
    for (int i=0 ;i<=scale;i++){
        all_groups_ss[i].set_score(i);
    }
}


StatusType OctopusGame::MergeGroups(int GroupID1, int GroupID2){
    if(GroupID1 <= 0 || GroupID2 <= 0 || GroupID1 > getK() || GroupID2 > getK()){
        return INVALID_INPUT;
    }
    try{
        GroupsUF.unionGroupsByID(GroupID1,GroupID2);
    }
    catch(const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
}


StatusType OctopusGame::AddPlayer(int PlayerID, int GroupID, int score){
    if(GroupID <= 0 || GroupID > getK() || PlayerID <= 0 || score <= 0 || score > getScale()){
        return INVALID_INPUT;
    }
    //check if the player is already exist.
    PlayersTable.find()
    //
    Player new_player(PlayerID,GroupID,score);
    Group& found_group = GroupsUF.find(GroupID);
    PlayersTable.insert(new_player);


    
}

StatusType OctopusGame::RemovePlayer(int PlayerID){
    if(PlayerID <= 0){
        return INVALID_INPUT;
    }
    //check if the player is exist.
    


}

StatusType OctopusGame::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease){
    if(PlayerID <= 0 || LevelIncrease <= 0){
        return INVALID_INPUT;
    }


}

StatusType OctopusGame::ChangePlayerIDScore(int PlayerID, int NewScore){
    if(PlayerID <= 0 || NewScore > getScale() || NewScore <= 0){
        return INVALID_INPUT;
    }

}

StatusType OctopusGame::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, double * players){
    if(players == NULL || GroupID < 0 || GroupID > getK()){
        return INVALID_INPUT;
    }
}

    

StatusType OctopusGame::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level){
    if(level == NULL || m <= 0 || GroupID < 0 || GroupID > getK()){
        return INVALID_INPUT;
    }

}
    

