
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdlib.h>

static const int n=40;              //size of map---change here
static const int m=40;              //size of map---change here
static int map[n][m];               //initialising map using 2d array
static int closed_nodes_map[n][m];  //map for storing visited locations.Unvisited locations=0,Visited locations=1
static int open_nodes_map[n][m];    //map for storing priority values of visited locations on map
static int dir_map[n][m];           //map for best direction of parent of each node
static int dir=4;                   //allowed directions to move-4
static int dx[]={1,  0,  -1,  0};   //directions along x
static int dy[]={0,  1,  0,  -1};   //directions along y
// node class for each cell  in map
class node{    
        int xPos;                   //x position of a node 
        int yPos;                   //y position of a node
        int g;                      //distance from start node
        int h;                      //distance to goal
        int priority;               //priority=g+h
                                
    public:
        node(int xp, int yp, int d, int p){xPos=xp; yPos=yp; g=d; priority=p;}              
        int getxPos() const {return xPos;}                                              
        int getyPos() const {return yPos;}
        int getg() const {return g;}
        int getPriority() const {return priority;}
        void updatePriority_astar(const int & xDest, const int & yDest){        //function for astar
             priority=g+estimate(xDest, yDest)*10;
        }
        void updatePriority_dijkstra(const int & xDest, const int & yDest){     //function for dijkstra
             priority=g;
        }
        void nextg(const int & i){
             g+=10;
        }
        int estimate(const int & xDest, const int & yDest) const{
            int xd, yd, h;
            xd=xDest-xPos;
            yd=yDest-yPos;         
            h=sqrt(xd*xd+yd*yd);
            return(h);
        }        
};
// prototype for pathFind function
std::string pathFind(int map[n][m], const int & xStart, const int & yStart, const int & xFinish, const int & yFinish,bool useAstar);