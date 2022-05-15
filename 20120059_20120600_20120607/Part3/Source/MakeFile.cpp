#include "SupportFunctions.h"
#include "viterbiAlgorithm.h"
using namespace std;

int main()
{
   fstream f, test;
   ofstream f2,f3;
   f.open("Test/en_dev_raw.txt");
   test.open("Test/en_dev_tagged.txt");
   f2.open("TaggedData.txt");
   f3.open("PredictionData.txt");
   string line = "", token = "", testLine = "";

   map<string, double> initMatrix = GetInitializeMatrix("Data/Initial.txt");
   map<string, map<string, double>> emiss = GetMatrix("Data/emis_matrix.txt");
   map<string, map<string, double>> trans = GetMatrix("Data/transition_matrix.txt");

   vector<string> Observations, States;
   for (auto i : initMatrix)
      States.push_back(i.first);
   map<string, vector<int>> S;
   int correct = 0;
   int total = 0;
   int n = 0;
   while (getline(f, line))
   {
      Observations = TokenizingSentence(line);
      getline(test, testLine);
      vector<string> TaggedObservations = TokenizingSentence(testLine);
      Parse(TaggedObservations);
      if (!CheckObservationAvailable(Observations, emiss))
         continue;
      vector<string> Prediction = ViterbiAlgorithm(Observations, States, initMatrix, trans, emiss);
      for(int i=0;i<Prediction.size();i++){
         f2 << TaggedObservations[i];
         if(i!=Prediction.size()-1)
            f2 << " ";

         f3 << Prediction[i];
         if(i!=Prediction.size()-1)
            f3 << " ";
      }
      f2<<endl;
      f3<<endl;
   }
   f.close();
}