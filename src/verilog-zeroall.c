#include <stdio.h>
#include "verilog-zeroall.h"

#include <vpi_user.h>

static int zeroall_compile(char * user_data) {
	return 0;
}

static void reset_regs(vpiHandle module) {
	vpiHandle reg, i;
	s_vpi_value value;
	int size, j;
	char * charData;

	value.format = vpiBinStrVal;
	i = vpi_iterate(vpiReg, module);

	while (reg = vpi_scan(i)) {
		vpi_get_value(reg, &value);
		charData = value.value.str;
		size = vpi_get(vpiSize, reg);
		for (j = 0; j < size; j++) {
			if (charData[j] == 'x') {
				charData[j] = '0';
			}
		}
		vpi_put_value(reg, &value, NULL, vpiNoDelay);
	}
}

static void module_iterate(vpiHandle i) {
	vpiHandle module;
	while (module = vpi_scan(i)) {
		vpi_printf("%s\n", vpi_get_str(vpiFullName, module));
		reset_regs(module);
		module_iterate(vpi_iterate(vpiModule, module));
	}
}

static int zeroall_call(char * user_data) {
	module_iterate(vpi_iterate(vpiModule, NULL));

	return 0;
}

void zeroall_register() {
	s_vpi_systf_data tf_data;

	tf_data.type      = vpiSysTask;
	tf_data.tfname    = "$zeroall";
	tf_data.calltf    = zeroall_call;
	tf_data.compiletf = zeroall_compile;

	vpi_register_systf(&tf_data);

	vpi_printf("VPI module verilog-zeroall registered\n");
}

API void(*vlog_startup_routines[])() = {
	zeroall_register,
	0
};