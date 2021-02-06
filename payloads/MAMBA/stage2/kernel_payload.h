#define kplugin_base_address	0x80000000007f0000

int inst_and_run_kernel(uint8_t *payload, int size)
{
	if((size < 4) || (size > KB(64)))
		return EINVAL;

	if(!payload)
		return ESRCH;

	memcpy((void *)kplugin_base_address, get_secure_user_ptr(payload), size);

	f_desc_t f;
	f.addr = (void *)kplugin_base_address;
	f.toc = (void *)MKA(TOC);

	int (* func)(void);
	func = (void *)&f;
	func();
	return SUCCEEDED;
}

int inst_and_run_kernel_dynamic(uint8_t *payload, int size, uint64_t *residence)
{
	if(size < 4)
		return EINVAL;

	if(!payload)
		return ESRCH;

	void *skprx = malloc(size);

	if(skprx)
	{
		memcpy(skprx, get_secure_user_ptr(payload), size);

		f_desc_t f;
		f.addr = skprx;
		f.toc = (void *)MKA(TOC);

		int (* func)(void);
		func = (void *)&f;
		func();

		uint64_t resident = (uint64_t)skprx;
		copy_to_user(&resident, get_secure_user_ptr(residence), 8);
		return 1;
	}

	return 0;
}

int unload_plugin_kernel(uint64_t residence)
{
	if(residence)
		free((uint64_t *)residence);

	return SUCCEEDED;
}
