/*
Note : The GetModuleCall() function accepts wide characters , so use the "L" prefix to pass while passing any string
*/

#include <stdio.h>
#include <windows.h>
#include <winternl.h>
#include <string.h>
#include <wchar.h>

wchar_t* extractor(LPCWSTR str1)
{
    static wchar_t dll_str[50];

    int len = wcslen(str1);
    int loop_to = len + 1;
    int loop_from = 0;

    // Find the last occurrence of backslash
    for (int i = len - 1; i >= 0; i--) 
    {
        if (str1[i] == L'\\') 
        {
            loop_from = i + 1;

            break;
        }
    }

    int incre = 0;
    for (int j = loop_from; j < loop_to; j++) 
    {
        dll_str[incre++] = str1[j];
    }
    dll_str[incre] = L'\0';

    return dll_str;
}

HMODULE GetModuleCall(LPCWSTR dllName) {

#ifdef _WIN64
    PPEB PEB_pointer = (PEB*)__readgsqword(0x60);
#elif _WIN32
    PPEB PEB_pointer = (PEB*)__readfsdword(0x30);
#endif

    //Pointer to "PPEB_LDR_DATA" Structure
    PPEB_LDR_DATA Ldr_pointer = PEB_pointer->Ldr;

    //Pointer to Head
    PLIST_ENTRY head = &(Ldr_pointer->InMemoryOrderModuleList);

    //Current Position
    PLIST_ENTRY current_Poisition = head->Flink;

    while (current_Poisition != head)
    {
//Macro to find the structure address
#define CONTAINING_RECORD(address, type, field) ((type *)((LPBYTE)(address) - (ULONG_PTR)(&((type *)0)->field)))

        PLDR_DATA_TABLE_ENTRY module = CONTAINING_RECORD(current_Poisition, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (module->FullDllName.Length != NULL)
        {
            if (_wcsicmp(extractor(module->FullDllName.Buffer), dllName) == 0)
            {
                return (HMODULE) module->DllBase;
            }
        }
        else
        {
            break;
        }
        current_Poisition = current_Poisition->Flink;
    }

    return NULL;
}