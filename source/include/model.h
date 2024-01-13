#ifndef MODEL_H
#define MODEL_H

#define IRT001 0x31
#define IRS002 0x40
#define IRT002 0x41
#define TVPROTO 0x51
#define IRS1001 0x60
#define DOL1001 0x70
#define DOL1002 0x72
#define USS1001 0x80
#define USS1002 0x82

typedef enum console_type {
	TYPE_UNKNOWN = -1,
	TYPE_FAT = 0,
	TYPE_SLIM = 1,
	TYPE_PSTV = 2,
	TYPE_DEVKIT = 3
} console_type;

console_type model_get_type(int for_display);

#endif