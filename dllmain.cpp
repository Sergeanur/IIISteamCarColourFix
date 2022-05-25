#include <windows.h>
#include <iostream>

const BYTE command1[] = { 0xA1, 0xD4, 0x3D, 0x67, 0 }; // mov eax, ds:673DD4h
const BYTE command2[] = { 0xB8, 0, 0, 0, 0 }; // mov eax, 0

const int address = 0x5D911B;

void Patch()
{
	register DWORD dwValue;
	if (!VirtualProtect ((LPVOID)address, 5, PAGE_EXECUTE_READWRITE, &dwValue))
		return;

	if (!memcmp((BYTE*)address, command1, 5))
		memcpy((BYTE*)address, command2, 5);

	VirtualProtect ((LPVOID)address, 5, dwValue, NULL);

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	DisableThreadLibraryCalls( hModule );
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Patch();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

