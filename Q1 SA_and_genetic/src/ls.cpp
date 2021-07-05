#include"FileInfo.h"



double dis[SIZE][SIZE];//距离矩阵
point pos[SIZE];//点坐标

double getDist(point A, point B){
    double xx = A.x-B.x, yy = A.y-B.y;
    return sqrt(xx*xx + yy*yy);
}

void calLength(path * p){
    int *a = p->point;
    
    double ans = dis[a[0]][a[SIZE-1]];
    for(int i = 1; i < SIZE; i++)
        ans += dis[a[i]][a[i-1]];
    p->length = ans;
}

void getDist(){
    ifstream fin("../data/kroC100.tsp");
    string s;
    for(int i = 0; i < 6; i++)
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



void checkAnswer(path *p){
    int check[SIZE] = {0};
    for(int i = 0; i < SIZE; i++)
        check[p->point[i]] = 1;
    for(int i = 0; i < SIZE; i++)
        if(!check[i]){
            cout << "error at " << i << endl;
            return;
        }
}

void showBest(){
    ifstream fin("../data/kroC100.opt.tour");
    string s;
    for(int i = 0; i < 5; i++)
        getline(fin, s);
    path ans;
    for(int i = 0; i < SIZE; i++)
    {
        fin >> ans.point[i];
        ans.point[i]--;
    }
    fin.close();

    checkAnswer(&ans);
    calLength(&ans);
    cout << "最短路径：";
    for(int i = 0; i < SIZE; i++)
        cout << ans.point[i] << ' ';
    cout << endl;
    cout << "最短路径长度：" << ans.length << endl;
}





void reverse(int *a, int length){
    for(int i = length/2; i < length; i++){
        int tmp = a[i];
        a[i] = a[length-i-1];
        a[length-i-1] = tmp;
    }
}

void forwordInsert(int *a, int length){
    int tmp = a[0];
    for(int i = 1; i < length; i++)
        a[i-1] = a[i];
    a[length-1] = tmp;
}

path getRandPath(path p){
    int method = rand()%3;
    switch (method)
    {
    case 0:
    {
        int x1 = rand()%SIZE, x2 = rand()%SIZE;
        while(x1==x2)
            x2 = rand()%SIZE;
        int tmp = p.point[x1];
        p.point[x1] = p.point[x2];
        p.point[x2] = tmp;
        break;
    }
    case 1:{
        int x1 = rand()%SIZE, x2 = rand()%SIZE;
        while(x1==x2)
            x2 = rand()%SIZE;
        if(x1>x2){
            int tmp = x1;
            x1 = x2;
            x2 = tmp;    
        }
        reverse(p.point+x1, x2-x1+1);
        break;
    }
    default:{
        int x1 = rand()%SIZE, x2 = rand()%SIZE;
        while(x1==x2)
            x2 = rand()%SIZE;
        if(x1>x2){
            int tmp = x1;
            x1 = x2;
            x2 = tmp;    
        }
        forwordInsert(p.point+x1, x2-x1+1);
        break;
    }
    }
    return p;
}

path init(){
    path random;
    for(int i = 0; i < SIZE; i++)
        random.point[i] = i;
    
    // for(int i = 0; i < SIZE; i++)
    //     cout << random.point[i] << ' ';
    // cout << endl;

    for(int i = 0; i < INIT_RAND_TIME; i++){
        random = getRandPath(random);
    }


    calLength(&random);

    return random;
}

path LS(){
    path ans = init();

    for(int i = 0; i < M; i++){
        path newAns = getRandPath(ans);
        calLength(&newAns);
        if(newAns.length < ans.length)
            ans = newAns;
    }
    return ans;
}

void saveFile(path *p){
    ofstream fout("../data/out.txt");
    for(int i = 0; i < SIZE; i++){
        int j = p->point[i];
        fout << pos[j].x << ' ' << pos[j].y << endl;
    }
}


int main(){
    getDist();
    
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