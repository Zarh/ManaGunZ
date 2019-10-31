#include "debug.h"
#include "network.h"
#include "kernel.h"

int debug_install(void) {
	if (!has_net_support())
		return -1;

	suspend_interrupts();
	resume_interrupts();

	return 0;
}

int debug_uninstall(void) {
	if (!has_net_support())
		return -1;

	suspend_interrupts();
	resume_interrupts();

	return 0;
}
