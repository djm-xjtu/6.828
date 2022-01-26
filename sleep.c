#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char const *argv[]) //第0个参数是程序名
{
	if (argc != 2)
	{
		fprintf(2, "fail to pass time\n");
		exit(1);
	}
	int time = atoi(argv[1]);
	sleep(time);
	
	exit(0);
}