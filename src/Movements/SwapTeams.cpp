#if !defined(Teams)
#define Teams

#include <vector>
#include <math.h>
#include "../Entities/TabuList.cpp"
#include "../Entities/Tournament.cpp"
#include "../Entities/AuxiliarTabuEntities.cpp"

using namespace std;

struct TabuSwapTeams{
  int teamA;
  int teamB;
};

void print(TabuSwapTeams element){
  cout << "Equipo A: " << element.teamA << ", Equipo B: " << element.teamB << endl;
}

/**
 * movement that change the local/visit for two teams
 * input: the two teams to swap
 * output: the new scheduling
*/
vector<vector<int>> SwapTeams(vector<vector<int>> scheduling, unsigned int teamA, unsigned int teamB){
  int postA = teamA - 1;
  int postB = teamB - 1;
  // change the two teams in all the rounds
  for(vector<int> &round : scheduling){
    unsigned int rivalA = abs(round[postA]);
    unsigned int rivalB = abs(round[postB]);
    // change the rival if it is not the other team
    if(rivalA != teamB){
      int originalA = round[postA];
      // change teamA
      round[postA] = copysign(rivalB, round[postB]);
      round[rivalB-1] = copysign(teamA, round[rivalB-1]);
      // change teamB
      round[postB] = copysign(rivalA, originalA);
      round[rivalA-1] = copysign(teamB, round[rivalA-1]);
    }
  }

  return scheduling;
}

bool SwapTeamsCondition(TabuSwapTeams inList, TabuSwapTeams auxiliar){
  bool cond1 = (inList.teamA == auxiliar.teamA && inList.teamB == auxiliar.teamB);
  bool cond2 = (inList.teamA == auxiliar.teamB && inList.teamB == auxiliar.teamA);
  return cond1 || cond2;
}

TabuSwapTeams BestSwapTeams(vector<vector<int>> distances, TSTournament &scheduling, TabuTail<TabuSwapTeams> tabuList, int weight, int DEBUG=0){
  unsigned int totalTeams = scheduling.getSchedule()[0].size();
  unsigned long int auxResult;
  TabuSwapTeams tempValues;
  TabuSwapTeams bestValues;
  vector<vector<int>> bestActual = scheduling.getSchedule();
  vector<vector<int>> tempScheduling;

  for (unsigned int auxTeamA = 1; auxTeamA <= totalTeams; auxTeamA++)
    for (unsigned int auxTeamB = auxTeamA+1; auxTeamB <= totalTeams; auxTeamB++){
      tempValues.teamA = auxTeamA;
      tempValues.teamB = auxTeamB;

      if(!tabuList.InTabuTail(SwapTeamsCondition, tempValues)){
        // get scheduling from movement
        tempScheduling = SwapTeams(bestActual, auxTeamA, auxTeamB);
        auxResult = ObjectiveFunction(distances, tempScheduling, weight);
        // if(DEBUG) cout << "[DEBUG] equipoA: " << auxTeamA << ", equipoB: " << auxTeamB << ", result: " << auxResult << endl;
        // compare
        if(auxResult < scheduling.getDistance()){
          scheduling.setDistance(auxResult);
          scheduling.setSchedule(tempScheduling);
          bestValues = tempValues;
        }
      }
    }

  return bestValues;
}

#endif