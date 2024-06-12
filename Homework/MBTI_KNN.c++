#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

struct Node {
    vector<double> point;
    Node* left;
    Node* right;
    
    Node(const vector<double>& p) : point(p), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;
    int dimensions;
    
    Node* buildTree(const vector<vector<double>>& points, int depth) {
        if (points.empty()) return nullptr;
    
        int axis = depth % dimensions;
        int medianIdx = points.size() / 2;
    
        vector<vector<double>> mutablePoints(points); // Make a copy since we'll be modifying it
        nth_element(mutablePoints.begin(), mutablePoints.begin() + medianIdx, mutablePoints.end(),
                [axis](const vector<double>& a, const vector<double>& b) {
                    return a[axis] < b[axis];
                });
    
        Node* node = new Node(mutablePoints[medianIdx]);
        node->left = buildTree(vector<vector<double>>(mutablePoints.begin(), mutablePoints.begin() + medianIdx), depth + 1);
        node->right = buildTree(vector<vector<double>>(mutablePoints.begin() + medianIdx + 1, mutablePoints.end()), depth + 1);
    
        return node;
    }

    void nearestNeighborUtil(Node* node, const vector<double>& target, int depth, int k, vector<pair<double, vector<double>>>& result) {
        if (!node) return;
        
        int axis = depth % dimensions;
        
        if (target[axis] < node->point[axis]) {
            nearestNeighborUtil(node->left, target, depth + 1, k, result);
        } else {
            nearestNeighborUtil(node->right, target, depth + 1, k, result);
        }
        
        double dist = euclideanDistance(node->point, target);
        
        if (result.size() < k) {
            result.push_back({dist, node->point});
            sort(result.begin(), result.end(), greater<pair<double, vector<double>>>());
        } else {
            if (dist < result.front().first) {
                result.erase(result.begin());
                result.push_back({dist, node->point});
                sort(result.begin(), result.end(), greater<pair<double, vector<double>>>());
            }
        }
        
        double largestDist = (result.size() < k) ? numeric_limits<double>::max() : result.front().first;
        
        if (abs(target[axis] - node->point[axis]) < largestDist) {
            if (target[axis] < node->point[axis]) {
                nearestNeighborUtil(node->right, target, depth + 1, k, result);
            } else {
                nearestNeighborUtil(node->left, target, depth + 1, k, result);
            }
        }
    }
    
    double euclideanDistance(const vector<double>& a, const vector<double>& b) {
        double dist = 0.0;
        for (int i = 0; i < dimensions; ++i) {
            dist += pow(a[i] - b[i], 2);
        }
        return sqrt(dist);
    }

public:
    BinaryTree(vector<vector<double>>& points, int dims) : root(nullptr), dimensions(dims) {
        root = buildTree(points, 0);
    }
    
    vector<pair<double, vector<double>>> nearestNeighbors(const vector<double>& target, int k) {
        vector<pair<double, vector<double>>> result;
        nearestNeighborUtil(root, target, 0, k, result);
        return result;
    }
};


// O(k log k -> k^2) หรือก็คือ worst case ของ function นี้ น้อยกว่า O(n)
// ใช้ k เพราะว่า type มีข้อมูลข้างในแค่ 3 ตัว และ size ก็เท่ากับ 3 ด้วยเช่นกัน
string findMostFrequentType(const string types[], int size) {
    unordered_map<string, int> typeCount;
    string mostFrequentType;
    int maxCount = 0;

    for (int i = 0; i < size; ++i) {
        string type = types[i];
        typeCount[type]++;
        if (typeCount[type] > maxCount) {
            maxCount = typeCount[type];
            mostFrequentType = type;
        }
    }

    return mostFrequentType;
}

int main() {
    // Example usage
    string Name[34] = {
        "Warin Wattanapornprom", "chanatip kwaechaoon", "Yodsaphat Kumwong", "Siwat Chotchong", "Janthima Janhom", "Nitipoom Phramsrichai", "Surasan Phothichak", "Tanyatorn Kongtonglang", "Sorawich Hongsopa", "Athitan Mahamon", "Nutgritta Prasomthongsuk", "Natthawat noiauthai", "Sittan Kunanit", "Jiratchaya Suwancheewasiri", "Teerapan Lueangkittikong", "Anukool Baiban", "Natthinan Kerdsri", "Watcharin Tadajetsombat", "Sukumpat Rujitanatroj", "Panwad Kabucha", "nutthawarara Sasrimuang", "Tonyok Buranawanich", "Mongkud Wathanasilapakit", "Natthapol Premkamon", "Amy Suganya Tripp", "Nichanun Boontanom", "Piriyakorn Srisook", "Napadech Kaewnok", "Pongsatorn Waiyaworn", "Watcharaphun Siriarkanay", "Thiraphat Panthong", "Suchakree panchorpom", "Wattanasuk Limchanyavong", "Suchanan Thongchanluk"
    };

    string Sex[34] = {
        "Male", "male", "male", "male", "female", "male", "Male", "female", "Male", "female", "female", "Male", "Female", "Female", "Male", "Male", "Male", "Male", "Male", "Female", "Female", "Female", "Male", "Female", "Male", "Male", "Male", "Male", "Male", "Female", "Male", "Male", "Male"
    };
    string types[46] = {
        "INTP", "INTJ", "ISTJ", "ISTP", "ENFJ", "INTP", "INFJ", "INFJ",
        "ISTP", "INTP", "ISTJ", "ISTP", "INFJ", "ENTP", "INTJ", "ENFJ",
        "INTP", "ISTJ", "ISTP", "ISTJ", "ISTP", "ESTP", "ISTP", "ENFJ",
        "ISTP", "INTP", "ISTJ", "ISTP", "INTJ", "ISTJ", "ISTP", "INFJ",
        "ISTJ", "ENTP", "ISTP", "INFJ", "ENTP", "ISTJ", "ISTP", "ENTP",
        "ESFJ", "ISTP", "ENTP", "INFJ", "ISTJ", "ENTP"
    };
    string Nick[34] = {
        "Aj.Yong", "Fluk", "Euro", "Nun", "Ploydao", "Phum", "Pui", "Net", "Num", "Dear", "Mymint"
        ,"Nut" , "Mai", "Fern", "Jai", "Guy", "Safe", "Kong", "Palm", "Mute", "Ant", "Namsai","Puay"
        , "khawfang", "Amy", "Gift", "Opal", "Ohm", "Tee", "Bigboss", "Tae", "Tra","Frank", "Mind"
    };
    
    vector<vector<double>> points = {
        {32.0, 32.0, 27.0, 36.0, 29.0, 31.0, 28.0, 23.0,0},
        {31.8, 33.0, 22.0, 30.0, 35.0, 26.0, 24.0, 23.0,1},
        {12.8, 15.6, 14.0, 29.0, 21.0, 20.0, 17.0, 17.0,2},
        {9.8, 14.0, 23.0, 23.0, 27.0, 30.0, 13.0, 25.0 ,3},
        {27.4, 30.4, 25.0, 25.0, 33.0, 28.0, 29.0, 19.0,4},
        {41.4, 31.8, 38.0, 42.0, 25.0, 36.0, 21.0, 39.0,5},
        {29.4, 36.4, 30.0, 34.0, 26.0, 28.0, 35.0, 29.0,6},
        {25.4, 20.4, 33.0, 30.0, 24.0, 32.0, 24.0, 17.0,7},
        {21.4, 20.4, 30.0, 31.0, 34.0, 30.0, 17.0, 22.0,8},
        {41.0, 30.4, 29.0, 45.0, 24.0, 42.0, 33.0, 31.0,9},
        {37.0, 37.4, 37.0, 30.0, 28.0, 40.0, 35.0, 29.0,10},
        {23.4, 27.0, 26.0, 25.0, 27.0, 30.0, 23.0, 20.0,11},
        {35.8, 35.6, 18.0, 23.0, 17.0, 32.0, 26.0, 22.0,12},
        {28.6, 21.0, 23.0, 24.0, 22.0, 26.0, 26.0, 13.0,13},
        {29.4, 39.4, 34.0, 42.0, 32.0, 31.0, 29.0, 29.0,14},
        {39.2, 34.6, 30.0, 23.0, 25.0, 28.0, 36.0, 23.0,15},
        {30.0, 18.4, 19.0, 31.0, 25.0, 31.0, 25.0, 15.0,16},
        {22.8, 27.0, 31.0, 33.0, 29.0, 35.0, 26.0, 22.0,17},
        {21.8, 26.0, 21.0, 34.0, 26.0, 25.0, 23.0, 22.0,18},
        {30.4, 38.0, 20.0, 30.0, 18.0, 29.0, 24.0, 14.0,19},
        {29.4, 28.6, 30.0, 31.0, 31.0, 34.0, 27.0, 25.0,20},
        {18.4, 26.6, 33.0, 38.0, 23.0, 41.0, 20.0, 24.0,21},
        {21.0, 29.4, 23.0, 36.0, 26.0, 32.0, 16.0, 27.0,22},
        {25.4, 26.0, 18.0, 28.0, 25.0, 23.0, 19.0, 23.0,23},
        {20.0, 14.8, 31.0, 37.0, 33.0, 17.0, 24.0, 27.0,24},
        {24.2, 25.6, 21.0, 26.0, 23.0, 28.0, 15.0, 21.0,25},
        {31.6, 29.4, 32.0, 21.0, 28.0, 33.0, 30.0, 21.0,26},
        {24.6, 32.2, 31.0, 39.0, 31.0, 35.0, 21.0, 29.0,27},
        {32.2, 38.8, 32.0, 36.0, 29.0, 35.0, 33.0, 30.0,28},
        {32, 32, 27, 36, 29, 31, 28, 23, 29},
        {22, 36.8, 25, 28, 24, 35, 20, 32, 30},
        {38, 37, 36, 38, 37, 36, 39, 36, 31},
        {36.4, 33.4, 35, 35, 36, 36, 37, 25, 32},
        {19.8, 25, 31, 35, 31, 30, 23, 21, 33},
    };
    
    BinaryTree binaryTree(points, 8);
    
    vector<double> target = {31, 37, 31.5, 37.8, 29, 32, 31, 29.5};
    int k = 3,count = 0;
    
    string nb[k];
    
    vector<pair<double, vector<double>>> nearest = binaryTree.nearestNeighbors(target, k);
    
    cout << "Nearest neighbors to target:";
    for (auto& neighbor : nearest) {
        // cout << endl << neighbor.second[6] << endl;
        nb[count] = types[static_cast<int>(neighbor.second[8])];
        
        cout << endl << "K"<< count+1 << "->";
        cout << "\nName: " << Name[static_cast<int>(neighbor.second[8])] << " ";
        cout << "\nNick Name: " << Nick[static_cast<int>(neighbor.second[8])] << " ";
        cout << "\nType: " << types[static_cast<int>(neighbor.second[8])] << " ";
        cout << "Distance: " << neighbor.first << endl;
        count++;
    }
    
    int size = sizeof(nb) / sizeof(nb[0]);
    string mostFrequentType = findMostFrequentType(nb, size);
    cout << "\n My type is: " << mostFrequentType << endl;
    
    return 0;
}

//สรุปเวลาโดยรวมของโค้ดนี้
// เมื่อต้นไม้มีความลึกที่สมดุลกัน time complexity = O(log n) เพราะใช้ binary tree
// เมื่อต้นไม้ไม่สมดุลกัน time complexity = O(n)

// และฟังก์ชัน โหวต 3 ตัวที่ใกล้ที่สุด มี time complexity = O(klogk) จนไปถึง O(k^2) โดยที่นี้ k มีค่าแค่ 3

