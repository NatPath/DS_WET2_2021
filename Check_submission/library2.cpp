#include "library2.h"
#include "OctopusGame.h"

void* Init(int k, int scale){
    if(k <= 0 || scale <= 0 || scale > 200){
        return NULL;
    }
    OctopusGame *DS = new OctopusGame(k, scale);
    return (void*)DS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->MergeGroups(GroupID1, GroupID2); // Needs to take care of StatusType -INVALID_INPUT, ALLOCATION_ERROR and SUCCESS
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
     if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->AddPlayer(PlayerID, GroupID, score); // Needs to take care of StatusType -INVALID_INPUT, ALLOCATION_ERROR, FAILURE and SUCCESS
}

StatusType RemovePlayer(void *DS, int PlayerID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->RemovePlayer(PlayerID); // Needs to take care of StatusType - FAILURE and SUCCESS
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->IncreasePlayerIDLevel(PlayerID, LevelIncrease); // Needs to take care of StatusType - ALLOCATION_ERROR, FAILURE and SUCCESS

}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->ChangePlayerIDScore(PlayerID, NewScore); // Needs to take care of StatusType - INVALID_INPUT, ALLOCATION_ERROR, FAILURE and SUCCESS

}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel, double * players){
   if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->GetPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players); // Needs to take care of StatusType - INVALID_INPUT, ALLOCATION_ERROR, FAILURE and SUCCESS
}
    

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
     if(DS == NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->AverageHighestPlayerLevelByGroup(GroupID, m, level); // Needs to take care of StatusType - INVALID_INPUT, ALLOCATION_ERROR, FAILURE and SUCCESS
}
    


StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,int * LowerBoundPlayers, int * HigherBoundPlayers){
    if (DS==NULL){
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->GetPlayersBound(GroupID, score,m,LowerBoundPlayers,HigherBoundPlayers); // Needs to take care of StatusType - INVALID_INPUT, ALLOCATION_ERROR, FAILURE and SUCCESS
}

void Quit(void** DS){
    delete (OctopusGame*)(*DS);
    *DS=nullptr;
}

