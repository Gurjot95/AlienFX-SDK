#pragma once
#include <wtypes.h>
#include <vector>
#include <string>
//#include "alienfx-controls.h"

#ifndef NOACPILIGHTS
#include "alienfan-SDK.h"
#endif

using namespace std;

namespace AlienFX_SDK {

	// Statuses for v1-v3
	#define ALIENFX_V2_RESET 0x06
	#define ALIENFX_V2_READY 0x10
	#define ALIENFX_V2_BUSY 0x11
	#define ALIENFX_V2_UNKNOWN 0x12
	// Statuses for apiv4
	#define ALIENFX_V4_READY 33
	#define ALIENFX_V4_BUSY 34
	#define ALIENFX_V4_WAITCOLOR 35
	#define ALIENFX_V4_WAITUPDATE 36
    #define ALIENFX_V4_WASON 38
	// Statuses for apiv5
    #define ALIENFX_V5_STARTCOMMAND 0x8c
    #define ALIENFX_V5_WAITUPDATE 0x80
    #define ALIENFX_V5_INCOMMAND 0xcc

	// Mapping flags:
    #define ALIENFX_FLAG_POWER		1
    #define ALIENFX_FLAG_INDICATOR	2
	#define ALIENFX_FLAG_LOCK		4

	// Maximal buffer size across all device types
    #define MAX_BUFFERSIZE 65

	union Afx_colorcode // Atomic color structure
	{
		struct {
			byte b, g, r;
			byte br; // Brightness
		};
		DWORD ci;
	};

	struct Afx_icommand {
		byte i, val;
	};

	struct Afx_light { // Light information block
		byte lightid;
		union {
			struct {
				WORD flags;
				WORD scancode;
			};
			DWORD data;
		};
		string name;
	};

	union Afx_groupLight {
		struct {
			WORD did, lid;
		};
		DWORD lgh;
	};

	struct Afx_group { // Light group information block
		DWORD gid;
		string name;
		vector<Afx_groupLight> lights;
		bool have_power = false;
	};

	struct Afx_grid {
		byte id;
		byte x, y;
		string name;
		Afx_groupLight *grid;
	};

	struct Afx_action { // atomic light action phase
		BYTE type; // one of Action values - action type
		BYTE time; // How long this phase stay
		BYTE tempo; // How fast it should transform
		BYTE r, g, b; // phase color
	};

	struct Afx_lightblock { // light action block
		byte index;
		vector<Afx_action> act;
	};

	enum Afx_Version {
		API_ACPI = 0, //128
		API_V8 = 8, //65
		API_V7 = 7, //65
		API_V6 = 6, //65
		API_V5 = 5, //64
		API_V4 = 4, //34
		API_V3 = 3, //12
		API_V2 = 2, //9
		API_V1 = 1, //8
		API_UNKNOWN = -1
	};

	enum Action	{
		AlienFX_A_Color = 0,
		AlienFX_A_Pulse = 1,
		AlienFX_A_Morph = 2,
		AlienFX_A_Breathing= 3,
		AlienFX_A_Spectrum = 4,
		AlienFX_A_Rainbow = 5,
		AlienFX_A_Power = 6
	};

	class Functions
	{
	private:

		HANDLE devHandle = NULL;
		OVERLAPPED callBack;

		void* device = NULL;

		bool inSet = false;

		int vid = -1; // Device VID
		int pid = -1; // Device PID, -1 if not initialized
		int length = -1; // HID report length
		byte chain = 1; // seq. number for APIv1-v3
		int version = API_UNKNOWN; // interface version
		byte reportID = 0; // HID ReportID (0 for auto)
		byte bright = 64; // Brightness for APIv4 and v6

		// support function for mask-based devices (v1-v3, v6)
		vector<Afx_icommand>* SetMaskAndColor(DWORD index, byte type, Afx_action c1, Afx_action c2 = { 0 }, byte tempo = 0);

		// Support function to send data to USB device
		bool PrepareAndSend(const byte *command, vector<Afx_icommand> *mods = NULL);
		bool PrepareAndSend(const byte* command, vector<Afx_icommand> mods);

		// Add new light effect block for v8
		byte AddV8DataBlock(byte bPos, vector<Afx_icommand>* mods, byte index, vector<Afx_action>* act);

		// Add new color block for v5
		byte AddV5DataBlock(byte bPos, vector<Afx_icommand>* mods, byte index, Afx_action* act);

		// Support function to send whole power block for v1-v3
		bool SavePowerBlock(byte blID, Afx_lightblock* act, bool needSave, bool needInverse = false);

		// Support function for APIv4 action set
		bool SetV4Action(byte index, vector<Afx_action>* act);

		// return current device state
		BYTE GetDeviceStatus();

		// Next command delay for APIv1-v3
		BYTE WaitForReady();

		// After-reset delay for APIv1-v3
		BYTE WaitForBusy();

	public:

		// current power mode (AC/Battery) for APIv1-v3
		bool powerMode = true;

		~Functions();

		// Initialize device
		// If vid is 0, first device found into the system will be used, otherwise device with this VID.
		// If pid is not zero, device with vid/pid will be used.
		// Returns PID of device used.
		int AlienFXInitialize(int vidd = -1, int pidd = -1);

		// Check device and initialize path and vid/pid
		// in case vid/pid -1 or absent, any vid/pid acceptable
		// Returns PID of device if ok, -1 otherwise
		int AlienFXCheckDevice(string devPath, int vid = -1, int pid = -1);

#ifndef NOACPILIGHTS
		// Initialize Aurora ACPI lights if present.
		// acc is a pointer to active AlienFan control object (see AlienFan_SDK for reference)
		int AlienFXInitialize(AlienFan_SDK::Control* acc);
#endif

		// Prepare to set lights
		bool Reset();

		// false - not ready, true - ready, 0xff - stalled
		BYTE IsDeviceReady();

		// basic color set with ID index for current device.
		// Now it's a synonym of SetAction, but with one color
		bool SetColor(byte index, Afx_action c);

		// Set multiply lights to the same color. This only works for some API devices, and emulated for other ones.
		// lights - pointer to vector of light IDs need to be set.
		// c - color to set
		bool SetMultiColor(vector<byte> *lights, Afx_action c);

		// Set multiply lights to different color.
		// act - pointer to vector of light control blocks
		// store - need to save settings into device memory (v1-v4)
		bool SetMultiAction(vector<Afx_lightblock> *act, bool store = false);

		// Set color to action
		// act - pointer to light control block
		bool SetAction(byte index, vector<Afx_action>* act);

		// Set action for Power button and store other light colors as default
		// act - pointer to vector of light control blocks
		bool SetPowerAction(vector<Afx_lightblock> *act, bool save = false);

		// Hardware enable/disable/dim lights
		// brightness - desired brightness (0 - off, 255 - full)
		// mappings - needed to enable some lights for v1-v4 and for software emulation
		// power - if true, power and indicator lights will be set too
		bool ToggleState(BYTE brightness, vector <Afx_light>* mappings, bool power);

		// Global (whole device) effect control for APIv5, v8
		// effType - effect type
		// mode - effect mode (off, steady, keypress, etc)
		// tempo - effect tempo
		// act1 - first effect color
		// act2 - second effect color (not for all effects)
		bool SetGlobalEffects(byte effType, byte mode, byte tempo, Afx_action act1, Afx_action act2);

		// Apply changes and update colors
		bool UpdateColors();

		// get PID for current device
		int GetPID();

		// get VID for current device
		int GetVID();

		// get API version for current device
		int GetVersion();

		// get data length for current device
		int GetLength();

		// check global effects availability
		bool IsHaveGlobal();
	};

	struct Afx_device { // Single device data
		WORD vid, pid;
		Functions* dev = NULL; // device object pointer
		string name;
		Afx_colorcode white = { 255,255,255 }; // white point
		vector <Afx_light> lights;
	};

	class Mappings {
	private:
		vector <Afx_group> groups; // Defined light groups
		vector <Afx_grid> grids; // Grid zones info

	public:

		vector<Afx_device> fxdevs; // main devices/mappings array
		unsigned activeLights = 0,  // total number of active lights into the system
				 activeDevices = 0; // total number of active devices

		~Mappings();

		// Enumerate all alienware devices into the system
		// acc - link to AlienFan_SDK::Control object for ACPI lights
		// returns vector of active device objects
		vector<Functions*> AlienFXEnumDevices(void* acc);

		// Apply device vector to fxdevs structure
		// activeOnly - clear inactive devices from list
		// devList - list of active devices
		// brightness - default device brightness
		// power - set brightness to power/indicator lights as well
		void AlienFXApplyDevices(bool activeOnly, vector<Functions*> devList, byte brightness, bool power);

		// Load device data and assign it to structure, as well as init devices and set brightness
		// activeOnly - clear inactive devices from list
		// acc - link to AlienFan_SDK::Control object
		// brightness - default device brightness
		// power - set brightness to power/indicator lights as well
		void AlienFXAssignDevices(bool activeOnly = true, void* acc = NULL, byte brightness=255, bool power=false);

		// load light names from registry
		void LoadMappings();

		// save light names into registry
		void SaveMappings();

		// get saved light structure by device ID and light ID
		Afx_light* GetMappingByID(WORD pid, WORD vid);

		// get defined groups vector
		vector <Afx_group>* GetGroups();

		// get defined grids vector
		vector <Afx_grid>* GetGrids() { return &grids; };

		// get grid object by it's ID
		Afx_grid* GetGridByID(byte id);

		// get device structure by PID/VID.
		// VID can be zero for any VID
		Afx_device* GetDeviceById(WORD pid, WORD vid = 0);

		// get or add device structure by PID/VID
		// VID can be zero for any VID
		Afx_device* AddDeviceById(WORD pid, WORD vid);

		// find light mapping into device structure by light ID
		Afx_light* GetMappingByDev(Afx_device* dev, WORD LightID);

		// find light group by it's ID
		Afx_group* GetGroupById(DWORD gid);

		// remove light mapping from device by id
		void RemoveMapping(Afx_device* dev, WORD lightID);

		// get light flags (Power, indicator, etc) from light structure
		int GetFlags(Afx_device* dev, WORD lightid);

		// get light flags (Power, indicator) by DevID (PID/VID)
		int GetFlags(DWORD devID, WORD lightid);
	};

}
