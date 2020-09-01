#pragma once  
#include "stdafx.h"

//#ifdef ALIENFX_EXPORTS  
//#define ALIENFX_API __declspec(dllexport)   
//#else  
//#define ALIENFX_API __declspec(dllimport)   
//#endif  

namespace AlienFX_SDK

{	

	enum Index
	{
		AlienFX_leftZone = 1, // 2 for m15
		AlienFX_leftMiddleZone = 2, // 3 for m15
		AlienFX_rightZone = 3, // 5 for m15
		AlienFX_rightMiddleZone = 4, // same for m15
		AlienFX_Macro = 5,
		AlienFX_AlienFrontLogo = 6, // ?? for m15
		AlienFX_LeftPanelTop = 7,
		AlienFX_LeftPanelBottom = 8,
		AlienFX_RightPanelTop = 9,
		AlienFX_RightPanelBottom = 10,
		AlienFX_TouchPad = 11,
		AlienFX_AlienBackLogo = 12, // 0 for m15
		AlienFX_Power = 13, // 1 for m15
	};


	class Functions
	{
	public:
		//This is VID for all alienware laptops, use this while initializing, it might be different for external AW device like mouse/kb
		const static int vid = 0x187c;
		//returns PID
		static  int AlienFXInitialize(int vid);

		static   bool AlienFXInitialize(int vid, int pid);

		//De-init
		static   bool AlienFXClose();

		//Enable/Disable all lights
		static  bool Reset(bool status);

		static  bool IsDeviceReady();

		static  bool SetColor(int index, int Red, int Green, int Blue);

		static  bool UpdateColors();
	};



}
