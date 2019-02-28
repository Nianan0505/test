#include <QCoreApplication>
#include <iostream>
#include "astar.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Astar astar; //类的实体化
    Node *startPoint=new Node(5,1);//起点
    Node *endPoint=new Node(3,8); //终点
    astar.search(startPoint,endPoint); //寻找路径
    return a.exec();
}
