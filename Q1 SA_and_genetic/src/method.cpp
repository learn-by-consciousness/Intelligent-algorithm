#include "FileInfo.h"

extern double dis[SIZE][SIZE]; //距离矩阵
extern point pos[SIZE];        //点坐标

/*
##############################################################################
## 函数：getDist
## 函数描述：计算两个城市之间的距离
## 参数描述：
## A：城市 A
## B：城市 B
##############################################################################
*/
double getDist(point A, point B)
{
    double xx = A.x - B.x, yy = A.y - B.y;
    return sqrt(xx * xx + yy * yy);
}
/*
##############################################################################
## 函数：InitDist
## 函数描述：数据的读取与距离矩阵的生成
## 参数描述：
## FILENAME：数据存储文件
## dis：距离矩阵
##############################################################################
*/
void InitDist(){
    ifstream fin(FILENAME);
    string s;
    for(int i = 0; i < PASSNUM; i++)
        getline(fin, s);

    int x;
    for(int i = 0; i < SIZE; i++)
        fin >> x >> pos[i].x >> pos[i].y;
    fin.close();
    
    for(int i = 0; i < SIZE; i ++){
        for(int j = i+1; j < SIZE; j++){
            dis[i][j] = dis[j][i] = getDist(pos[i], pos[j]);
        }
    }
}

/*
##############################################################################
## 函数：calLength
## 函数描述：得到回路的长度
## 参数描述：
## *p：回路
##############################################################################
*/
void calLength(path *p)
{
    int *a = p->point;

    double ans = dis[a[0]][a[SIZE - 1]];
    for (int i = 1; i < SIZE; i++)
        ans += dis[a[i]][a[i - 1]];
    p->length = ans;
}



/*
##############################################################################
## 函数：checkAnswer
## 函数描述：检测回路是否完整且无重复
## 参数描述：
## *p：回路
##############################################################################
*/
void checkAnswer(path *p)
{
    int check[SIZE] = {0};
    for (int i = 0; i < SIZE; i++)
        check[p->point[i]] = 1;
    for (int i = 0; i < SIZE; i++)
        if (!check[i])
        {
            cout << "error at " << i << endl;
            return;
        }
}


/*
##############################################################################
## 函数：showBest
## 函数描述：最佳回路及其长度
## 参数描述：
## BEST_FILENAME：数据存储文件
## dis：距离矩阵
##############################################################################
*/
void showBest()
{
    ifstream fin(BEST_FILENAME);
    string s;
    for (int i = 0; i < ANS_PASSNUM; i++)
        getline(fin, s);
    path ans;
    for (int i = 0; i < SIZE; i++)
    {
        fin >> ans.point[i];
        ans.point[i]--;
    }
    fin.close();

    checkAnswer(&ans);
    calLength(&ans);
    showPath(&ans);
}

/*
##############################################################################
## 函数：reverse
## 函数描述：将一段数组倒序排列
## 参数描述：
## *a：一段数组数据
## length：数组长度
##############################################################################
*/
void reverse(int *a, int length)
{
    for (int i = length / 2; i < length; i++)
    {
        int tmp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = tmp;
    }
}

/*
##############################################################################
## 函数：forwordInsert
## 函数描述：将数组头数据放到最后
## 参数描述：
## *a：一段数组数据
## length：数组长度
##############################################################################
*/
void forwordInsert(int *a, int length)
{
    int tmp = a[0];
    for (int i = 1; i < length; i++)
        a[i - 1] = a[i];
    a[length - 1] = tmp;
}



/*
##############################################################################
## 函数：getRandPath
## 函数描述：得到原回路的邻域回路
## 参数描述：
## p：原回路
## method: 0-2的随机值
##############################################################################
*/
path getRandPath(path p)
{
    int method = rand() % 3;
    switch (method)
    {
    case 0:
    {
        int x1 = rand() % SIZE, x2 = rand() % SIZE;
        while (x1 == x2)
            x2 = rand() % SIZE;
        int tmp = p.point[x1];
        p.point[x1] = p.point[x2];
        p.point[x2] = tmp;
        break;
    }
    case 1:
    {
        int x1 = rand() % SIZE, x2 = rand() % SIZE;
        while (x1 == x2)
            x2 = rand() % SIZE;
        if (x1 > x2)
        {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        reverse(p.point + x1, x2 - x1 + 1);
        break;
    }
    default:
    {
        int x1 = rand() % SIZE, x2 = rand() % SIZE;
        while (x1 == x2)
            x2 = rand() % SIZE;
        if (x1 > x2)
        {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        forwordInsert(p.point + x1, x2 - x1 + 1);
        break;
    }
    }
    return p;
}


/*
##############################################################################
## 函数：init
## 函数描述：回路的初始选择
## 参数描述：
## *p：回路
##############################################################################
*/
path init()
{
    path random;
    for (int i = 0; i < SIZE; i++)
        random.point[i] = i;

    // for(int i = 0; i < SIZE; i++)
    //     cout << random.point[i] << ' ';
    // cout << endl;

    for (int i = 0; i < INIT_RAND_TIME; i++)
    {
        random = getRandPath(random);
    }

    calLength(&random);

    return random;
}


void saveFile(path *p)
{
    static int count = 0;
    ofstream fout(OUTFILE);
    for (int i = 0; i < SIZE; i++)
    {
        int j = p->point[i];
        fout << pos[j].x << ' ' << pos[j].y << endl;
    }
}


void showPath(path *p){
    cout << p->point[0];
    for (int i = 1; i < SIZE; i++)
        cout << "->" << p->point[i];
    cout << endl;

    cout << "length:" << p->length << endl;
}