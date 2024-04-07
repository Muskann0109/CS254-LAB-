#include<bits/stdc++.h>
using namespace std;

struct edge{
    int src,des,wt;
    edge(){};
    edge(int s,int d,int w){
        src=s;des=d;wt=w;
    }
};

bool customCompare(edge e1,edge e2){
    return e1.wt > e2.wt;
}

int find_fun(int x,int parent[]){
    if(parent[x]==x){return x;}
    else return find_fun(parent[x],parent); 
}

void union_fun(int x,int y,int parent[],int rank[]){
    int x_res = find_fun(x,parent);
    int y_res = find_fun(y,parent);
    if(x_res == y_res){return;}
    if(rank[x]<rank[y]){
        parent[x_res]=y_res;
    }else if(rank[x]>rank[y]){
        parent[y_res]=x_res;
    }else{
        parent[y_res]=x_res;
        rank[x]++;
    }
}

int kruskal(edge a[],int n){
    int parent[n],rank[n];
    for(int i=0;i<n;i++){
        parent[i]=i;rank[i]=0;        
    }
    sort(a,a+7,customCompare);
    int ans=0;
    for(int i=0,s=0;s<n-1;i++){
        edge e = a[i];
        int x = find_fun(e.src,parent);
        int y = find_fun(e.des,parent);
        if(x!=y){
            union_fun(x,y,parent,rank);
            s++;
            ans+=e.wt;
        }
    }    
    return ans;
}

int main(){
    int n = 5; // Number of vertices
    int m = 7; // Number of edges
    edge edges[] = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 2, 3},
        {1, 3, 4},
        {2, 3, 5},
        {2, 4, 6},
        {3, 4, 7}
    };

    int result = kruskal(edges, n);
    cout << "Maximum Weight of MST: " << result << endl;
}