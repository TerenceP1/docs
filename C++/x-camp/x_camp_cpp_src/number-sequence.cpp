#include <iostream>
#include <vector>
#include <string>
using namespace std;
int n;
int eval(vector<char>tsts){
    vector<int> itms;
    for (int i=1;i<=n;i++){
        itms.push_back(i);
    }
    for (int i=0;i<tsts.size();i++){
        if (tsts[i]=' '){
            itms[i]*=10;
            itms[i]+=itms[i+1];
            itms.erase(itms.begin()+i+1);
            tsts.erase(tsts.begin()+i+1);
            i--;
        }
    }
    for (int i=0;i<tsts.size();i++){
        if (tsts[i]='+'){
            itms[i]+=itms[i+1];
            itms.erase(itms.begin()+i+1);
            tsts.erase(tsts.begin()+i+1);
            i--;
        }
    }
    for (int i=0;i<tsts.size();i++){
        if (tsts[i]='-'){
            itms[i]-=itms[i+1];
            itms.erase(itms.begin()+i+1);
            tsts.erase(tsts.begin()+i+1);
            i--;
        }
    }
    return itms[0];
}
void solve(vector<char>pst,int n){
    if (n!=0){
        vector<char>t1=pst,t2=pst,t3=pst;
        t1.push_back(' ');
        t2.push_back('+');
        t3.push_back('-');
        solve(t1,n-1);
        solve(t2,n-1);
        solve(t3,n-1);
    }else{
        if (eval(pst)==0){
            for (int i=0;i<pst.size();i++){
                cout<<i+1<<pst[i];
            }
            cout<<n<<endl;
        }
    }
}
int main(){
    cin>>n;
    solve({},n);
}