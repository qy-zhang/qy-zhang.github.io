//
// Created by zhangqianyi on 2017/7/10.
//

#include <cmath>
#include "AStar.h"

int AStar::CalcF(Point* point) {
    return point->G + point->H;
}

int AStar::CalcG(Point* tempStart, Point* point) {
    int parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则其父节点是空，G也是0
    int extraG = (abs(point->x - tempStart->x) + abs(point->y - tempStart->y)) == 1 ? kStraight : kSlash; //是在邻接点直线还是斜线位置
    return parentG + extraG;
}

int AStar::CalcH(Point* point, Point* end) {
    //使用欧几里得距离计算H
    double distance = sqrt((end->x - point->x) * (end->x - point->x) +
                        (end->y - point->y) * (end->y - point->y))*kSlash;
    return static_cast<int>(distance);
}

Point* AStar::FindPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner) {
    m_openList.push_back(new Point(startPoint.x,startPoint.y)); //置入起点,拷贝开辟一个节点，内外隔离
    while(!m_openList.empty()) {
        Point* curPoint = GetLeastFPoint(); //找到F值最小的点
        m_openList.remove(curPoint); //从开启列表中删除
        m_closeList.push_back(curPoint); //放到关闭列表
        //1,找到当前周围八个格中可以通过的格子
        vector<Point*> surroundPoints = GetSurroundPoints(curPoint, isIgnoreCorner);
        for(Point* &target:surroundPoints) {
            //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if(!IsInOpenlist(m_openList,target)) {
                target->parent=curPoint;

                target->G = CalcG(curPoint,target);
                target->H = CalcH(target,&endPoint);
                target->F = CalcF(target);

                m_openList.push_back(target);
            } else { //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
                int tempG = CalcG(curPoint,target);
                if(tempG<target->G)
                {
                    target->parent=curPoint;

                    target->G = tempG;
                    target->F = CalcF(target);
                }
            }
            Point* resPoint = IsInOpenlist(m_openList,&endPoint);
            if(resPoint) { //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
                return resPoint;
            }
        }
    }

    return NULL;
}

vector<Point*> AStar::GetSurroundPoints(Point* point, bool isIgnoreCorner) {
    vector<Point*> surroundPoints;
    for(int x=point->x - 1; x <= point->x + 1; ++x) {
        for (int y = point->y - 1; y <= point->y + 1; ++y) {
            if (IsWalkable(point, new Point(x, y), isIgnoreCorner)) {
                surroundPoints.push_back(new Point(x, y));
            }
        }
    }

    return surroundPoints;
}

bool AStar::IsWalkable(Point* point, Point* target, bool isIgnoreCorner) {
    if(target->x < 0 || target->x > m_maze.size()-1 || target->y < 0 || target->y > m_maze[0].size()-1
       || m_maze[target->x][target->y] == 1
       || (target->x == point->x && target->y == point->y)
       || IsInOpenlist(m_closeList, target)) { //如果点超出地图、是障碍物、与当前节点重合、或者在关闭列表中，返回false，不可达
        return false;
    } else {
        if(abs(point->x - target->x) + abs(point->y - target->y) == 1) //非斜角可以
            return true;
        else
        {
            //斜对角要判断是否绊住
            if(m_maze[point->x][target->y] == 0 && m_maze[target->x][point->y]==0)
                return true;
            else
                return isIgnoreCorner;
        }
    }
}


Point* AStar::IsInOpenlist(list<Point*>& list, Point* point) {
    for (Point* tempPoint : list) {
        if (point->x == tempPoint->x && point->y == tempPoint->y) {
            return tempPoint;
        }
    }
    return NULL;
}

Point* AStar::GetLeastFPoint() {
    if (!m_openList.empty()) {
        Point* leastPoint = m_openList.front();
        for (Point* point : m_openList) {
            if (point->F < leastPoint->F) {
                leastPoint = point;
            }
        }
        return leastPoint;
    }
    return NULL;
}

list<Point*> AStar::GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner) {
    Point* result = FindPath(startPoint, endPoint, isIgnoreCorner);
    list<Point*> path;
    while (result != NULL) {
        path.push_front(result);
        result = result->parent;
    }
    return path;
}

int UseAStar() {
	AStar astar(maze);

    //设置起始和结束点
    Point start(1,1);
    Point end(6,10);
    //A*算法找寻路径
    list<Point*> path = astar.GetPath(start, end, false);
    //打印
    for(auto &p : path)
        cout<<'('<<p->x<<','<<p->y<<')'<<endl;
    
    return 0;
}