# include "node.h"
using namespace std;

string pathFind( int map[n][m],const int & xStart, const int & yStart, const int & xFinish, const int & yFinish,bool useAstar){
    // initiate priority queues
    priority_queue<node> pq[2];
    int pqi;
    node* n0;
    node* m0;
    int i, j, x, y, xdx, ydy;
    char c;
    pqi=0;
    // initialise open and  closed  list to  0
    for(y=0;y<m;y++){
        for(x=0;x<n;x++){
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }
    // initialise start node as new node,find priority of start node.
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority_astar(xFinish, yFinish);
    //push start node to first priority queue
    pq[pqi].push(*n0);
    //update priority of start node in open list
    open_nodes_map[x][y]=n0->getPriority(); 

    while(!pq[pqi].empty()){
        // create new node and initialise it values from top of priority queue,remove that node from priority queue
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), pq[pqi].top().getg(), pq[pqi].top().getPriority());
        x=n0->getxPos(); y=n0->getyPos();
        pq[pqi].pop(); 
        //update  values in open and closed list
        open_nodes_map[x][y]=0;
        closed_nodes_map[x][y]=1;
        //if goal reached find path using dir_map
        if(x==xFinish && y==yFinish) {
            string path="";
            while(!(x==xStart && y==yStart)){
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }
            delete n0;
        while(!pq[pqi].empty()) pq[pqi].pop();           
        return path;
        }
        //check conditions for creating child nodes
        for(i=0;i<dir;i++){
            xdx=x+dx[i]; ydy=y+dy[i];
            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 || closed_nodes_map[xdx][ydy]==1)){
                //if conditions met then createnew child node
                m0=new node( xdx, ydy, n0->getg(), n0->getPriority());
                m0->nextg(i);
                // use the appropriate algorithm
                if (useAstar){
                m0->updatePriority_astar(xFinish, yFinish);
                }
                else{
                m0->updatePriority_dijkstra(xFinish, yFinish);
                }
                //check if child node is not in open list and  then update
                if(open_nodes_map[xdx][ydy]==0){
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }//check if child  node is in open list, check pasta dn present priority  values and update
                else if(open_nodes_map[xdx][ydy]>m0->getPriority()){
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                    //since this node is already in the priority queuue,it has to be popped and updated priority node should  be  pushed.
                    //this  is  done by using  2 priority queues.
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy)){                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); 
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                        while(!pq[pqi].empty()){                
                            pq[1-pqi].push(pq[pqi].top());
                            pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0);
                }
                else delete m0; 
            }
        }
        delete n0; 
    }
    return ""; 
};

// overloading operator for priority queue
bool operator<(const node & a, const node & b){
  return a.getPriority() > b.getPriority();
};
