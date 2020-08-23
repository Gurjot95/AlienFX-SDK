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
		AlienFX_leftZone = 2, //1,
		AlienFX_leftMiddleZone = 3, //2,
		AlienFX_rightZone = 5, // was 3,
		AlienFX_rightMiddleZone = 4, // was 4,
		AlienFX_Macro = 5,
		AlienFX_AlienFrontLogo = 1, //6,
		AlienFX_LeftPanelTop = 7,
		AlienFX_LeftPanelBottom = 8,
		AlienFX_RightPanelTop = 9,
		AlienFX_RightPanelBottom = 10,
		AlienFX_TouchPad = 11,
		AlienFX_AlienBackLogo = 0,//12,
		AlienFX_Power = 1, //13,
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
