#include "setlevel.h"
#include <gint/std/string.h>
void set_level(int id_level, char level[], int *startx, int *starty, char *gravity, int *appear, int *disappear){
switch(id_level){case 0:
memcpy(level,"111111111111111111111111100000000c300000000000100000000000c3000000K0k0l1000111ddd1111aaa111111111h11111ddd1111aaa1ddddd00000110000001110001d000000000110s00001110001d000000000111111001110001d0011d1100110b01001110001d00e000000110S01001110001d000000000110001001110001d011111000100t01000m00001d000000000000001000m00001ddddd0000001111111111111111111111111",350);
*appear=9;
*disappear=13;
break;
case 1:
memcpy(level,"10011111111dddd1111111111000111100000000000000000000011110011111111ddd100001111111001dd000ddddd111111111111001dd0t0ddddddddd11000001001dd000ddddddddd11000001001aaaaaaaaaaaaaa110s00010010000000000000e11d1100100100000000000aaa11111001001000000000ddddd1111100100100000000011111100010000010000000003000000001000001000K0000030k0001001111111111111111111111",350);
break;
case 2:
memcpy(level,"1dddddd100111111111111111000000000011111000000000000000000l01100c00000000001aaaaaaa111100c00000000011dddddddddd1001aaaaaaaaa11cccccccccc1001ddddddddd1000000000001331000000aa000000000000s10e1k0000000001ccccccccc111111111113311100000000011001000000000110000000001100b0000000001100000000011t0b00000000011000K0000011111aaaaaaaaa1111111110011111ddddddddd1",350);
*appear=12;
*disappear=1
;
break;
case 3:
memcpy(level,"11001111111001111111111111000111dddd000000000100013000111dddd00000000010003300000000dd11111000010e03100000000dd03a01000011111111110000dd03a01000000001100s1dd00ddt3a0100000000110001dd00dd1110100000000110001dd0Kdd00001ddd000ddd10001dd00dd00001111100ddd10001dd00dd00001000000ddd30001dd0000000010k000000330001dd0000000010000000031d00111111100111111111111",350);
break;
case 4:
memcpy(level,"11111111111011111dddd1111100001dd0000dd100000000011s0001dd0d11dd10000000001111001dd0d111dd00111100011dd001dt0d10000001dd100011dd001d11d10000001dd100011dd00dd11110011111dd100011dd00000000001dddddd100011dd1111dbd1111ddd111100011ddddddd0dd1d1ddd100000011ddddddd0000d1ddd1e0000011ddddddd1110d1ddd111cccc11dddddddddd0d1ddd111dddd11111111111101111111111111",350);
*appear=12;
*disappear=13;
break;
case 5:
memcpy(level,"000000000000000000000000000000000000000000000000t000000000000000000000000000011dd111111111111111110000100000100000010000001000011cc001s0000d00000001000010000e111dd0100000dd100001001111000d0000000dd100001000001000111d000ddd1000010000000000000000ddd1000011111111111d111B1111100000000000000000000000000000000000000000000000000000000000000000000000000000",350);
*appear=12;
*disappear=6;
break;
case 6:
memcpy(level,"10001011111011111111111111000101dd10001111dddd11110000101dd10001000000000001111101dd1aaa1000ccccddd110s00010013331000000000011dddd110010001mmmdd00000100000000010e010t0dd00000011111100011111d1dddddd1111k00000001d000111001111111111111101d00000000000111000010000100000000000000010K010000100011100000011110001000010001110000dd1111000101111101111111111111",350);
*appear=5;
*disappear=9;
break;
case 7:
memcpy(level,"111001111111100i0d0011111100000111ddd000i0d0000001100000000000000itd00000e1111111ddd111111111111111100000000000000000h00d0000111111111dd111110100d000110001100000000010100d0001000011000000000i0d00d0000000000000000000i0d00d00001111dd111000000ild00111111000011111ddd00i0d0011111d000011111ddd00i0d0011111d0s0011111ddd00i0d0011111111001111111100i0d0011111",350);
break;
case 8:
memcpy(level,"dddddddddddddddddddddddddBBBBBBBBBBBBBBBBBBBBBBBBB100001kk10011111dt0a000011000010010010000d11a00001100001BB100100000000000013000000000010001110000000300000000001aaaaaa0000000111111000001000000001111110dd00000001000000001000110000000a001BBBd00a0100013000000000010001000010003300s000000010K0100001e003aaBBBBBBBBBBBBBBBBBBBaaaaddddddddddddddddddddddddd",350);
break;
case 9:
memcpy(level,"00000ddddddd100000000000011111111111111111110011111000000dd1111ddd0K10000b1100111000000100000100000110000100000010000010010011000k111dd101dd00d10000011000110000001000001BBBB011000100011dd1000001dddd01100010ddd1dd1d00dd1011001133310ddd1dd1BBBBB1t00001100000ddd1dd1000001ddd1111s0000ddd1dd10000011111111BBB111aaaaa110001111111100000000000e1000000000000",350);
break;
case 10:
memcpy(level,"11111111t133111111100011111111111133311111110K01111100000100111111111000111110s00010i11111100000001111d110K10i11111d000000011111110K10i1111a001BBBBB11110000010i111d0a010000011110000010i11a03011d0ddd1111001ddd0i1d0a0d110000011110000000i0a30111100e00111100000k0130ad11110aa001111dd000001031111111ddd11111111111B1001111111aaa1111111111101001111111000111",350);
break;
case 11:
memcpy(level,"1ddddddddddd11dddddddddd11dddddddddd00000dd3aaa11i1dd111100000000000030000i1dd000000000001110003000i1d000001111100K000003000i1d00000S00k0000000003aBB110s000100000ddd011103atl11111331ddddddddddddddd1111ddd001dddddddd11d0S0ddd11ddd00d1dd11d000300000dd11ddd000000000000300000dd11dddaaa00000000d3S00e0dd11dddddd00S0d111d3d000ddd11ddddddddddddddddddddddd1",350);
break;
case 12:
memcpy(level,"1111111111010001dd11111110000001000013331001000000000000100t01000h0010000001111iB111111000h0013311111e00ik11d111000300300000d10ddi011d0010003003000s0d10aai01000010001hh1hh11111000i01h1h1100010010000011dd0i000000h00010010001a11aa01dd0dd110001001000h0110001dd1d1110S0100100010110000S0S0001ddd100h0001Kd100000S0S001111100h00011111111dddd10h0001111111111",350);
break;
case 13:
memcpy(level,"11111111111111111111111111ddddddddd0S00ddddddddddd1ddddaaaaa000000ddddddddd1ddd00S000000e0ddd0dddddd1dd000000ddddddd00000dddd1daaaa00dd11100S00S000ddd10000000d00000000000S00dd10K000h0d00001100000000dd1111000ddd000000S0d0h00dd1ddd000dd000dd000ddd000dd1dddhhdd000ddddddddd000dd1ddb00S0000100000dd0000dd1dtb00000011s000000000ddd111111d11111111111111dddd",350);
break;
case 14:
memcpy(level,"1111111111111ddd11iK1d00100000d111000000011it1d00000000d100000000011i31110011100d13331110e011ihhh11100000d100011111111i00000000000d100000011111i00111011100d1000000000011000s111111111000000000011dd0001hk001111i00Sddd001dddd00hh0000001i000111000aad1ddhddd0000000001110000001111111dd0000000111000000001111111dd000011110000000001111111111111111ddd1310001",350);
break;
case 15:
memcpy(level,"i011100dd1111dddm111ddmd1i01d1000000010S0011100S01i01d100000001000000000001i01d1cc111001hh1c11111001i01ddddddi00i000bddd00001i01dd1133i00i000lddd000K1100000000i00i00001d110011300000000i00100331d100003300000010i001s03t1d1000031111100hki0011111ddd1BB1110S01hh11100m0000aaa0000110001001d100m000000000001100e1001d100m0aaa000aaa0110d11001111111ddddddddd11",350);
*appear=4;
*disappear=7;
break;
}
set_gravity(id_level, gravity);
unsigned int x = 0;
unsigned int y = 0;
unsigned int i = 0;
while (i!=strlen(level)){
switch(level[i]){
case 's':
*startx = x;
*starty = y;
break;}
x+=16;
if(x==16*25){x=0;
y+=16;}i++;}}
void set_gravity(int id_level, char *default_gravity){
switch(id_level){case 0:
*default_gravity = 0;
break;
case 1:
*default_gravity = 0;
break;
case 2:
*default_gravity = 0;
break;
case 3:
*default_gravity = 1;
break;
case 4:
*default_gravity = 0;
break;
case 5:
*default_gravity = 0;
break;
case 6:
*default_gravity = 1;
break;
case 7:
*default_gravity = 0;
break;
case 8:
*default_gravity = 0;
break;
case 9:
*default_gravity = 0;
break;
case 10:
*default_gravity = 0;
break;
case 11:
*default_gravity = 0;
break;
case 12:
*default_gravity = 0;
break;
case 13:
*default_gravity = 0;
break;
case 14:
*default_gravity = 1;
break;
case 15:
*default_gravity = 0;
break;
}}
void del_level(char level[])
{memcpy(level,"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",350);}