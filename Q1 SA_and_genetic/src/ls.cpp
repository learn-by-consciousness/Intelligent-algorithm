#include"FileInfo.h"

#define SEARCH_TIME 1000000

double dis[SIZE][SIZE];//距离矩阵
point pos[SIZE];//点坐标




path LS(){
    path ans = init();
    ofstream fout("../result/ls.length");

    for(int i = 0; i < SEARCH_TIME; i++){
        path newAns = getRandPath(ans);
        calLength(&newAns);
        if(newAns.length < ans.length)
            ans = newAns;

        if(i%10==0)
            fout << ans.length << endl;
        
        if(i%(SEARCH_TIME/10)==0){
            saveFile(&ans, "../result/ls");
        }
    }
    fout.close();

    return ans;
}




int main(){
    InitDist();
    
    srand(time(NULL));
    path ans = LS();
    checkAnswer(&ans);

    showPath(&ans);

    showBest();

    return 0;
}