static uint8_t fan_control_running = 0;

int sm_set_fan_policy(uint8_t unk, uint8_t fan_mode, uint8_t fan_speed)
{
	f_desc_t f;
	f.addr = (void *)MKA(sm_set_fan_policy_symbol);
	f.toc  = (void *)MKA(TOC);
	int(*func)(uint64_t, uint8_t,uint8_t,uint8_t) = (void *)&f;

	int ret = func(MKA(sysmem_obj), unk, fan_mode, fan_speed);

	return ret;
}

static int sm_get_fan_speed(void)
{
	uint8_t st;
	uint8_t mode;
	uint8_t fan_speed;
	uint8_t unk;

	f_desc_t f;
	f.addr = (void*)MKA(sm_get_fan_policy_symbol);
	f.toc  = (void*)MKA(TOC);
	int(*func)(uint64_t, uint8_t, uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint64_t) = (void*)&f;

	func(MKA(sysmem_obj), 0, &st, &mode, &fan_speed, &unk, 10000000);

	return fan_speed;
}

LV2_SYSCALL2(int, sm_set_fan_policy_sc,(uint8_t unk, uint8_t fan_mode, uint8_t fan_speed))
{
	// fan modes: 1 = SYSCON, 2 = MANUAL
	if(fan_mode == 2) fan_control_running = 0; // disable internal fan control if fan speed is set manually via syscall 389

	return sm_set_fan_policy(unk, fan_mode, fan_speed);
}

LV2_SYSCALL2(int, sm_get_fan_policy_sc,(uint8_t id, uint8_t *st, uint8_t *policy, uint8_t *mode, uint8_t *duty))
{
	uint8_t st1;
	uint8_t policy1;
	uint8_t mode1;
	uint8_t duty1;
	f_desc_t f;
	f.addr = (void*)MKA(sm_get_fan_policy_symbol);
	f.toc  = (void*)MKA(TOC);
	int(*func)(uint64_t, uint8_t, uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint64_t) = (void*)&f;

	int ret = func(MKA(sysmem_obj), id, &st1, &policy1, &mode1, &duty1, 10000000);

	if(ret == 0)
	{
		ret = copy_to_user(&st1, st, 1);
		if(ret == 0)
		{
			ret = copy_to_user(&policy1, policy, 1);
			if(ret == 0)
			{
				ret = copy_to_user(&mode1, mode, 1);
				if(ret == 0)
				{
					ret = copy_to_user(&duty1, duty, 1);
				}
			}
		}
	}
	return ret;
}

static void get_temperature(uint32_t id, uint32_t *temp)
{
	f_desc_t f;
	f.addr = (void*)MKA(sm_get_temperature_symbol);
	f.toc  = (void*)MKA(TOC);
	int(*func)(uint64_t, uint32_t, uint32_t *, uint64_t) = (void*)&f;
	func(MKA(sysmem_obj), id, temp, 1000000);
	*temp >>= 24; // return °C
}

static void fan_control(uint64_t arg0)
{
	DPRINTF("FAN CONTROL: started.\n");

	uint32_t t_cpu, t_rsx, prev = 0; fan_control_running = 1;

	while(fan_control_running)
	{
		timer_usleep(SECONDS(10));

		if(fan_control_running) // Avoid activating the previous mode
		{
			t_cpu = t_rsx = 0;
			get_temperature(0, &t_cpu);
			get_temperature(1, &t_rsx);

			if(t_rsx > t_cpu) t_cpu = t_rsx;
			if(prev == t_cpu) continue;

			// 60°C=31%, 61°C=33%, 62°C=35%, 63°C=37%, 64°C=39%, 65°C=41%, 66°C=43%, 67°C=45%, 68°C=47%, 69°C=49%
			// 70°C=50%, 71°C=53%, 72°C=56%, 73°C=59%, 74°C=62%, 75°C=65%, 76°C=68%, 77°C=71%, 78°C=74%, 79°C=77%,+80°C=80%

			if(t_cpu >= 80)
				sm_set_fan_policy(0, 2, 0xCC); // 80%
			else if(t_cpu >= 70)
				sm_set_fan_policy(0, 2, 0x80 + 0x8*(t_cpu - 70)); // 50% + 3% per degree °C
			else if(t_cpu >= 60)
				sm_set_fan_policy(0, 2, 0x50 + 0x5*(t_cpu - 60)); // 30% + 2% per degree °C
			else
				sm_set_fan_policy(0, 1, 0); // SYSCON < 60°C

			prev = t_cpu;
		}
	}

	ppu_thread_exit(0);
}

void do_fan_control(void)
{
	thread_t fan_control_id;

	if(!fan_control_running)
		ppu_thread_create(&fan_control_id, fan_control, 0, -0x1D8, 0x4000, 0, "fan_control");
}
