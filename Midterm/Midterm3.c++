#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm> // For nth_element and sort
#include <limits>
#include <cmath>
#include <string>

using namespace std;

struct Area
{
    char ID[50];
    int Latitude;
    int Longitude;
    int HasGold; // 0 for No, 1 for Yes

    bool operator<(const Area &other) const
    {
        return strcmp(ID, other.ID) < 0;
    }
};

struct Node
{
    Area area;
    Node *left;
    Node *right;

    Node(const Area &a) : area(a), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    Node *root;
    int dimensions;

    Node *buildTree(const vector<Area> &areas, int depth)
    {
        if (areas.empty())
            return nullptr;

        int axis = depth % dimensions;
        int medianIdx = areas.size() / 2;

        vector<Area> mutableAreas(areas); // Make a copy since we'll be modifying it
        nth_element(mutableAreas.begin(), mutableAreas.begin() + medianIdx, mutableAreas.end(),
                    [axis](const Area &a, const Area &b)
                    {
                        return (axis == 0) ? a.Latitude < b.Latitude : a.Longitude < b.Longitude;
                    });

        Node *node = new Node(mutableAreas[medianIdx]);
        node->left = buildTree(vector<Area>(mutableAreas.begin(), mutableAreas.begin() + medianIdx), depth + 1);
        node->right = buildTree(vector<Area>(mutableAreas.begin() + medianIdx + 1, mutableAreas.end()), depth + 1);

        return node;
    }

    void nearestNeighborUtil(Node *node, const Area &target, int depth, size_t k, vector<pair<double, Area>> &result)
    {
        if (!node)
            return;

        int axis = depth % dimensions;

        if ((axis == 0 && target.Latitude < node->area.Latitude) || (axis == 1 && target.Longitude < node->area.Longitude))
        {
            nearestNeighborUtil(node->left, target, depth + 1, k, result);
        }
        else
        {
            nearestNeighborUtil(node->right, target, depth + 1, k, result);
        }

        double dist = euclideanDistance(node->area, target);

        if (result.size() < k)
        {
            result.push_back({dist, node->area});
            sort(result.begin(), result.end()); // Sort using the operator< of Area
        }
        else
        {
            if (dist < result.back().first)
            {
                result.pop_back(); // Remove the element with the largest distance
                result.push_back({dist, node->area});
                sort(result.begin(), result.end()); // Sort using the operator< of Area
            }
        }

        double largestDist = (result.size() < k) ? numeric_limits<double>::max() : result.back().first;

        if ((axis == 0 && abs(target.Latitude - node->area.Latitude) < largestDist) ||
            (axis == 1 && abs(target.Longitude - node->area.Longitude) < largestDist))
        {
            if ((axis == 0 && target.Latitude < node->area.Latitude) || (axis == 1 && target.Longitude < node->area.Longitude))
            {
                nearestNeighborUtil(node->right, target, depth + 1, k, result);
            }
            else
            {
                nearestNeighborUtil(node->left, target, depth + 1, k, result);
            }
        }
    }

    double euclideanDistance(const Area &a, const Area &b)
    {
        return sqrt(pow(a.Latitude - b.Latitude, 2) + pow(a.Longitude - b.Longitude, 2));
    }

public:
    BinaryTree(vector<Area> &areas, int dims) : root(nullptr), dimensions(dims)
    {
        root = buildTree(areas, 0);
    }

    vector<pair<double, Area>> nearestNeighbors(const Area &target, int k)
    {
        vector<pair<double, Area>> result;
        nearestNeighborUtil(root, target, 0, k, result);
        return result;
    }
};

string findMostFrequentType(const int values[], int size)
{
    int mostFrequentValue = 0;
    int maxCount = 0;

    for (int i = 0; i < size; ++i)
    {
        int value = values[i];
        int count = 1;
        for (int j = i + 1; j < size; ++j)
        {
            if (values[j] == value)
                ++count;
        }
        if (count > maxCount)
        {
            maxCount = count;
            mostFrequentValue = value;
        }
    }

    return (mostFrequentValue == 1) ? "Yes" : "No";
}

int main()
{
    string HGold[2] = {"No", "Yes"};
    vector<Area> areas = {
        Area{"1", 54, 97, 1},
        Area{"2", 99, 91, 0},
        Area{"3", 61, 53, 1},
        Area{"4", 43, 95, 0},
        Area{"5", 60, 10, 1},
        Area{"6", 40, 74, 0},
        Area{"7", 16, 92, 1},
        Area{"8", 8, 8, 0},
        Area{"9", 90, 37, 1},
        Area{"10", 13, 32, 0},
        Area{"11", 85, 75, 1},
        Area{"12", 98, 23, 0},
        Area{"13", 94, 74, 1},
        Area{"14", 54, 38, 0},
        Area{"15", 36, 42, 1}};

    BinaryTree binaryTree(areas, 2);

    Area target = {"Target", 52, 25, -1};
    int k = 3, count = 0;

    int hasGold[k];

    vector<pair<double, Area>> nearest = binaryTree.nearestNeighbors(target, k);

    cout << "Nearest neighbors to target:";
    for (auto &neighbor : nearest)
    {
        hasGold[count] = neighbor.second.HasGold;
        cout << "\nArea ID: " << neighbor.second.ID << " ";
        cout << " hasgold : " << HGold[neighbor.second.HasGold] << "   ";
        cout << "Distance: " << neighbor.first;
        count++;
    }

    string mostFrequentType = findMostFrequentType(hasGold, k);
    cout << "\nThe Hasgold of Latitude = 52 and Longitude = 25 is: " << mostFrequentType << endl;

    return 0;
}
