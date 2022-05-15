#include"viterbiAlgorithm.h"
#include<fstream>
const string ObservationDataPath = "Observationdata.txt";

vector<string> GetObservations(string filePath, vector<string> &res)
{
    fstream f;
    vector<string> Observations;
    f.open(ObservationDataPath);
    string line ="";
    while(getline(f,line))
    {
        Observations.push_back(line.substr(1,1));
        res.push_back((line[5]=='I') ? "Inbalanced" : "Balanced");
    }
    f.close();
    return Observations;
}

int main()
{
    vector<string> res;
    vector<string> Observations = GetObservations(ObservationDataPath,res);
    vector<string> States{"Balanced", "Inbalanced"};
    map<string,double> Pi;
    Pi["Balanced"] = 0.5;
    Pi["Inbalanced"] = 0.5;
    map<string,map<string,double>> Trans;
    Trans["Balanced"].insert(pair<string,double> ("Balanced",0.8));
    Trans["Balanced"].insert(pair<string,double> ("Inbalanced",0.2));
    Trans["Inbalanced"].insert(pair<string,double> ("Balanced",0.7));
    Trans["Inbalanced"].insert(pair<string,double> ("Inbalanced",0.3));

    map<string,map<string,double>> Emission;
    Emission["1"].insert(pair<string,double>("Balanced",1.0/6));
    Emission["2"].insert(pair<string,double>("Balanced",1.0/6));
    Emission["3"].insert(pair<string,double>("Balanced",1.0/6));
    Emission["4"].insert(pair<string,double>("Balanced",1.0/6));
    Emission["5"].insert(pair<string,double>("Balanced",1.0/6));
    Emission["6"].insert(pair<string,double>("Balanced",1.0/6));

    Emission["1"].insert(pair<string,double>("Inbalanced",0.1));
    Emission["2"].insert(pair<string,double>("Inbalanced",0.1));
    Emission["3"].insert(pair<string,double>("Inbalanced",0.1));
    Emission["4"].insert(pair<string,double>("Inbalanced",0.1));
    Emission["5"].insert(pair<string,double>("Inbalanced",0.1));
    Emission["6"].insert(pair<string,double>("Inbalanced",0.5));
    vector<string> predictionState = ViterbiAlgorithm(Observations, States, Pi, Trans, Emission);

    //Prediction (calc accuracy)
    cout << "Predict       TrueTag"<<endl;
    int positive = 0;
    for(int i = 0 ; i<predictionState.size();i++)
    {
        cout << predictionState[i] << " <=> " << res[i]<<endl;
        if(predictionState[i] == res[i])
        {
            positive++;
        }
    }
    cout << "Accuracy = " << positive << "%";
    // 
}
