/**
 * Test file for library to interact with switches
 * 
 * Run this test in conjunction with the simulator 
 * GUI. As you press buttons on the GUI, the respective
 * switches will change from '0' to '1' on the CLI display
 * to show that pressing the buttons is read by the BSP
 */ 

#include "common.h"
#include "config.h"
#include <bsp.h>

int main() {
    BSP_Switches_Init();
    printf("LT\tRT\tHDLT\tFWD/REV\tHZD\tCRS_SET\tCRS_EN\tREGEN\tIGN_1\tIGN_2\n");
    while(1) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r", 
                BSP_Switches_Read(LT),
                BSP_Switches_Read(RT),
                BSP_Switches_Read(HDLT),
                BSP_Switches_Read(FWD_REV),
                BSP_Switches_Read(HZD),
                BSP_Switches_Read(CRS_SET),
                BSP_Switches_Read(CRS_EN),
                BSP_Switches_Read(REGEN),
                BSP_Switches_Read(IGN_1),
                BSP_Switches_Read(IGN_2));
    }
    printf("\n");
}