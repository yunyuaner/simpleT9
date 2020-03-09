#define CONFIGURE_INIT
#include "system.h"

extern void __main(int argc, char *argv[]);

void UserInit(void)
{
#ifdef USER_APP_INIT
	USER_APP_INIT
#endif
	
	int _argc = 1;
	char *_argv[] = { "testSimpleT9" };
	
	__main(_argc, _argv); 

	return;
}
