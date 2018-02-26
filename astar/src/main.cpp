# include "node.h"
using namespace std;

int main(int argc, char** argv){
    bool useAstar=true;
    if (argc==2){
        string algo=argv[1];
        if (algo=="dijkstra"){
            useAstar=false;
        }
        else if(algo=="astar"){
            useAstar=true;
        }
        else {
            cout<<"Enter astar or dijkstra"<<endl;
            return 0;
        }
    }
    srand(time(NULL));
    
    //Generating empty map
    for(int y=0;y<m;y++){
        for(int x=0;x<n;x++) map[x][y]=0;
    }
    //Generating obstacle in "+" shape
    for(int x=n/8;x<n*7/8;x++){
        map[x][m/2]=1;
    }
    for(int y=m/8;y<m*7/8;y++){
        map[n/2][y]=1;
    }
    // Randomly generating start and end points  
    int xA, yA, xB, yB;
    switch(rand()%8){
        case 0: xA=0;yA=0;xB=n-1;yB=m-1; break;
        case 1: xA=0;yA=m-1;xB=n-1;yB=0; break;
        case 2: xA=n/2-1;yA=m/2-1;xB=n/2+1;yB=m/2+1; break;
        case 3: xA=n/2-1;yA=m/2+1;xB=n/2+1;yB=m/2-1; break;
        case 4: xA=n/2-1;yA=0;xB=n/2+1;yB=m-1; break;
        case 5: xA=n/2+1;yA=m-1;xB=n/2-1;yB=0; break;
        case 6: xA=0;yA=m/2-1;xB=n-1;yB=m/2+1; break;
        case 7: xA=n-1;yA=m/2+1;xB=0;yB=m/2-1; break;
    }
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;
    // starting clock to measure time
    clock_t start = clock();
    // finding path using the appropriate algorithm
    string route=pathFind(map, xA, yA, xB, yB,useAstar);
    if(route=="") cout<<"An empty route generated!"<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
    cout<<"Route:"<<endl;
    cout<<route<<endl<<endl;

    if(route.length()>0){
         // generating route map
        int j; char c; int x=xA; int y=yA;
        map[x][y]=2;
        for(int i=0;i<route.length();i++){
            c =route.at(i);
            j=atoi(&c); 
            x=x+dx[j];
            y=y+dy[j];
            map[x][y]=3;
        }
        map[x][y]=4;
        // displaying route map
        for(int y=0;y<m;y++){
            for(int x=0;x<n;x++)
            if(map[x][y]==0)
                cout<<".";
            else if(map[x][y]==1)
                cout<<"O";
            else if(map[x][y]==2)
                cout<<"S"; 
            else if(map[x][y]==3)
                cout<<"R"; 
            else if(map[x][y]==4)
                 cout<<"F"; 
            cout<<endl;
        }        
    } 
    return(0);
}



