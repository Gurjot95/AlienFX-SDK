// AlienFX Sample App.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "../AlienFX_SDK/AlienFX_SDK.h"
#include <iostream>

using namespace std;

int main()
{
	int isInit = AlienFX_SDK::Functions::AlienFXInitialize(AlienFX_SDK::Functions::vid2);
	std::cout << "PID: " << std::hex << isInit << std::endl;
	if (isInit != -1)
	{
		//bool ready = AlienFX_SDK::Functions::IsDeviceReady();
		//std::cout << "Ready: " << ready << std::endl;

		//bool result = AlienFX_SDK::Functions::Reset(false);
		//if (!result) {
		//	std::cout << "Reset faled with " << std::hex << GetLastError() << std::endl;
		//	return 1;
		//}
		cout << "API v" << AlienFX_SDK::Functions::GetVersion() << endl;
		cout << "Now try to set colors...." << endl;

		int ret = AlienFX_SDK::Functions::SetColor(22, 255, 0, 0);
		cout << "Set color result " << ret << endl;
		ret = AlienFX_SDK::Functions::UpdateColors();
		cout << "Update result " << ret << endl;
		cin.get();
		cout << "Ok, how about multi colors?" << endl;
		AlienFX_SDK::Functions::SetColor(23, 255, 0, 0);
		AlienFX_SDK::Functions::SetColor(24, 0, 255, 0);
		AlienFX_SDK::Functions::SetColor(25, 0, 0, 255);
		AlienFX_SDK::Functions::UpdateColors();
		cin.get();
		cout << "That's all for now, exiting." << endl;
		return 0;
		//AlienFX_SDK::Functions::SetAction(2, AlienFX_SDK::Action::AlienFX_Pulse, 7, 0x64, 25, 134, 245);
		//AlienFX_SDK::Functions::SetAction(2, AlienFX_SDK::Action::AlienFX_Color, 0, 0xfa, 255, 255, 255);
		//std::cout << "Initial state: " << std::dec << (int) AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		//AlienFX_SDK::Functions::Reset(false);
		//std::cout << "Reset state: " << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		//AlienFX_SDK::Functions::SetColor(2, 255, 0, 0); //r
		//std::cout << "ColorSet state: " << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		//AlienFX_SDK::Functions::SetAction(3, AlienFX_SDK::Action::AlienFX_A_Pulse, 7, 0x64, 25, 134, 245);
		//std::cout << "ActionSet state: " << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		//AlienFX_SDK::Functions::SetPowerAction(1, 0, 0, 255, 255, 0, 0);
		//std::cout << "PowerAction state: " << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		//AlienFX_SDK::Functions::SetColor(AlienFX_SDK::Index::AlienFX_leftMiddleZone, 0, 0, 255); //b
		//AlienFX_SDK::Functions::SetColor(AlienFX_SDK::Index::AlienFX_rightMiddleZone, 0, 255, 0); // g - right
		AlienFX_SDK::Functions::SetColor(4, 0, 255, 0); // right middle
		//std::cout << "BeforeUpdate state: " << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus() << std::endl;
		AlienFX_SDK::Functions::UpdateColors();
		//std::cout << "Update state:" << std::dec << (int)AlienFX_SDK::Functions::AlienfxGetDeviceStatus();
		/*for (int i = 0; i < 16; i++) { // let's test all lights...
			std::cout << "Set zone " << std::dec << i << std::endl;
			AlienFX_SDK::Functions::SetColor(i, 0, 255, 0);
			AlienFX_SDK::Functions::UpdateColors();
			Sleep(200);
			std::cin.get();
		}*/
		AlienFX_SDK::Functions::AlienFXClose();
	}
	else
		cout << "Can't init device!" << endl;

	//std::cin.get();
	return 0;
}

