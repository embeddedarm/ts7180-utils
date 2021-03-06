#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "load_fpga-ts7180.h"
#include "ispvm.h"

int main(int argc, char **argv)
{
	int x;
	struct ispvm_f hardware;

	const char * ispvmerr[] = { "pass", "verification fail",
	  "can't find the file", "wrong file type", "file error",
	  "option error", "crc verification error" };

	if(argc != 2) {
		printf("Usage: %s file.vme\n", argv[0]);
		return 1;
	}

	hardware.init = init_ts7180;
	hardware.restore =restore_ts7180;
	hardware.readport = readport_ts7180;
	hardware.writeport = writeport_ts7180;
	hardware.sclock = sclock_ts7180;
	hardware.udelay = udelay_imx6;

	x = ispVM(&hardware, argv[1]);

	if (x == 0) {
		printf("loadfpga_ok=1\n");
	} else {
		assert(x < 0);
		printf("loadfpga_ok=0\n");
		printf("loadfpga_error=\"%s\"\n", ispvmerr[-x]);
	}

	return 0;
}
