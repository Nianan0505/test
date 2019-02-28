#include "astar.h"
#include "cstddef"
using namespace std;
int map[10][10]=  //定义一个地图，已经说明了节点是否为障碍
{
    {0,0,0,1,0,1,0,0,0},
    {0,0,0,1,0,1,0,0,0},
    {0,0,0,0,0,1,0,0,0},
    {0,0,0,1,0,1,0,1,0},
    {0,0,0,1,0,1,0,1,0},
    {0,0,0,1,0,0,0,1,0},
    {0,0,0,1,0,0,0,1,0}
};
Astar::Astar(){}
Astar::~Astar(){}
void Astar::search(Node *startPoint, Node *endPoint)
{
    if(startPoint->x<0||startPoint->x>row||startPoint->y <0||startPoint->y>col||
       endPoint->x<0||endPoint->x>row||endPoint->y <0||endPoint->y>col )//如果横纵坐标超过地图就返回
        return ;
    Node *current;//定义节点结构 当前节点
    this->startPoint=startPoint;
    this->endPoint=endPoint;
    openlist.push_back(startPoint); //把起始点放入open集合中
    while(openlist.size()>0) //当open集合不为0时
    {
        current=openlist[0];
        if(current->x==endPoint->x && current->y==endPoint->y){
            cout<<"find the path"<<endl;//如果当前节点等于终点，则结束
            printMap();
            printPath(current);
            openlist.clear();
            closelist.clear();
            break;
        }
        NextStep(current); //如果当前节点不为终点，则继续
        closelist.push_back(current);
        openlist.erase(openlist.begin());//把当前节点从open集合中拿出放入close集合
        sort(openlist.begin(),openlist.end(),compare); //对openlist里的节点排序，目的为找到g最小的点
    }
}
void Astar::checkPoint(int x, int y, Node *father, int g)//对节点检查
{
    if(x<0||x>row||y<0||y>col) return;//节点超出地图范围，返回
    if(this->unvisit(x,y)) return; //节点不可访问，返回
    if(isContains(&closelist,x,y)!=-1) return; //是否包含在close集合中，包含则返回
    int index;
    if(( index=isContains(&openlist,x,y))!=-1)
    {
        Node *point=openlist[index];//
        if(point->g > father->g+g) //如果节点的g大于父节点的g和两节点间距则
        {
            point->father=father;
            point->g=father->g+g;
            point->f=point->g+point->h;
        }
    }
    else
    {
        Node *point=new Node(x,y,father);
        countGHF(point,endPoint,g);
        openlist.push_back(point);//把point加入open集合中
    }
}
void Astar::NextStep(Node *current) //对当前节点下一步即检查neighbor节点
{
    checkPoint(current->x-1,current->y,current,Weight);//左
    checkPoint(current->x+1,current->y,current,Weight);//右
    checkPoint(current->x,current->y+1,current,Weight);//下
    checkPoint(current->x,current->y-1,current,Weight);//上
    checkPoint(current->x-1,current->y+1,current,Weight_dia);//左上
    checkPoint(current->x-1,current->y-1,current,Weight_dia);//左下
    checkPoint(current->x+1,current->y+1,current,Weight_dia);//右上
    checkPoint(current->x+1,current->y-1,current,Weight_dia);//右下
}
int Astar::isContains(vector<Node*> *Nodelist, int x, int y)//检查节点是否包含在open/close集合中
{
    for(size_t i=0;i<(Nodelist->size());i++)
    {
        if(Nodelist->at(i)->x==x && Nodelist->at(i)->y==y)
            return i;
    }
    return -1;  //包含返回i，不包含返回-1
}
void Astar::countGHF(Node *sNode, Node *eNode, int g)//计算ghf值
{
    int h=(abs(sNode->x - eNode->x)+abs(sNode->y - eNode->y))*Weight;
    int currentg=sNode->father->g+g;
    int f=currentg+h;
    sNode->f=f;
    sNode->h=h;
    sNode->g=currentg;
}
bool Astar::compare(Node *n1, Node *n2)
{
    return n1->f < n2->f; //当节点1的小于节点2的f时返回true
}
bool Astar::unvisit(int x, int y)//节点是否可访问，不可访问为true，可访问为false
{
    if(map[x][y]==1)
        return true;
    return false;
}
void Astar::printPath(Node *current) //输出父节点即路径
{
    if(current->father!=NULL)
    {
        printPath(current->father);
    }
    cout<<"path:  ";
    cout<<"("<<current->x<<","<<current->y<<") "<<endl;
}
void Astar::printMap()//输出地图
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }

}
