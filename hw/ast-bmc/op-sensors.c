/* Copyright 2015 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 */
#include <skiboot.h>
#include <device.h>
#include <cpu.h>
#include <opal-api.h>
#include <sensor.h>
#include <ast.h>

int64_t op_opal_read_sensor(uint32_t sensor_hndl, int token,
		uint32_t *sensor_data)
{
	int64_t rc = 0, val = -1;

	prlog(PR_INSANE, "op_opal_read_sensor [%08x], %d\n", sensor_hndl,
		token);

	if (!sensor_hndl) {
		rc = OPAL_PARAMETER;
		goto out;
	}

	rc = occ_read_sensor(this_cpu()->chip_id, sensor_hndl, &val);
	*sensor_data = val;
out:
	return rc;
}

void op_init_sensor(void)
{
	struct dt_node *op_node;

	op_node = dt_new(sensor_node, "power#1-data");
	dt_add_property_string(op_node, "compatible", "ibm,opal-sensor-power");
	dt_add_property_cells(op_node, "sensor-id", 0x16);

	op_node = dt_new(sensor_node, "amb-temp#1-data");
	dt_add_property_string(op_node, "compatible",
				"ibm,opal-sensor-amb-temp");
	dt_add_property_cells(op_node, "sensor-id", 0x14);

	op_node = dt_new(sensor_node, "cooling-fan#1-data");
	dt_add_property_string(op_node, "compatible",
				"ibm,opal-sensor-cooling-fan");
	dt_add_property_cells(op_node, "sensor-id", 0x1B);
}
