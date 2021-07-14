#include "FileInfo.h"

double dis[SIZE][SIZE]; //距离矩阵
point pos[SIZE];        //点坐标


path GA(){
    

    path curtAns = init();
    path best = curtAns;
    return best;
}


int main() {
    srand(time(NULL));
    InitDist();
    path ans = GA();


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