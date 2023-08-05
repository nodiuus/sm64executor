/*
	Try to make some sense of all this shit in my brain
	One foot stuck in a tar pit of my ways
*/

#include <iostream>
#include <string>

#include "Addresses.hpp"

void ExecuteScript(std::string& String) {
	Typedefs::ExecuteString((char*)String.c_str());
	Typedefs::ConsoleMessage((char*)String.c_str());
}

void Main() {
	ConsoleBypass("Console");
	
	std::string UserInput;

	std::cout << "excute" << std::endl;

	for (;;) {
		std::cout << ">> ";
		getline(std::cin, UserInput);

		if (UserInput == "MoonJump()") { //added this just in case you want to test it or something
			std::string Script = "function mario_update(m) if (m.action & ACT_FLAG_AIR) ~= 0 then m.vel.y = m.vel.y + 5 end end; hook_event(HOOK_MARIO_UPDATE, mario_update)";
			ExecuteScript(Script);
		}
		else {
			ExecuteScript(UserInput);
		}
	}
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, void* Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(Module);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}