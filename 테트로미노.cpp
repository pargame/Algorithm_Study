// https://www.acmicpc.net/problem/14500

#include <iostream>
#include <vector>

using namespace std;

struct Shape
{
    vector<vector<int>> map;

    Shape(int _shape_num)
    {
        switch (_shape_num)
        {
        case 1:
            map = {{1, 1, 1, 1}};
            break;
        case 2:
            map = {{1, 1}, {1, 1}};
            break;
        case 3:
            map = {{1, 1, 1}, {1, 0, 0}};
            break;
        case 4:
            map = {{1, 1, 0}, {0, 1, 1}};
            break;
        case 5:
            map = {{1, 1, 1}, {0, 1, 0}};
            break;
        default:
            cout << "Wrong Shape!\n";
        }
    }

    vector<vector<int>> GetRotate90Map()
    {
        vector<vector<int>> ret(map[0].size(), vector<int>(map.size()));
        for (size_t i = 0; i < ret.size(); ++i)
        {
            for (size_t j = 0; j < ret[0].size(); ++j)
            {
                ret[i][j] = map[map.size() - j - 1][i];
            }
        }
        return ret;
    }

    vector<vector<int>> GetFlipVrtMap()
    {
        vector<vector<int>> ret(map.size(), vector<int>(map[0].size()));
        for (size_t i = 0; i < ret.size(); ++i)
        {
            for (size_t j = 0; j < ret.size(); ++j)
            {
                ret[i][j] = map[i][map.size() - j - 1];
            }
        }
        return ret;
    }
};

class Tet
{
private:
    Shape shape; // 모양: 1~5
    bool flip;   // 유의미한 좌우 반전 여부
    int rot;     // 유의미한 회전 수

public:
    Tet(int _shape_num) : shape(_shape_num)
    {
        switch (_shape_num)
        {
        case 1:
            flip = false;
            rot = 1;
            break;
        case 2:
            flip = false;
            rot = 0;
            break;
        case 3:
        case 4:
        case 5:
            flip = true;
            rot = 3;
            break;
        default:
            cout << "Worng Shape!!\n";
        }
    }
    int GetMax(vector<vector<int>> const &board)
    {
        }
};

int main()
{
    vector<vector<int>> brd;
}