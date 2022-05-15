#include "Evaluation.h"

void Evaluate(vector<string> TaggedData, vector<string> PredictionData, map<string, PredictionVariables> &States)
{
    for (int j = 0; j < TaggedData.size(); j = j + 1)
    {
        if (TaggedData[j] == PredictionData[j])
        {
            States[PredictionData[j]].true_pos++;
            ;
        }
        else if (TaggedData[j] != PredictionData[j])
        {
            States[TaggedData[j]].false_pos++;
            States[PredictionData[j]].false_neg++;
        }
    }
}
bool IsAvailable(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            return true;
    }
    return false;
}
void PrintMap1(map<string, PredictionVariables> m)
{
    cout << "     \t"
         << "true_positive\tfalse_positive\tfalse_negative"<<endl;
    for (auto i : m)
    {
        cout << setw(7) <<left<< i.first << setw(20) <<left<< i.second.true_pos << setw(20) <<left<<i.second.false_pos << setw(20) <<left<< i.second.false_neg << endl;
    }
}
void PrintMap2(map<string, PredictionV> m) 
{
    cout << "     \t"
         << "precision\t   recall\t      f1_score"<<endl;
    for (auto i : m)
    {
        cout << setw(7) <<left<< i.first << setw(20) <<left << i.second.precision << setw(20) <<left<< i.second.recall << i.second.f1_score << endl;
    }
}
int main()
{
    fstream pre, tag;
    pre.open("Evaluation Data/PredictionData.txt");
    tag.open("Evaluation Data/TaggedData.txt");

    map<string, PredictionVariables> States;
    string preStr = "", tagStr = "";
    int correctPredictions = 0;
    int allPredictions = 0;
    int unavailable = 0;
    while (getline(pre, preStr) && getline(tag, tagStr))
    {
        if (preStr == tagStr)
            correctPredictions++;
        if (!IsAvailable(preStr))
        {
            unavailable++;
            continue;
        }
        vector<string> TaggedStr = TokenizingSentence(tagStr);
        vector<string> PredStr = TokenizingSentence(preStr);
        Evaluate(TaggedStr, PredStr, States);
        allPredictions++;
    }

    cout << "There are " << unavailable << " sentences that contain token not in Train data." << endl;
    map<string, PredictionV> E;
    for (auto i : States)
    {
        E[i.first].precision = i.second.true_pos * 1.0 / (i.second.true_pos + i.second.false_pos);
        E[i.first].recall = i.second.true_pos * 1.0 / (i.second.true_pos + i.second.false_neg);
        E[i.first].f1_score = 2 * E[i.first].precision * E[i.first].recall / (E[i.first].precision + E[i.first].recall);
    }

    cout << correctPredictions << " " << allPredictions << " " << correctPredictions*1.0/allPredictions<<endl;
    PrintMap1(States);
    PrintMap2(E);
    pre.close();
    tag.close();
}