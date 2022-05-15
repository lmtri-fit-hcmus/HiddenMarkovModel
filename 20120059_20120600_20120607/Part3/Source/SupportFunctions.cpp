#include "SupportFunctions.h"

map<string, double> GetInitializeMatrix(string filePath)
{
    fstream f;
    f.open(filePath);
    string line = "";
    map<string, double> InitMatrix;
    while (getline(f, line))
    {
        string d = "";
        string state;
        double prob;
        for (auto i : line)
            if (i != ' ')
                d += i;
            else
            {
                state = d;
                d = "";
            }
        prob = stod(d);
        InitMatrix.insert(pair<string, double>(state, prob));
    }
    f.close();
    return InitMatrix;
}

map<string, map<string, double>> GetMatrix(string filePath)
{
    map<string, map<string, double>> Trans;
    fstream f;
    f.open(filePath);
    string line = "";
    while (getline(f, line))
    {
        string ele1 = "", ele2 = "", d = "";
        double prob;
        for (auto i : line)
        {
            if (i == '/')
            {
                ele1 = d;
                d = "";
            }
            else if (i == ' ')
            {
                ele2 = d;
                d = "";
            }
            else
                d += i;
        }
        prob = stod(d);
        Trans[ele1].insert(pair<string, double>(ele2, prob));
        if (ele1 == "do")
            int k = 1;
    }
    f.close();
    int k = Trans.size();
    return Trans;
}
vector<string> TokenizingSentence(string sentence)
{
    vector<string> tokens;
    stringstream check1(sentence);
    string intermediate;
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool CheckObservationAvailable(vector<string> Obs, map<string, map<string, double>> Emis)
{
    for (auto i : Obs)
        if (Emis[i].size() == 0)
        {
            cout << "Not found " << i << endl;
            return false;
        }
    return true;
}

void Parse(vector<string> &listToken)
{
    for (int j = 0; j < listToken.size(); j++)
    {
        int i = 0;
        for (; i < listToken[j].length(); i++)
            if (listToken[j][i] == '/')
                break;
        string res = listToken[j].substr(i+1, listToken[j].length() - i);
        listToken[j] = res;
    }
}