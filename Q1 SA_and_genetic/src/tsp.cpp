#include "FileInfo.h"


double dis[SIZE][SIZE]; //距离矩阵
point pos[SIZE];        //点坐标


/*
##############################################################################
## 函数：SA
## 函数描述：模拟退火算法
## 参数描述：
## dis：设备上的距离矩阵
## pos：设备上的城市坐标
## t：当前温度
## curtAns：当前回路
## best：目前最佳回路
##############################################################################
*/

path SA()
{
    path curtAns = init();
    path best = curtAns;

    double t = T0;
    double alpha = ALPHA_INIT;

    while (t > TN)
    {
        for (int i = 0; i < M; i++)
        {
            path newAns = getRandPath(curtAns);
            calLength(&newAns);

            if (newAns.length < curtAns.length)
            {
                curtAns = newAns;
                if (curtAns.length < best.length)
                    best = curtAns;
            }
            else
            {
                double num = rand() * 1.0 / RAND_MAX;
                double acceptProbability = exp(-(newAns.length - curtAns.length) / t);

                if (num < acceptProbability)
                {
                    curtAns = newAns;
                }
            }
        }

        t *= alpha;
    }

    return best;
}

void saveFile(path *p)
{
    ofstream fout(OUTFILE);
    for (int i = 0; i < SIZE; i++)
    {
        int j = p->point[i];
        fout << pos[j].x << ' ' << pos[j].y << endl;
    }
}

int main()
{
    srand(time(NULL));
    clock_t start, end;
    start = clock();
    path ans = SA();
    end = clock();

    cout << "Serial Runtime:" << (end - start) / 1000000.0 << endl;

    checkAnswer(&ans);
    cout << ans.point[0];
    for (int i = 1; i < SIZE; i++)
        cout << "->" << ans.point[i];
    cout << endl;
    saveFile(&ans);
    cout << "length:" << ans.length << endl;

    showBest();

    return 0;
}