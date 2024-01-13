#include "include/model.h"
#include "include/syscon.h"

console_type model_get_type(int for_display)
{
	const unsigned int hardware_info = syscon_get_hardware_info();
	unsigned int *hw_info = &hardware_info; // Stupid, I know
	console_type type = TYPE_UNKNOWN;

	if (hw_info[2] == IRS002 || hw_info[2] == IRS1001) {
		type = TYPE_FAT;
	} else if (hw_info[2] == USS1001 || hw_info[2] == USS1002) {
		type = TYPE_SLIM;
	} else if (hw_info[2] == DOL1001 || hw_info[2] == DOL1002) {
		type = TYPE_PSTV;
	}  else if (hw_info[2] == IRT002) {
		if (for_display)
			return TYPE_FAT;
		type = TYPE_DEVKIT;
	}

	return type;
}
