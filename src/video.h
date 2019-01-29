#pragma once

#define BIT(n)               (0x01<<(n))

#define BIOS_VIDEO        0x10
#define VIDEO_MODE        0x00
#define VBE_MODE          0x4F
#define LINEAR_MODE       BIT(14)



#define SET_VBE_MODE      0x02
#define VBE_GET_MODE_INFO 0x4F01
#define VBE_CTRL_INFO     0x4F00
#define INDEXED_MODE      0x105
#define DIRECT_32_BITS    0x144
#define H_SIZE            1024
#define V_SIZE            768


#define MOVEMENT_SIZE_X     68
#define MOVEMENT_SIZE_Y     76

#define ENEMY_SIZE        20

