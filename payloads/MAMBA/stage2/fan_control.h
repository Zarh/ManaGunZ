#ifdef FAN_CONTROL
//#include <lv2/ctrl.h>

#define SYS_SHUTDOWN			0x0100
#define SYS_SHUTDOWN2			0x1100

static u8 fan_control_running = 0;

u8 set_fan_speed = 0;

static int sm_get_fan_speed(void)
{
	u8 st;
	u8 mode;
	u8 fan_speed;
	u8 unk;

	sm_get_fan_policy(0, &st, &mode, &fan_speed, &unk);

	return fan_speed;
}

static void fan_control(u64 arg0)
{
	#ifdef DEBUG
	DPRINTF("FAN CONTROL: started.\n");
	#endif

	u32 t_cpu, t_rsx, prev = 0;
	fan_control_running = 1;

	while(fan_control_running)
	{
		timer_usleep(SECONDS(10));

		if(fan_control_running) // Avoid activating the previous mode
		{
			t_cpu = t_rsx = 0;

			sm_get_temperature(0, &t_cpu);
			sm_get_temperature(1, &t_rsx);

			if(t_rsx > t_cpu) t_cpu = t_rsx; // compare highest temperature
			if(prev == t_cpu) continue;		 // temperature didn't change

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

void load_fan_control(void)
{
	if(set_fan_speed == 0) // Disabled
		fan_control_running = 0;
	else if(set_fan_speed >= 0x33 && set_fan_speed <= 0x80)
		sm_set_fan_policy(0, 2, set_fan_speed); // Manual mode
	else if(set_fan_speed == 1)
		sm_set_fan_policy(0, 1, 0); // SYSCON mode
	else // if(set_fan_speed >= 2 && set_fan_speed <= 0x32)
		do_fan_control();  // Dynamic fan control
}

LV2_HOOKED_FUNCTION_COND_POSTCALL_3(int, sm_set_fan_policy_sc, (u8 unk, u8 _fan_mode, u8 _fan_speed))
{
	fan_control_running = 0; // disable internal fan control if fan speed is set manually via syscall 389
	return DO_POSTCALL;
}

LV2_HOOKED_FUNCTION_COND_POSTCALL_3(int, sys_shutdown, (uint16_t op, const void *buf, u64 size))
{
	// Avoids max FAN speed after a shutdown by Evilnat
	if(op == SYS_SHUTDOWN || op == SYS_SHUTDOWN2)
	{
		#ifdef DEBUG
		DPRINTF("Shutdown executed, resetting FAN policy\n");
		#endif
		sm_set_fan_policy(0, 1, 0);
	}

	return DO_POSTCALL;
}

void fan_patches(void)
{
	hook_function_with_cond_postcall(get_syscall_address(SYS_SM_SET_FAN_POLICY), sm_set_fan_policy_sc, 3);
	hook_function_with_cond_postcall(get_syscall_address(SYS_SM_SHUTDOWN), sys_shutdown, 3);
}

void unhook_all_fan_patches(void)
{
	suspend_intr();
	unhook_function_with_precall(get_syscall_address(SYS_SM_SET_FAN_POLICY), sm_set_fan_policy_sc, 3);
	unhook_function_with_precall(get_syscall_address(SYS_SM_SHUTDOWN), sys_shutdown, 3);
	resume_intr();
}
#endif
