// md4-bust.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <openssl/md4.h>
#include <openssl/evp.h>
#include <openssl/provider.h>
#include <openssl/err.h>

#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

unsigned char target[16];
#define tLen  5
string chars = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM'-!\"#$%&()*,./:;?@[]^_`{|}~+<=>";
int threads = 16;


#define inc(st) for (int i=0;i<tLen;i++){(st)[i]=((st)[i]+1)%(chars.length());if((st)[i]!=0)break;}
#define mInc(st,am) for (int i=0;i<am;i++){inc(st);}


EVP_MD* md;

void thr(int id) {
    int st[tLen] = { 0 };
    mInc(st, id);
    char hash[16];
    int i = 0;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, md, NULL);
    while (true) {
        i++;
        // Make string
        char str[tLen];
        for (int i = 0; i < tLen; i++) {
            str[i] = chars[st[i]];
		}
        //hash
        EVP_DigestUpdate(ctx, str, tLen);
        unsigned int dmp = 16;
        EVP_DigestFinal_ex(ctx, (unsigned char*)hash, &dmp);
        // check hash
        bool res = true;
        for (int i = 0; i < 16; i++) {
            if ((unsigned char)hash[i] != target[i]) {
                res = false;
                break;
			}
        }
        string nstr(str, tLen);
        if (i % 50000 == 0) {
            cout <<i<<' ' << nstr << endl;
            cout << i << "-th hash: ";
            stringstream ss2;
            ss2<< hex<< setw(2)<<setfill('0');
            for (int i = 0; i < 16; i++) {
                ss2 << (int)(unsigned char)hash[i];
			}
            ss2 << dec << endl;
			cout << ss2.str();
        }
        if (nstr == "9999") {
			//cout << "Should be here." << endl;
        }
        if (res) {
            cout << "MD4 BUSTED!!!! " << nstr << endl;
            exit(0);
        }
		mInc(st, threads);
    }
    EVP_MD_CTX_free(ctx);
}


int main()
{
    OSSL_PROVIDER_load(NULL, "default");
    OSSL_PROVIDER_load(NULL, "legacy");
    md = EVP_MD_fetch(NULL, "MD4", NULL);
    cout << "Bust time!" << endl;
    string hexHash = "803b4a40f5184fb711293e4c615d3a0f";
    for (int i = 0; i < 16; i++) {
        unsigned int x;
        std::stringstream ss;
        ss << std::hex << hexHash.substr(i*2,2);
        ss >> x;
		target[i] = (unsigned char)x;
		cout << "Target byte " << i << ": " <<hex<< (int)target[i]<<dec << endl;
    }
	vector<thread> threadsVec;
    for (int i = 0; i < threads; i++) {
        //thread t(thr, i);
        threadsVec.emplace_back(thr,i);
	}
    for (auto& t : threadsVec) {
        t.join();
    }
    cout << "All threads finished. No hash match :(" << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
