//
// Created by zhangqianyi on 2017/7/10.
//

#include <cmath>
#include "AStar.h"

int AStar::CalcF(Point* point) {
    return point->G + point->H;
}

int AStar::CalcG(Point* tempStart, Point* point) {
    int parentG = point->parent == NULL ? 0 : point->parent->G; //����ǳ�ʼ�ڵ㣬���丸�ڵ��ǿգ�GҲ��0
    int extraG = (abs(point->x - tempStart->x) + abs(point->y - tempStart->y)) == 1 ? kStraight : kSlash; //�����ڽӵ�ֱ�߻���б��λ��
    return parentG + extraG;
}

int AStar::CalcH(Point* point, Point* end) {
    //ʹ��ŷ����þ������H
    double distance = sqrt((end->x - point->x) * (end->x - point->x) +
                        (end->y - point->y) * (end->y - point->y))*kSlash;
    return static_cast<int>(distance);
}

Point* AStar::FindPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner) {
    m_openList.push_back(new Point(startPoint.x,startPoint.y)); //�������,��������һ���ڵ㣬�������
    while(!m_openList.empty()) {
        Point* curPoint = GetLeastFPoint(); //�ҵ�Fֵ��С�ĵ�
        m_openList.remove(curPoint); //�ӿ����б���ɾ��
        m_closeList.push_back(curPoint); //�ŵ��ر��б�
        //1,�ҵ���ǰ��Χ�˸����п���ͨ���ĸ���
        vector<Point*> surroundPoints = GetSurroundPoints(curPoint, isIgnoreCorner);
        for(Point* &target:surroundPoints) {
            //2,��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ�丸�ڵ㣬����F G H
            if(!IsInOpenlist(m_openList,target)) {
                target->parent=curPoint;

                target->G = CalcG(curPoint,target);
                target->H = CalcH(target,&endPoint);
                target->F = CalcF(target);

                m_openList.push_back(target);
            } else { //3����ĳһ�����ӣ����ڿ����б��У�����Gֵ, �����ԭ���Ĵ�, ��ʲô������, �����������ĸ��ڵ�Ϊ��ǰ��,������G��F
                int tempG = CalcG(curPoint,target);
                if(tempG<target->G)
                {
                    target->parent=curPoint;

                    target->G = tempG;
                    target->F = CalcF(target);
                }
            }
            Point* resPoint = IsInOpenlist(m_openList,&endPoint);
            if(resPoint) { //�����б���Ľڵ�ָ�룬��Ҫ��ԭ�������endpointָ�룬��Ϊ���������
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
       || IsInOpenlist(m_closeList, target)) { //����㳬����ͼ�����ϰ���뵱ǰ�ڵ��غϡ������ڹر��б��У�����false�����ɴ�
        return false;
    } else {
        if(abs(point->x - target->x) + abs(point->y - target->y) == 1) //��б�ǿ���
            return true;
        else
        {
            //б�Խ�Ҫ�ж��Ƿ��ס
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

    //������ʼ�ͽ�����
    Point start(1,1);
    Point end(6,10);
    //A*�㷨��Ѱ·��
    list<Point*> path = astar.GetPath(start, end, false);
    //��ӡ
    for(auto &p : path)
        cout<<'('<<p->x<<','<<p->y<<')'<<endl;
    
    return 0;
}