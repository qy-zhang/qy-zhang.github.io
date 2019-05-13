//
// Created by zhangqianyi on 2017/7/10.
//

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int kStraight = 10; //直线走一格距离为10
const int kSlash = 14; //斜线走一格距离为14

struct Point {
    int x, y; //当前点的坐标
    int F, G, H; //A*算法的F、G、H值
    Point* parent; //parent的坐标
    Point(int x1, int y1) : x(x1), y(y1), F(0), G(0), H(0), parent(NULL) {}
};

class AStar {
public:
    AStar(vector<vector<int> > maze) : m_maze(maze) {}
    list<Point*> GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);

private:
    Point* FindPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
    vector<Point*> GetSurroundPoints(Point* point, bool isIgnoreCorner);
    bool IsWalkable(Point* point, Point* target, bool isIgnoreCorner);
    Point* IsInOpenlist(list<Point*>& list, Point* point);
    Point* GetLeastFPoint();

    /*
     *
     */
    int CalcG(Point* tempStart, Point* point);
    int CalcH(Point* point, Point* end);
    int CalcF(Point* point);

    vector<vector<int> > m_maze; //迷宫二维矩阵
    list<Point*> m_openList; //A*算法中的开启列表
    list<Point*> m_closeList; //A*算法中的结束列表
};


#endif //ASTAR_H
