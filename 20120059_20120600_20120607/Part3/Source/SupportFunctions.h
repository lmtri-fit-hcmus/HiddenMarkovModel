#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<cstring>
#include<iostream>
#include<sstream>
using namespace std;

map<string,double> GetInitializeMatrix(string filePath);
map<string,map<string, double>> GetMatrix(string filePath);
vector<string> TokenizingSentence(string sentence);
void Parse(vector<string> &listToken);
bool CheckObservationAvailable(vector<string> Obs, map<string,map<string,double>> Emis);