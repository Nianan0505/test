#ifndef ASTAR_H
#define ASTAR_H
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef struct Node //声明node结构
{
    int x,y; //节点的坐标
    int g,h,f; //三个函数 f=g+h；
    Node *father; //父节点指针
    Node(int x,int y)
    {
        this->x=x;
        this->y=y;
        this->g=0;
        this->h=0;
        this->f=0;
        this->father=NULL;
    }
    Node(int x, int y,Node *father) //override
    {
        this->x=x;
        this->y=y;
        this->g=0;
        this->h=0;
        this->f=0;
        this->father=father;
    }
}Node;
class Astar  //声明astar类
{
public:
    Astar();
    ~Astar();
    void search(Node *startPoint, Node *endPoint); //起始点和终点
    void checkPoint(int x,int y, Node *father,int g);
    void NextStep(Node *currentPoint);
    int isContains(vector<Node*>* Nodelist ,int x,int y);
    void countGHF(Node* sNode,Node* eNode,int g); //计算ghf值 f=g+h
    static bool compare(Node* n1,Node* n2);
    bool unvisit(int x,int y); //节点是否可访问，代表是否为障碍，true为不可访问
    void printPath(Node *current);
    void printMap();
    vector <Node*> openlist; //定义将要被检查的点集合
    vector <Node*> closelist;  //定义已经被检查的点集合
    Node *startPoint; //起点
    Node *endPoint;  //终点
    static const int Weight=10; //定义上下左右四个方向距离
    static const int Weight_dia=14; //定义对角线距离10*1.414
    static const int row=6;
    static const int col=8;
};

#endif // ASTAR_H
