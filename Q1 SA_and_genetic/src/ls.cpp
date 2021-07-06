#include"FileInfo.h"

#define SEARCH_TIME 1000000

double dis[SIZE][SIZE];//距离矩阵
point pos[SIZE];//点坐标




path LS(){
    path ans = init();

    for(int i = 0; i < SEARCH_TIME; i++){
        path newAns = getRandPath(ans);
        calLength(&newAns);
        if(newAns.length < ans.length)
            ans = newAns;
    }
    return ans;
}




int main(){
    InitDist();
    
    srand(time(NULL));
    path ans = LS();
    checkAnswer(&ans);

    cout << "算法产生路径：";
    for(int i = 0; i < SIZE; i++)
        cout << ans.point[i] << ' ';
    cout << endl;
    saveFile(&ans);
    cout << "长度：" << ans.length << endl;

    showBest();

    return 0;
}