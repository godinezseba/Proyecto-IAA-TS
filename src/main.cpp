#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "./TabuSearch.cpp"

using namespace std;

int n;
int seed;
int DEBUG;
int iterations;
int lenList;
int weight;

int readInput(int argc, char **argv){ 
    seed = atoi(argv[1]);
    n = atoi(argv[2]);
    DEBUG = atoi(argv[3]);
    iterations = atoi(argv[4]);
    lenList = atoi(argv[5]);
    weight = atoi(argv[6]);

    return 1;
}

int main(int argc, char *argv[]){
    readInput(argc, argv);

    vector<vector<int>> distances(n, vector<int>(n));
    vector<vector<int>> solution;

    // read input matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distances[i][j];
        }
    }

    // define seed
    srand(seed);

    // give matrix to the algorithm
    solution = TabuSearch(distances, iterations, lenList, weight, DEBUG);
    
    // show solution
    // calculateDistance(solution, distances);
    // calculateDistancePenalty(solution, distances);
    // showSolution(solution);
    return 0;
}
