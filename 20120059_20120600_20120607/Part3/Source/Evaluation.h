#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "SupportFunctions.h"
#include<iomanip>
using namespace std;
struct PredictionVariables
{
    int true_pos = 0;
    int false_pos = 0;
    int false_neg = 0;
};
struct PredictionV
{
    double precision;
    double recall;
    double f1_score;
};

void Evaluate(vector<string> TaggedData, vector<string> PredictionData,map<string,PredictionVariables> &States);
bool IsAvailable(string str);
void PrintMap1(map<string,PredictionVariables> m);
void PrintMap2(map<string,PredictionVariables> m);