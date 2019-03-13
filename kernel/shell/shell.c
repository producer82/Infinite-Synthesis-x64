#include "shell.h"
#include "shroutine.h"
#include "stdkernel.h"

unsigned char shellLine = 1;
unsigned char *at = "Synthesis>";

void enterShell(){
	osVersion();
	clear();
}