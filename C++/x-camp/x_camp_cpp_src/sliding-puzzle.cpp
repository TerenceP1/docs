#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
typedef vector<vector<short>> pzl;
vector<short>tri(3);
map<pzl,pair<int,int>> pss;
int cx[4]={0,1,0,-1};
int cy[4]={1,0,-1,0};
bool isValid(int x,int y){
    return (x>-1)&&(x<3)&&(y>-1)&&(y<3);
}
int main(){
    pzl in(3,tri);
    string tmp;
    cin>>tmp;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            in[i][j]=tmp[i*3+j]-'0';
        }
    }
    queue<pzl> fp,bp;//forward and backwards passes
    pzl tg={
        {1,2,3},
        {8,0,4},
        {7,6,5}
    };
    bp.push(tg);
    pss.insert({tg,{INT_MAX,0}});
    pss.insert({in,{0,INT_MAX}});
    fp.push(in);
    while (!(fp.empty()&&bp.empty())){
        //forwards pass
        pzl fpt=fp.front();
        int x0,y0;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (fpt[i][j]==0){
                    x0=i;
                    y0=j;
                }
            }
        }
        for (int i=0;i<4;i++){
            int tx=x0+cx[i];
            int ty=y0+cy[i];
            if (isValid(tx,ty)){
                pzl fptt=fpt;
                fptt[tx][ty]=0;
                fptt[x0][y0]=fpt[tx][ty];
                if (pss.find(fptt)==pss.end()){
                    pss.insert({fptt,{pss.find(fpt)->second.first+1,INT_MAX}});
                    fp.push(fptt);
                }else{
                    if (pss.find(fptt)->second.second!=INT_MAX){
                        cout<<pss.find(fptt)->second.second+pss.find(fpt)->second.first+1;
                        return 0;
                    }
                }
            }
        }
        fp.pop();
        //backwards pass
        pzl bpt=bp.front();
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (bpt[i][j]==0){
                    x0=i;
                    y0=j;
                }
            }
        }
        for (int i=0;i<4;i++){
            int tx=x0+cx[i];
            int ty=y0+cy[i];
            if (isValid(tx,ty)){
                pzl fptt=bpt;
                fptt[tx][ty]=0;
                fptt[x0][y0]=bpt[tx][ty];
                if (pss.find(fptt)==pss.end()){
                    pss.insert({fptt,{INT_MAX,pss.find(bpt)->second.second+1}});
                    bp.push(fptt);
                }else{
                    if (pss.find(fptt)->second.first!=INT_MAX){
                        cout<<pss.find(fptt)->second.first+pss.find(bpt)->second.second+1;
                        return 0;
                    }
                }
            }
        }
        bp.pop();
    }
    cout<<0;
}