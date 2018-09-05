# AlienFX-SDK
Better AlienFX/LightFX SDK than Dell official's one without any limitations.

Dell official SDK does a very terrible job if you want to change LED color in quick succession. Their official SDK comes with 3 seconds delay and behaves pretty weird in general.
This SDK not only fixes up its issue and performs better but is written from scratch by reverse engineerig USB protocol. It sends byte data directly to USB which then changes zones color. This also removes the dependency from their Command Center software and works irrespective of settings set in stock software. In other words, you can finally achieve Rainbow effect across all LED's like it was intended without any lag.  This SDK also lets you change color of zones that are not possible with official SDK such as Macro keys, power button etc.

Please checkout Sample App for reference.

**Currently tested on AW13/R3, AW15R2/R3, AW17R3/R4 but should be working with all alienware laptops**

### Initialization
```C++
//Returns PID value if init is successful or -1 if failed. Takes Vendor ID as argument.
int isInit = AlienFX_SDK::Functions::AlienFXInitialize(AlienFX_SDK::vid);

```

### Set Color
```C++
//Make sure your device is ready to process new instructions before updating color
bool result = AlienFX_SDK::Functions::IsDeviceReady();
std::cout << "\nReady: " << result; 

//Takes index of the location you want to update as first argument and Red, Green and Blue values for others.
AlienFX_SDK::Functions::SetColor(AlienFX_SDK::Index::AlienFX_leftZone, 225, 134, 245);
AlienFX_SDK::Functions::SetColor(AlienFX_SDK::Index::AlienFX_rightZone, 25, 114, 245);

//This is important to apply the updated color changes. Should only be called once after you're done with new colors.
AlienFX_SDK::Functions::UpdateColors();
```

#### Projects using this SDK

[Project Aurora](https://github.com/antonpup/Aurora).
