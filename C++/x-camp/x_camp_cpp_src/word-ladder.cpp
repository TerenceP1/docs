#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <climits>
using namespace std;
set<string>names;
queue<string>tsts;
map<string,pair<int,int>>dsts;
int main(){
    string first,last;
    cin >> first >> last;
    int n;
    cin>>n;
    for (int i=0; i<n; i++){
        string tmp;
        cin>>tmp;
        names.insert(tmp);
    }
    queue<string>fq,bq;
    fq.push(first);
    bq.push(last);
    dsts.insert({first,{0,INT_MAX}});
    dsts.insert({last,{INT_MAX,0}});
    while (!(fq.empty()&&bq.empty())){
        //forwards

        string fqt=fq.front();
        fq.pop();
        set<string>cVariations;
        for (int i=0; i<=fqt.length();i++){
            for (int j=0; j<26;j++){
                string nt=fqt;
                nt.insert(i,1,'a'+j);
                if (names.find(nt)!=names.end()){
                    cVariations.insert(nt);
                }
            }
        }
        for (int i=0;i<fqt.length();i++){
            for (int j=0;j<26;j++){if(j!=fqt[i]-'a'){
                string nt=fqt;
                nt[i]='a'+j;
                if (names.find(nt)!=names.end()){
                    cVariations.insert(nt);
                }
            }}
        }
        for (int i=0;i<fqt.length();i++){
            string nt=fqt;
            nt.erase(nt.begin()+i);
            if (names.find(nt)!=names.end()){
                cVariations.insert(nt);
            }
        }
        for (auto it=cVariations.begin();it!=cVariations.end();it++){
            string i=*it;
            if (dsts.find(i)!=dsts.end()){
                if (dsts.find(i)->second.second!=INT_MAX){
                    cout<<dsts.find(i)->second.second+dsts.find(fqt)->second.first+1;
                    return 0;
                }
            }else{
                dsts.insert({i,{dsts.find(i)->second.first+1,INT_MAX}});
                fq.push(i);
            }
        }
        //backwards


        string bqt=bq.front();
        bq.pop();
        cVariations.clear();
        for (int i=0; i<=bqt.length();i++){
            for (int j=0; j<26;j++){
                string nt=bqt;
                nt.insert(i,1,'a'+j);
                if (names.find(nt)!=names.end()){
                    cVariations.insert(nt);
                }
            }
        }
        for (int i=0;i<bqt.length();i++){
            for (int j=0;j<26;j++){if(j!=bqt[i]-'a'){
                string nt=bqt;
                nt[i]='a'+j;
                if (names.find(nt)!=names.end()){
                    cVariations.insert(nt);
                }
            }}
        }
        for (int i=0;i<bqt.length();i++){
            string nt=bqt;
            nt.erase(nt.begin()+i);
            if (names.find(nt)!=names.end()){
                cVariations.insert(nt);
            }
        }
        for (auto it=cVariations.begin();it!=cVariations.end();it++){
            string i=*it;
            if (dsts.find(i)!=dsts.end()){
                if (dsts.find(i)->second.first!=INT_MAX){
                    cout<<dsts.find(i)->second.first+dsts.find(bqt)->second.second+1;
                    return 0;
                }
            }else{
                dsts.insert({i,{INT_MAX,dsts.find(i)->second.second+1}});
                bq.push(i);
            }
        }
    }
    cout<<-1;
}