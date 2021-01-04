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

#include "Sync.h"
#include "../Player/player.h"
#include "../Vehicle/VehicleData.h"
#include "Func.h"

void vSync::Vehicle_Sync()
{
	if (!VehicleData::vList.empty() && !Player::pList.empty())
	{
		for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
		{
			if (it->second->lock_mode == false)
			{
				bool dist_ok = false;

				for (std::vector<int>::iterator p = Player::pList.begin(); p != Player::pList.end(); p++)
				{
					float pX, pY, pZ;
					GetPlayerPos(*p, &pX, &pY, &pZ);

					int pWorld = GetPlayerVirtualWorld(*p), pInterior = GetPlayerInterior(*p);

					if (vFunction::Veh_Dist(pX, pY, pZ, it->second->x, it->second->y, it->second->z) < it->second->distance)
					{
						if (it->second->world == pWorld && it->second->interior == pInterior)
						{
							dist_ok = true;

							if (it->second->real_id == INVALID_REAL_ID)
							{
								vFunction::Vehicle_Create(it->first);
								break;
							}
							else
							{
								// Pos Update
								GetVehiclePos(
									it->second->real_id, 
									&it->second->x, 
									&it->second->y, 
									&it->second->z
								);

								// Rotation Update
								GetVehicleZAngle(
									it->second->real_id, 
									&it->second->rotation
								);

								// Health Update
								GetVehicleHealth(
									it->second->real_id, 
									&it->second->arac_hp
								);

								// Params Update
								GetVehicleParamsEx(
									it->second->real_id, 
									&it->second->engine, 
									&it->second->lights, 
									&it->second->alarm, 
									&it->second->doors, 
									&it->second->bonnet, 
									&it->second->boot, 
									&it->second->objective
								);

								// Door Update
								GetVehicleParamsCarDoors(
									it->second->real_id,
									&it->second->kapi_driver,
									&it->second->kapi_passenger,
									&it->second->kapi_backleft,
									&it->second->kapi_backright
								);

								// Windows Update
								GetVehicleParamsCarWindows(
									it->second->real_id,
									&it->second->cam_driver,
									&it->second->cam_passenger,
									&it->second->cam_backleft,
									&it->second->cam_backright
								);

								// Damage Update
								GetVehicleDamageStatus(
									it->second->real_id,
									&it->second->hasar_panels,
									&it->second->hasar_doors,
									&it->second->hasar_lights,
									&it->second->hasar_tires
								);
								break;
							}
						}
					}
				}

				if (!dist_ok)
				{
					if (it->second->real_id != INVALID_REAL_ID)
					{
						DestroyVehicle(it->second->real_id);
						it->second->real_id = INVALID_REAL_ID;
					}
				}
			}
		}
	}
}