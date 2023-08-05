/*
	Late for everything, my face to the cement
	That's how I always seen it
	I spent days faded and anemic
	You could see it in my face, I ain't been eatin'
	I'm just wastin' away
*/

#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <Psapi.h>

void ConsoleBypass(const char* Title) { //credit to whoever lmao
	DWORD aaaa;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &aaaa);
	*(BYTE*)(&FreeConsole) = 0xC3;
	AllocConsole();
	SetConsoleTitleA(Title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}

MODULEINFO GetModuleInfo(const char* ModuleName) {
	MODULEINFO ModuleInfo = { 0 };
	HMODULE HandleModule = GetModuleHandleA(ModuleName);
	
	if (HandleModule != NULL) {
		GetModuleInformation(GetCurrentProcess(), HandleModule, &ModuleInfo, sizeof(MODULEINFO));
	}
	return ModuleInfo;
}

uintptr_t FindPattern(char* Module, char* Pattern, char* Mask)
{
	MODULEINFO ModuleInfo = GetModuleInfo(Module);

	uintptr_t Base = (uintptr_t)ModuleInfo.lpBaseOfDll;
	uintptr_t Size = (uintptr_t)ModuleInfo.SizeOfImage;

	uintptr_t PatternLength = (uintptr_t)strlen(Mask);

	for (uintptr_t i = 0; i < Size - PatternLength; i++)
	{
		bool Found = true;

		for (uintptr_t j = 0; j < PatternLength; j++)
		{
			Found &= Mask[j] == '?' || Pattern[j] == *(char*)(Base + i + j);
		}

		if (Found)
			return Base + i;
	}

	return 0x0;
}
