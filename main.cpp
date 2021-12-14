
//




#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include<stack>
#include <vector>

using namespace std;

#define INF 99999

int vertice = 0, edge = 0 ,clusters = 0;



int min(int a, int b) {
    return (a<b)?a:b;
}

class Edge {
public:
    int src, dest, weight;
};

class Graph {
public:

    int V, E;
    Edge* edge;
};

Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[E];

    return graph;
}

class subset {
public:
    int parent;
    int rank;
};


int find(subset subsets[], int i)
{

    if (subsets[i].parent != i)
        subsets[i].parent
                = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);


    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph* graph)
{
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);


    subset* subsets = new subset[(V * sizeof(subset))];


    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }


    while (e < V - 1 && i < graph->E)
    {
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }

    }


    cout << "\nAnswer 2: Cables needs to be installed:\n";
    int minimumCost = 0;
    for (i = 0; i < e; ++i)
    {
        cout << result[i].src << " <---> " << result[i].dest
             << " == " << result[i].weight << endl;
        minimumCost = minimumCost + result[i].weight;
    }

    cout << "Total Cable Installation cost: " << minimumCost
         << endl;
}

int ArrayOfClusters[50][50];
int ArrayNumber=0;

void MakeTheArrayOfClustersNull(){
    for(int a=0;a<50;a++){
            for(int k=0;k<50;k++){
               ArrayOfClusters[a][k]=-1;
            }
    }
}

void findComponent(int u, int disc[], int low[], stack<int>&stk, bool stkItem[], int **graph) {
    static int time = 0;



    disc[u] = low[u] = ++time;
    stk.push(u);
    stkItem[u] = true;
    for(int v = 0; v<vertice; v++) {
        if(graph[u][v]) {
            if(disc[v] == -1) {

                findComponent(v, disc, low, stk, stkItem,graph);

                low[u] = min(low[u], low[v]);
            } else if(stkItem[v])
                low[u] = min(low[u], disc[v]);
        }
    }
    int poppedItem = 0;
    int count=0;
    if(low[u] == disc[u]) {
        while(stk.top() != u) {
            poppedItem = stk.top();
            cout << poppedItem << " ";
           // cout  << "( arraynumber:" << ArrayNumber << "( Count:" << count << " )";
            ArrayOfClusters[ArrayNumber][count] = poppedItem;
            count++;

            stkItem[poppedItem] = false;    //mark as item is popped
            stk.pop();

        }
        poppedItem = stk.top();
        clusters++;

        cout << poppedItem ;
       // cout  << "( arraynumber:" << ArrayNumber << "( Count:" << count << " )";
       // cout << "<-- Cluster: " << clusters << endl;
        ArrayOfClusters[ArrayNumber][count] = poppedItem;
        ArrayNumber++;

        stkItem[poppedItem] = false;
        stk.pop();
    }
}


void strongConComponent(int **graph) {
    MakeTheArrayOfClustersNull();
    int disc[vertice], low[vertice];
    bool stkItem[vertice];
    stack<int> stk;
    for(int i = 0; i<vertice; i++) {    //initialize all elements
        disc[i] = low[i] = -1;
        stkItem[i] = false;
    }
    cout << endl;
    cout << endl;
    cout << "Answer 3 : CLuters of data centers:" << endl;
    for(int i = 0; i<vertice; i++)    //initialize all elements
        if(disc[i] == -1){
            findComponent(i, disc, low, stk, stkItem, graph);
            cout << endl << endl;
            for(int a=0;a<50;a++){
                if(ArrayOfClusters[a][0]>-1){
                    for(int k=0;k<50;k++){
                        if(ArrayOfClusters[a][k]>-1){
                            cout << ArrayOfClusters[a][k];
                        }
                    }
                    cout << endl;
                }

            }

        }
}

void clusterMat(int **adj){
    int clusMat[clusters][clusters];
    for(int i=0;i<clusters;i++){
        for(int j=0;j<clusters;j++){
            clusMat[i][j]=0;
        }
    }
    cout << "Answer 4: Matrix of clusters possible paths" << endl;
    for (int i = 0; i < vertice; i++) {
        for (int j = 0; j < vertice; j++) {
          if (adj[i][j] == 1){
              for (int g = 0; g < clusters; g++) {
                  for (int h = 0; h < vertice; h++) {
                      if(ArrayOfClusters[g][h] == i){
                          bool isInTheSame = false;
                          for(int k=0;k<vertice;k++){
                              if(ArrayOfClusters[g][h]==j){
                                  isInTheSame=true;
                              }
                          }
                          if(!isInTheSame){

                              for(int o=0;o<clusters;o++){
                                  if(o!=g){
                                      for(int u=0;u<vertice;u++){
                                       if(ArrayOfClusters[o][u]==j){
                                           clusMat[g][o]++;
                                       }
                                      }
                                  }

                              }
                          }
                      }
                  }
                  }
          }
        }
    }

    for(int t=0;t<clusters;t++){
        for(int r=0;r<clusters;r++){
            cout << clusMat[t][r];
        }
        cout << endl;
    }
}

int main()
{
  // REading adjecency Matrix from file

    ifstream file;
    
    file.open("C:\\mat3.txt");


    if(!file){
        cerr << "Error reading adjecency matrix file" << endl;
        exit(1);
    }
    cout << "Adjecency Matrix" << endl;

    file >> vertice;

    int** adj=new int*[vertice];
    for(int i =0; i<vertice; i++){
        adj[i] = new int[vertice];
    }

    for (int i = 0; i < vertice; i++) {
        for (int j = 0; j < vertice; j++) {
            file >> adj[i][j];
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    file.close();
    cout << endl;

    // REading Cost Matrix from file

    file.open("C:\\cost3.txt");

    if(!file){
        cerr << "Error reading cost matrix file" << endl;
        exit(1);
    }

    cout << "Cost Matrix" << endl;

    file >> vertice;
    int cost[vertice][vertice];
    for (int i = 0; i < vertice; i++) {
        for (int j = 0; j < vertice; j++) {
            file >> cost[i][j];
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }

    file.close();

    cout << endl;

    // REading cable Installing Cost Matrix from file

    file.open("C:\\instal_cost3.txt");

    if(!file){
        cerr << "Error reading cost matrix file" << endl;
        exit(1);
    }

    cout << "Cable Cost Matrix" << endl;

    file >> vertice;
    int inst_cost[vertice][vertice];
    for (int i = 0; i < vertice; i++) {
        for (int j = 0; j < vertice; j++) {
            file >> inst_cost[i][j];
            cout << inst_cost[i][j] << " ";
        }
        cout << endl;
    }

    file.close();
    cout << endl;

    // Creating cost graph with adjecency matrix and cost matrix files readed

    cout << "Calculated cost Matrix" << endl;

    int cost_mat[vertice][vertice];
    for(int i=0;i<vertice;i++){
        for(int j = 0;j<vertice;j++){
            if(adj[i][j] == 1){
                cost_mat[i][j] = cost[i][j];
                cout << cost_mat[i][j] << " ";
                edge++;

            }
            else{
                cost_mat[i][j] = INF ;
                cout << "INF ";
            }
        }
        cout << endl;
    }
    cout << "Number of edges" << edge << endl;
    cout << endl;

    //
    // Floyed Warshell - 1st question-------------------------------------------------------------------------
    //


    int dist[vertice][vertice], i, j, k;

    for (i = 0; i < vertice; i++)
        for (j = 0; j < vertice; j++)
            dist[i][j] = cost_mat[i][j];

    for (k = 0; k < vertice; k++)
    {
        for (i = 0; i < vertice; i++)
        {
            for (j = 0; j < vertice; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout<<"Answer 1 : This Mtrix shows the routing table from every vertices (Data Centers)\n";
    for (int i = 0; i < vertice; i++)
    {
        cout<< "Rounting Table for Node:" << i << "-->";
        for (int j = 0; j < vertice; j++)
        {
            cout<<"	 ";
            if (dist[i][j] == INF)
                cout<<"INF"<<"	 ";
            else
                cout<<dist[i][j]<<"	 ";
        }
        cout<<endl;
    }
    cout << endl;
    //
    // Kruskals algorithm Question no. 2 -----------------------------------------------------------------------
    //
    Graph* graph = createGraph(vertice, vertice*vertice);

        k =0;
        for(int i=0;i<vertice;i++){
            for(int j = 0;j<vertice;j++){
                if(k < vertice*vertice){
                    // This algorithm works on directed and undirected Graphs, if I chage the src and destination vice-cersa output will be same.
                    graph->edge[k].src = i;
                    graph->edge[k].dest = j;
                    graph->edge[k].weight = inst_cost[i][j];
                    cout <<"Cable no."<< k << " Between " <<i << " and "<< j << " Has weight: " << inst_cost[i][j] << " " << endl;
                    k++;
                }
        }
    }
    KruskalMST(graph);
    cout << endl;
    cout << endl;

    //
    // Trajan Algorithms Question no. 3: ----------------------------------------------------------------------------
    //
    strongConComponent(adj);
    cout << endl;
    cout << endl;
    //
    //  Question no. 4:-----------------------------------------------------------------------------------------------
    //

    clusterMat(adj);

    return 0;
}
