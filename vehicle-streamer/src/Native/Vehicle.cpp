/*
 * Copyright (C) 2021 Burak (NexoR)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Vehicle.h"
#include "../Vehicle/SlotManager.h"
#include "../Vehicle/VehicleData.h"

cell AMX_NATIVE_CALL Native::CreateDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(12);

	int modelid       = static_cast<int>(params[1]);
	float x           = static_cast<float>(amx_ctof(params[2]));
	float y           = static_cast<float>(amx_ctof(params[3]));
	float z           = static_cast<float>(amx_ctof(params[4]));
	float r           = static_cast<float>(amx_ctof(params[5]));
	int color1        = static_cast<int>(params[6]);
	int color2        = static_cast<int>(params[7]);
	int respawn_delay = static_cast<int>(params[8]);
	int addsiren      = static_cast<int>(params[9]);
	int world         = static_cast<int>(params[10]);
	int interior      = static_cast<int>(params[11]);
	float dist        = static_cast<float>(amx_ctof(params[12]));

	size_t vehicleid = SlotManager::Free_ID();

	std::unique_ptr<vdata> v(new vdata());

	v->real_id = INVALID_REAL_ID;
	v->modelid = modelid;
	v->x = x;
	v->y = y;
	v->z = z;
	v->rotation = r;
	v->color1 = color1;
	v->color2 = color2;
	v->respawn = respawn_delay;
	v->addsiren = addsiren;
	v->world = world;
	v->interior = interior;
	v->distance = dist;
	for (int i = 0; i < 14; i++)
	{
		v->modifiye[i] = 0;
	}
	v->paintjob = 3;
	v->arac_hp = 1000.0;
	v->plaka[0] = '\0';
	v->engine = -1;
	v->lights = -1;
	v->alarm = -1;
	v->doors = -1;
	v->bonnet = -1;
	v->boot = -1;
	v->objective = -1;

	v->kapi_driver = 0;
	v->kapi_passenger = 0;
	v->kapi_backleft = 0;
	v->kapi_backright = 0;

	v->cam_driver = 0;
	v->cam_passenger = 0;
	v->cam_backleft = 0;
	v->cam_backright = 0;

	v->hasar_panels = 0;
	v->hasar_doors = 0;
	v->hasar_lights = 0;
	v->hasar_tires = 0;

	VehicleData::vList.insert(std::make_pair(vehicleid, std::move(v)));

	return static_cast<cell>(vehicleid);
}