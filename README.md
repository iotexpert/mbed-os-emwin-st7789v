# mbed-os-emwin-st7789v
This repository contains the configuration files required to run emWin using the CY8CKIT-028-TFT shield.  That shield has a Sitronix ST7789V Display driver that is attached using a parallel bus.

These files contain the GUI configuration files as well as the the ST7789V interface files.  The interface is implemented using the mbedos HAL.

The pins are correct for the targets
* CY8CKIT062_WIFI_BT
* CY8CKIT062S2_43012
* CY8CKIT_062_BLE

To make an emWin project using these files you should
* mbed add git@github.com:iotexpert/mbed-os-emwin-st7789v.git
* mbed add git@github.com:cypresssemiconductorco/emwin.git


To use these two libraries you need to add the emWin library to mbed_app.json
```json
"target_overrides": {
        "*": {
            "target.components_add": ["EMWIN_OSNTS"]
        }
        }
```
Here is an example main.cpp
```
#include "mbed.h"
#include "GUI.h"

int main()
{
    GUI_Init();
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_BLACK);
    GUI_SetFont(GUI_FONT_32B_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    GUI_DispStringAt("Hello World", GUI_GetScreenSizeX()/2,GUI_GetScreenSizeY()/2 - GUI_GetFontSizeY()/2);

}
```

If you need to use it for a different kit you can add pins using the target overides like this:
```json
"target_overrides": {
        "*": {
            "target.components_add": ["EMWIN_OSNTS"]
        },
        "CY8CKIT_NEWKIT" : {
            "ST7789V_TFT.TFTRD":"P12_3"
        }
    }
```
All of the pins are defined in mbed_lib.json
```json
{
    "name" : "ST7789V_TFT",
    "config": {
        "TFTRD":"P12_3",
        "TFTWR":"P12_0",
        "TFTDC":"P12_1",
        "TFTRST":"P12_2",

        "DB8":"P9_0",
        "DB9":"P9_1",
        "DB10":"P9_2",
        "DB11":"P9_4",
        "DB12":"P9_5",
        "DB13":"P0_2",
        "DB14":"P13_0",
        "DB15":"P13_1"
    },
    "target_overrides": {
        "CY8CKIT_062S2_43012" : {
           "DB13":"P5_7",
           "DB14":"P7_5",
           "DB15":"P7_6"
        }
    }
}
```
