#include<stdio.h>
#include "Helpers/Std_Types.h"

#define LOWCMDREG(REG,VAL) REG=(REG&0xF0)|(VAL&0x0F)
#define HEIGHCMDREG(REG,VAL) REG=(REG&0xF0)|(VAL>>4)

int main (){
    uint8 port,Valu;
    port = 0x50;
    Valu = 0x28;
    printf("%00X\n",(LOWCMDREG(port,Valu)));
    printf("%00X\n",HEIGHCMDREG(port,Valu));
    
    return 0;
}