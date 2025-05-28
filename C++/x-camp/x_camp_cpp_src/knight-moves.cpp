#include <iostream>
#include <queue>
#include <map>
using namespace std;
int n,x1,y1,x2,y2;
map<pair<int,int>,int> itms;
int mvs[8][2]={
    {1,2},
    {1,-2},
    {2,1},
    {2,-1},
    {-1,2},
    {-1,-2},
    {-2,1},
    {-2,-1}
};
bool isValid(int x,int y){
    return (x>-1)&&(x<n)&&(y>-1)&&(y<n);
}
int main(){
    cin>>n>>x1>>y1>>x2>>y2;
    queue<pair<pair<int,int>,int>> q;
    q.push({{x1,y1},0});
    while (!q.empty()){
        pair<pair<int,int>,int> ths=q.front();
        q.pop();
        itms.insert(ths);
        if (ths.first.first==x2&&ths.first.second==y2){
            cout<<ths.second;
            return 0;
        }
        for (int i=0;i<8;i++){
            pair<int,int> tmp=ths.first;
            tmp.first+=mvs[i][0];
            tmp.second+=mvs[i][1];
            if (isValid(tmp.first,tmp.second)){
                if (itms.find(tmp)==itms.end()){
                    q.push({tmp,ths.second+1});
                    itms.insert({tmp,ths.second+1});
                }
            }
        }
    }
}