#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

vector<string> PrintPath(string maxx, map<int, map<string, string>> Path, vector<string> &PathVector);
vector<string> ViterbiAlgorithm(vector<string> Observations, vector<string> States, map<string,double> Pi, map<string,map<string,double>> Trans, map<string,map<string,double>>  Emission);