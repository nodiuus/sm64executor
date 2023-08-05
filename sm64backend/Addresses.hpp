/*
	"neon genesis evangelion peak :60:"
	~schwaffles 2023
*/

#include "Functions.hpp"

#define ASLR(x) (x - 0x140000000 + reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL)))

/*
	//#define DJUI_MESSAGE_CREATE ASLR(0x14013E5A0)
	//#define SMLUA_EXEC_STR ASLR(0x140151610)
	//#define DJUI_CONSOLE_MESSAGE ASLR(0x14013F250)

	for reference ^^
*/

namespace Typedefs {
	uintptr_t SMLUA_EXEC_STR		= FindPattern((char*)"sm64.us.f3dex2e.exe", (char*)"\x55\x57\x56\x53\x48\x83\xEC\x38\x48\x8B\x1D\xCC\xCC\xCC\xCC\x48\x89", (char*)"xxxxxxxxxxx????xx");
	uintptr_t DJUI_CONSOLE_MESSAGE  = FindPattern((char*)"sm64.us.f3dex2e.exe", (char*)"\x56\x53\x48\x83\xEC\x48\x48\x89\xCB\x48\x8B", (char*)"xxxxxxxxxxx");

	typedef void(__fastcall* exec_str)(char* String);
	typedef void(__fastcall* console_message)(char* Message);

	exec_str ExecuteString		   = (exec_str)SMLUA_EXEC_STR;
	console_message ConsoleMessage = (console_message)DJUI_CONSOLE_MESSAGE;
}