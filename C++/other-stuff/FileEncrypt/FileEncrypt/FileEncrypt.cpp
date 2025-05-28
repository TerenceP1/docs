// FileEncrypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
#pragma comment (lib,"Bcrypt.lib")
#include <bcrypt.h>
#include <string>
#include <conio.h>
using namespace std;

void aesCTR(UCHAR iv[16], BCRYPT_ALG_HANDLE aes, BCRYPT_KEY_HANDLE key, int len, char* inpC, char* outC) {
	UCHAR ctr[16];
	memcpy(ctr, iv, 16);
	for (int i = 0; i < len; i += 16) {
		ULONG dump;
		char tRes[16];
		BCryptEncrypt(
			key,
			(PUCHAR)ctr,
			16,
			NULL,
			NULL,
			0,
			(PUCHAR)tRes,
			min(16,len-i),
			&dump,
			NULL
		);
		for (int j = 0; j < 16; j++) {
			if (i + j >= len) { break; }
			outC[i + j] = inpC[i+j]^tRes[j];
		}
		for (int j = 15; j >= 0; j--) {
			if (++ctr[j] != 0) break;
		}
	}
}

void zeroStr(string& str) {
	SecureZeroMemory((void*)str.data(), str.length());
}

void secureGet(string& out) {
	out = "";
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dwMode;
	GetConsoleMode(hConsole, &dwMode);
	SetConsoleMode(hConsole, dwMode & ~ENABLE_ECHO_INPUT);
	string lst;
	char cChar;
	while (true) {
		cChar = _getch();
		lst += cChar;
		if (cChar == 13) {
			break;
		}
		if (cChar == 27) {
			cout << "\n\nTERMINATING\n";
			exit(0);
		}
		if (cChar == 8 || cChar==127) {
			if (out.length() > 0) {
				out.pop_back();
				cout << "\b \b";
			}
		}
		if (cChar <= 31) {
			continue;
		}
		else {
			out += cChar;
			cout << "*";
		}
	}
	cout << endl;
	SetConsoleMode(hConsole, dwMode);
	zeroStr(lst);
	//cout << lst<< endl;
}


int main()
{
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dwMode;
	GetConsoleMode(hConsole, &dwMode);
	SetConsoleMode(hConsole, dwMode | ENABLE_ECHO_INPUT);

	bool mode;
	cout << "Encrypt or decrypt ? (1 for encrypt, 0 for decrypt): ";
	cin >> mode;
	cout << "Password? ";
	string pwd;
	// cin >> pwd;
	secureGet(pwd);
	char* cPwd = const_cast<char*>(pwd.c_str());
	BCRYPT_ALG_HANDLE aes, sha256,mac;
	NTSTATUS status;
	status=BCryptOpenAlgorithmProvider(
		&aes,
		L"AES",
		MS_PRIMITIVE_PROVIDER,
		0
	);
	if (status) {
		cerr << std::hex << "Error: " << status << endl;
		return status;
	}
	BCryptOpenAlgorithmProvider(
		&sha256,
		L"SHA256",
		MS_PRIMITIVE_PROVIDER,
		0
	);
	BCryptOpenAlgorithmProvider(
		&mac,
		L"SHA256",
		MS_PRIMITIVE_PROVIDER,
		BCRYPT_ALG_HANDLE_HMAC_FLAG
	);/*
	BCRYPT_HASH_HANDLE hHash;
	char* hash = new char[256 / 8];
	DWORD bufsz;
	BCryptGetProperty(
		sha256,
		BCRYPT_OBJECT_LENGTH,
		(unsigned char*)(&bufsz),
		sizeof(bufsz),
		NULL,
		0
	);
	char* tmp = new char[bufsz];
	BCryptCreateHash(
		sha256,
		&hHash,
		NULL,
		0,
		0,
		0,
		0
	);
	BCryptHashData(
		hHash,
		(unsigned char*)cPwd,
		pwd.length(),
		0
	);
	BCryptFinishHash(
		hHash,
		(unsigned char*)hash,
		256 / 8,
		0
	);
	cout << "Hash: ";
	for (int i = 0; i < 256 / 8; i++) {
		printf("%02x", (unsigned char)hash[i]);
	}
	cout << endl;*/
	UCHAR iv[16];

	BCryptGenRandom(NULL, iv, sizeof(iv), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
	PUCHAR cMode = (unsigned char*)"ChainingModeCTR";
	/*status = BCryptSetProperty(
		aes,
		BCRYPT_CHAINING_MODE,
		cMode,
		15,
		0
	);
	if (status) {
		cerr << std::hex << "Error: " << status << endl;
		return status;
	}*/
	cout << "File name: ";
	string fnm;
	getline(cin, fnm);
	getline(cin, fnm);
	cout << "Output: ";
	string outfile;
	getline(cin , outfile);
	ifstream inp(fnm, ios::binary);
	ofstream outp(outfile, ios::binary);
	char sanity2[16];
	char orHash[32];
	char salt[32];
	BCryptGenRandom(NULL, (PUCHAR)salt, sizeof(salt), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
	//cout << endl;
	if (!mode) {
		inp.read((char*)iv, 16);
		inp.read(sanity2, 16);
		inp.read(orHash, 32);
		inp.read(salt, 32);
	}
	//cout << "Salt: ";
	for (int i = 0; i < 32; i++) {
		//printf("%02x", (unsigned char)salt[i]);
	}
	char pHash[32];
	BCryptDeriveKeyPBKDF2(
		mac,
		(PUCHAR)cPwd,
		pwd.length(),
		(PUCHAR)salt,
		sizeof(salt),
		100000000,
		(PUCHAR)pHash,
		sizeof(pHash),
		0
	);
	//cout << "PBKDF2: ";
	for (int i = 0; i < 32; i++) {
		//printf("%02x", (unsigned char)pHash[i]);
	}
	//cout << endl;
	char* inpC;
	inp.seekg(0, inp.end);
	int len = mode ? (int)inp.tellg() : (int)inp.tellg() - 96;
	inp.seekg(mode ? 0 : 96, inp.beg);
	inpC = new char[len];
	inp.read(inpC, len);
	//cout << "Size: " << len << endl;
	BCRYPT_KEY_HANDLE key;
	status = BCryptGenerateSymmetricKey(
		aes,
		&key,
		0,
		0,
		(unsigned char*)pHash,
		256 / 8,
		0
	);
	if (status) {
		cerr << std::hex << "Error: " << status << endl;
		BCryptCloseAlgorithmProvider(aes, 0);
		BCryptCloseAlgorithmProvider(sha256, 0);
		BCryptCloseAlgorithmProvider(mac, 0);
		SecureZeroMemory(cPwd, pwd.length());
		zeroStr(pwd);
		SecureZeroMemory(pHash, sizeof(pHash));
		SecureZeroMemory(inpC, sizeof(inpC));
		return status;
	}
	//cout << "IV: ";
	for (int i = 0; i < 16; i++) {
		//printf("%02x", iv[i]);
	}
	//cout << endl;
	//cout << "SANITY CHECK: ";
	char sanity[16];
	ULONG dmp;
	BCryptEncrypt(
		key,
		(PUCHAR)iv,
		16,
		NULL,
		NULL,
		0,
		(PUCHAR)sanity,
		16,
		&dmp,
		NULL
	);
	for (int i = 0; i < 16; i++) {
		//printf("%02x", (UCHAR)(sanity[i]));
	}
	//cout << endl;
	
	if (mode) {
		// encrypt
		char* outC = new char[len];
		ULONG dump;
		/*status = BCryptEncrypt(
			key,
			(PUCHAR)inpC,
			len,
			NULL,
			iv,
			16,
			(PUCHAR)outC,
			len,
			&dump,
			0
		);*/aesCTR(iv, aes, key, len, inpC, outC);
		BCRYPT_HASH_HANDLE hHash2;
		BCryptCreateHash(
			sha256,
			&hHash2,
			NULL,
			0,
			0,
			0,
			0
		);
		BCryptHashData(
			hHash2,
			(unsigned char*)inpC,
			len,
			0
		);
		char* rHash2 = new char[256 / 8];
		BCryptFinishHash(
			hHash2,
			(unsigned char*)rHash2,
			256 / 8,
			0
		);
		outp.write((char*)iv, 16);
		outp.write(sanity, 16);
		outp.write(rHash2, 32);
		outp.write(salt, 32);
		outp.write((char*)outC, len);
		outp.close();
		BCryptCloseAlgorithmProvider(aes, 0);
		BCryptCloseAlgorithmProvider(sha256, 0);
		BCryptCloseAlgorithmProvider(mac, 0);
		SecureZeroMemory(cPwd, pwd.length());
		zeroStr(pwd);
		SecureZeroMemory(pHash, sizeof(pHash));
		SecureZeroMemory(inpC, sizeof(inpC));
		SecureZeroMemory(outC, sizeof(outC));
	}
	else {
		for (int i = 0; i < 16; i++) {
			if (sanity[i] != sanity2[i]) {
				cerr << "Sanity check failed!" << endl;
				cerr << "Password is WRONG!" << endl;
				BCryptCloseAlgorithmProvider(aes, 0);
				BCryptCloseAlgorithmProvider(sha256, 0);
				BCryptCloseAlgorithmProvider(mac, 0);
				SecureZeroMemory(cPwd, pwd.length());
				zeroStr(pwd);
				SecureZeroMemory(pHash, sizeof(pHash));
				SecureZeroMemory(inpC, sizeof(inpC));
				return 1;
			}
		}
		char* outC = new char[len];
		ULONG dump;
		/*status = BCryptEncrypt(
			key,
			(PUCHAR)inpC,
			len,
			NULL,
			iv,
			16,
			(PUCHAR)outC,
			len,
			&dump,
			0
		);*/aesCTR(iv, aes, key, len, inpC, outC);

		BCRYPT_HASH_HANDLE hHash2;
		BCryptCreateHash(
			sha256,
			&hHash2,
			NULL,
			0,
			0,
			0,
			0
		);
		BCryptHashData(
			hHash2,
			(unsigned char*)outC,
			len,
			0
		);
		char* rHash2 = new char[256 / 8];
		BCryptFinishHash(
			hHash2,
			(unsigned char*)rHash2,
			256 / 8,
			0
		);
		for (int i = 0; i < 32; i++) {
			if (rHash2[i] != orHash[i]) {
				cerr << "Hash check failed!" << endl;
				cerr << "Cyphertext or SHA256 has been tampered with" << endl;
				cout << "current hash: ";
				for (int i = 0; i < 32; i++) {
					printf("%02x", (UCHAR)(rHash2[i]));
				}
				cout << endl;
				cout << "expected hash: ";
				for (int i = 0; i < 32; i++) {
					printf("%02x", (UCHAR)(orHash[i]));
				}
				cout << endl;
				return 1;
			}
		}
		outp.write((char*)outC, len);
		outp.close();
		BCryptCloseAlgorithmProvider(aes, 0);
		BCryptCloseAlgorithmProvider(sha256, 0);
		BCryptCloseAlgorithmProvider(mac, 0);
		SecureZeroMemory(cPwd, pwd.length());
		zeroStr(pwd);
		SecureZeroMemory(pHash, sizeof(pHash));
		SecureZeroMemory(inpC, sizeof(inpC));
		SecureZeroMemory(outC, sizeof(outC));
	}
	if (status) {
		cerr << std::hex << "Error: " << status << endl;
		return status;
	}
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
