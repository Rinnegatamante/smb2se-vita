#ifndef __CONFIG_H__
#define __CONFIG_H__

#define DEBUG

#define LOAD_ADDRESS 0x98000000

#define MEMORY_NEWLIB_MB 240
#define MEMORY_VITAGL_THRESHOLD_MB 12

#define DATA_PATH "ux0:data/smb2"
#define SO_PATH DATA_PATH "/" "libsmb2.so"
#define TROPHIES_FILE "ux0:data/smb2/trophies.chk"

#define SCREEN_W 960
#define SCREEN_H 544

#endif
