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

#include "Func.h"
#include "VehicleData.h"

float vFunction::Veh_Dist(float pX, float pY, float pZ, float vX, float vY, float vZ)
{
	return sqrt(powf(vX - pX, 2) + powf(vY - pY, 2) + powf(vZ - pZ, 2) * 1.0);
}

void vFunction::Vehicle_Create(size_t vehicleid)
{
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		int vid = CreateVehicle(it->second->modelid, it->second->x, it->second->y, it->second->z, it->second->rotation, it->second->color1, it->second->color2, it->second->respawn, it->second->addsiren);
		if (vid != INVALID_VEHICLE_ID)
		{
			// set real id
			it->second->real_id = vid;

			// set world
			SetVehicleVirtualWorld(vid, it->second->world);
			
			// set interior
			LinkVehicleToInterior(vid, it->second->interior);
			
			// set mod
			for (int i = 0; i < 14; i++)
			{
				if (it->second->modifiye[i] != 0)
				{
					AddVehicleComponent(vid, it->second->modifiye[i]);
				}
			}

			// set paintjob
			ChangeVehiclePaintjob(vid, it->second->paintjob);
			
			// set health
			SetVehicleHealth(vid, it->second->arac_hp);
			
			// set plate
			if (it->second->plaka.length() != 0)
			{
				SetVehicleNumberPlate(vid, it->second->plaka.c_str());
			}

			// Set Params
			SetVehicleParamsEx(
				vid,
				it->second->engine,
				it->second->lights,
				it->second->alarm,
				it->second->doors,
				it->second->bonnet,
				it->second->boot,
				it->second->objective
			);

			// Set Door
			SetVehicleParamsCarDoors(
				vid,
				it->second->kapi_driver,
				it->second->kapi_passenger,
				it->second->kapi_backleft,
				it->second->kapi_backright
			);

			// Set Windows
			SetVehicleParamsCarWindows(
				vid,
				it->second->cam_driver,
				it->second->cam_passenger,
				it->second->cam_backleft,
				it->second->cam_backright
			);

			// Set Damage
			UpdateVehicleDamageStatus(
				vid,
				it->second->hasar_panels,
				it->second->hasar_doors,
				it->second->hasar_lights,
				it->second->hasar_tires
			);
		}
	}
}