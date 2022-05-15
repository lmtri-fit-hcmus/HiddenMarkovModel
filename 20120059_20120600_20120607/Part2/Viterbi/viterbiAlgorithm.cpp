#include "viterbiAlgorithm.h"

// Hàm in ra đường đi tối ưu nhất với maxIndex là vị trí cuối cùng của State tối ưu
// Vector Path lưu đường đi tối ưu nhất, vector States để truy xuất đường đi từ Path
vector<string> PrintPath(string maxx, map<int, map<string, string>> Path)
{
    vector<string> PathVector;
    PathVector.push_back(maxx);
    for (int i = Path.size() - 1; i > 0; i--)
    {
        maxx = Path[i][maxx];
        PathVector.push_back(maxx);
    }
    // In ra duong di
    reverse(PathVector.begin(), PathVector.end());
    // cout << "Steps: " << endl;
    // for (int i = 0; i < PathVector.size(); i++)
    //     cout << i << ". " << PathVector[i] << endl;
    return PathVector;
}

// Hàm thuật toán Viterbi
/*
    - Observations là vector các quan sát được
    - O là vector là tập các giá trị có thể quan sát được
    - States là tập các trạng thái ẩn
    - Pi là tập xác suất khởi tạo
    - Trans và Emission lần lượt là tập xác suất chuyển tiếp và xác suất "Emission"
*/
vector<string> ViterbiAlgorithm(vector<string> Observations, vector<string> States, map<string, double> Pi, map<string, map<string, double>> Trans, map<string, map<string, double>> Emission)
{
    // V lưu xác suất tối ưu nhất tới Observation thứ i với States j
    map<int, map<string, double>> V;
    // Path lưu đường đi của xác suất tối ưu đó
    // Path[i][j] lưu vị trí tối ưu nhất của States của Observation trước đó (theo tinh thần
    // quy hoạch động)
    map<int, map<string, string>> Path;
    // Khởi tạo V
    for (auto i : Emission[Observations[0]])
    {
        double prob = Pi[i.first] * Emission[Observations[0]][i.first];
        V[0].insert(pair<string, double>(i.first, prob));
        Path[0].insert(pair<string, string>(i.first, " "));
    }
    // Chạy dòng for trên mỗi observation
    for (int i = 1; i < Observations.size(); i++)
    {
        // Chạy các State j tương ứng với Observation i
        for (auto j : Emission[Observations[i]])
        {
            double maxP = 0;
            // Tìm đường đi tối ưu nhất tới State hiện tại từ Observation trước đó (
            // dùng công thức quy hoạch động)
            for (auto k : Emission[Observations[i - 1]])
            {
                // Nếu đường đi có xác suất bằng 0 thì bỏ đường đi đó
                if (Trans[k.first].find(j.first) == Trans[k.first].end())
                    continue;
                double cmpNum = V[i - 1][k.first] * Trans[k.first][j.first] * Emission[Observations[i]][j.first];
                if (cmpNum > maxP)
                {
                    maxP = cmpNum;
                    // Lưu vị trí đường đi tối ưu
                    Path[i][j.first] = k.first;
                }
            }
            V[i][j.first] = maxP;
            if (V[i][j.first] == 0)
                V[i].erase(j.first);
        }
    }
    // Sau khi tìm được ma trận V, ta tìm xác suất có khả nang xảy ra cao nhất
    // MaxIndex là biến đại diện thứ tự của States có khả năng xảy ra cao nhất của Observation cuối cùng
    // Bắt đầu tìm xác suất tối ưu trong V(Chỉ duyệt cột cuối cùng)
    string maxx = "";
    double maxProb = 0;
    for (auto i : Emission[Observations.back()])
    {
        if (V[Observations.size() - 1][i.first] > maxProb)
        {
            maxProb = V[Observations.size() - 1][i.first];
            maxx = i.first;
        }
    }
    // In ra đường đi tương ứng với xác suất đó
    vector<string> res = PrintPath(maxx, Path);
    // cout << endl
    //      << "With highest probability of " << maxProb << endl;
    return res;
}
