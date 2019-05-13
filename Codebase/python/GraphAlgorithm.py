# -*- coding: utf-8 -*-   
import copy
inf = float('inf')

def dijkstra(graph, n):
    dis = [0] * n
    flag = [False] * n

    flag[0] = True  # 将第一个顶点加入到已搜索表中
    # 初始化第一个顶点到其余顶点的距离
    for i in range(n):
        dis[i] = graph[0][i]

    # 遍历剩余的n-1个顶点
    for i in range(n-1):
        min = inf
        min_index = 0
        for j in range(n):
            if flag[j] == False and dis[j] < min:
                min = dis[j]
                min_index = j
        
        flag[min_index] = True
        for j in range(n):
            if dis[j] > dis[min_index] + graph[min_index][j]:
                dis[j] = dis[min_index] + graph[min_index][j]

    return dis

def floyd(graph, n):
    dis = copy.deepcopy(graph)  # 使用深拷贝，函数参数传递的是对象，由于list对象可修改，所以内部会修改graph，使用深拷贝新建一个变量，防止修改了graph
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if (dis[i][j] > dis[i][k] + dis[k][j]):
                    dis[i][j] = dis[i][k] + dis[k][j]
    return dis

if __name__ == "__main__":
    n = 6
    graph = [
            [0,6,3,inf,inf,inf],
            [6,0,2,5,inf,inf],
            [3,2,0,3,4,inf],
            [inf,5,3,0,2,3],
            [inf,inf,4,2,0,5],
            [inf,inf,inf,3,5,0],
            ]
    dis_dijkstra = dijkstra(graph,n)
    print(dis_dijkstra)

    dis_floyd = floyd(graph, n)
    print(dis_floyd)

    print(graph)