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

#include "precompiler.h"
#include "Native/Native_List.h"
#include "Native/Settings.h"
#include "Player/player.h"
#include "Vehicle/VehicleData.h"
#include "Vehicle/Sync.h"
#include "Vehicle/SlotManager.h"


extern void* pAMXFunctions;

std::set<AMX*> global_Amx;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
	// Clear vehicle data
	VehicleData::vList.clear();

	// Clear players
	Player::pList.clear();

	// Reset Slot Manager
	SlotManager::Reset();


	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	bool load = sampgdk::Load(ppData);
	sampgdk::logprintf("");
	sampgdk::logprintf(" ===============================");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("      --<Test Version>--        ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("    Vehicle Streamer Loaded     ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("        Version: v1.0           ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("    Developer: Burak (NexoR)    ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf(" ===============================");
	sampgdk::logprintf("");
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	// Clear vehicle data
	VehicleData::vList.clear();

	// Clear players
	Player::pList.clear();

	// Reset Slot Manager
	SlotManager::Reset();

	sampgdk::logprintf("");
	sampgdk::logprintf(" ===============================");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("      --<Test Version>--        ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("    Vehicle Streamer Unloaded   ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("        Version: v1.0           ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf("    Developer: Burak (NexoR)    ");
	sampgdk::logprintf("                                ");
	sampgdk::logprintf(" ===============================");
	sampgdk::logprintf("");
	sampgdk::Unload();
}

extern "C" const AMX_NATIVE_INFO native_list[] =
{
	// Settings
	REG_AMX_NATIVE(Vehicle_GetTickRate)
	REG_AMX_NATIVE(Vehicle_SetTickRate)
	
	// Vehicle
	REG_AMX_NATIVE(CreateDynamicVehicle)
	REG_AMX_NATIVE(DestroyDynamicVehicle)
	REG_AMX_NATIVE(IsDynamicVehicleStreamedIn)
	REG_AMX_NATIVE(GetDynamicVehiclePos)
	REG_AMX_NATIVE(SetDynamicVehiclePos)
	REG_AMX_NATIVE(GetDynamicVehicleZAngle)
	REG_AMX_NATIVE(GetDynamicVehicleRotationQuat)
	REG_AMX_NATIVE(GetDynVehicleDistanceFromPoint)
	REG_AMX_NATIVE(SetDynamicVehicleZAngle)
	REG_AMX_NATIVE(SetDynamicVehicleParamsEx)
	REG_AMX_NATIVE(GetDynamicVehicleParamsEx)
	REG_AMX_NATIVE(GetDynVehicleParamsSirenState)
	REG_AMX_NATIVE(SetDynamicVehicleParamsCarDoors)
	REG_AMX_NATIVE(GetDynamicVehicleParamsCarDoors)
	REG_AMX_NATIVE(SetDynVehicleParamsCarWindows)
	REG_AMX_NATIVE(GetDynVehicleParamsCarWindows)
	REG_AMX_NATIVE(SetDynamicVehicleToRespawn)
	REG_AMX_NATIVE(SetDynamicVehicleInterior)
	REG_AMX_NATIVE(GetDynamicVehicleInterior)
	REG_AMX_NATIVE(AddDynamicVehicleComponent)
	REG_AMX_NATIVE(RemoveDynamicVehicleComponent)
	REG_AMX_NATIVE(ChangeDynamicVehicleColor)
	REG_AMX_NATIVE(ChangeDynamicVehiclePaintjob)
	REG_AMX_NATIVE(SetDynamicVehicleHealth)
	REG_AMX_NATIVE(GetDynamicVehicleHealth)
	REG_AMX_NATIVE(SetDynamicVehicleNumberPlate)
	REG_AMX_NATIVE(GetDynamicVehicleModel)
	REG_AMX_NATIVE(GetDynVehicleComponentInSlot)
	REG_AMX_NATIVE(RepairDynamicVehicle)
	REG_AMX_NATIVE(GetDynamicVehicleVelocity)
	REG_AMX_NATIVE(SetDynamicVehicleVelocity)
	REG_AMX_NATIVE(SetDynVehicleAngularVelocity)
	REG_AMX_NATIVE(GetDynamicVehicleDamageStatus)
	REG_AMX_NATIVE(UpdateDynVehicleDamageStatus)
	REG_AMX_NATIVE(SetDynamicVehicleVirtualWorld)
	REG_AMX_NATIVE(GetDynamicVehicleVirtualWorld)
	REG_AMX_NATIVE(PutPlayerInDynamicVehicle)
	REG_AMX_NATIVE(GetPlayerDynamicVehicleID)
	REG_AMX_NATIVE(IsPlayerInDynamicVehicle)
	REG_AMX_NATIVE(PlayerSpectateDynamicVehicle)
	REG_AMX_NATIVE(IsValidDynamicVehicle)

	// NULL
	{NULL, NULL}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	global_Amx.insert(amx);
	return amx_Register(amx, native_list, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	// Clear vehicle data
	VehicleData::vList.clear();

	// Clear players
	Player::pList.clear();

	// Reset Slot Manager
	SlotManager::Reset();

	global_Amx.erase(amx);
	return AMX_ERR_NONE;
}

bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	Player::pList.push_back(playerid);
	return true;
}

bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	auto it = std::find(Player::pList.begin(), Player::pList.end(), playerid);
	if (it != Player::pList.end())
	{
		Player::pList.erase(it);
	}
	return true;
}

bool PLUGIN_CALL OnPlayerEnterVehicle(int playerid, int vehicleid, bool ispassenger)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnPlayerEnterDynamicVehicle", &idx))
				{
					amx_Push(*j, ispassenger);
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnPlayerExitVehicle(int playerid, int vehicleid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnPlayerExitDynamicVehicle", &idx))
				{
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnUnoccupiedVehicleUpdate(int vehicleid, int playerid, int passenger_seat, float new_x, float new_y, float new_z, float vel_x, float vel_y, float vel_z)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnUnoccupiedDynVehicleUpdate", &idx))
				{
					amx_Push(*j, amx_ftoc(vel_z));
					amx_Push(*j, amx_ftoc(vel_y));
					amx_Push(*j, amx_ftoc(vel_x));
					amx_Push(*j, amx_ftoc(new_z));
					amx_Push(*j, amx_ftoc(new_y));
					amx_Push(*j, amx_ftoc(new_x));
					amx_Push(*j, passenger_seat);
					amx_Push(*j, playerid);
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleDamageStatusUpdate(int vehicleid, int playerid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynVehicleDamageStatusUpdate", &idx))
				{
					amx_Push(*j, playerid);
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleDeath(int vehicleid, int killerid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			// araç patlayinca ilk oluþturulan konuma ayarla ve hasarlari sifirla
			it->second->lock_mode = true;

			it->second->x = it->second->cx;
			it->second->y = it->second->cy;
			it->second->z = it->second->cz;
			it->second->rotation = it->second->cr;

			it->second->arac_hp = 1000.0f;

			it->second->hasar_doors = 0;
			it->second->hasar_lights = 0;
			it->second->hasar_panels = 0;
			it->second->hasar_tires = 0;

			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleDeath", &idx))
				{
					amx_Push(*j, killerid);
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleMod(int playerid, int vehicleid, int componentid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleMod", &idx))
				{
					amx_Push(*j, componentid);
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehiclePaintjob(int playerid, int vehicleid, int paintjobid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehiclePaintjob", &idx))
				{
					amx_Push(*j, paintjobid);
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleRespray(int playerid, int vehicleid, int color1, int color2)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleRespray", &idx))
				{
					amx_Push(*j, color2);
					amx_Push(*j, color1);
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleSirenStateChange(int playerid, int vehicleid, int newstate)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynVehicleSirenStateChange", &idx))
				{
					amx_Push(*j, newstate);
					amx_Push(*j, it->first);
					amx_Push(*j, playerid);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleSpawn(int vehicleid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			// arac patlamasi bitince tekrar senkronize moduna al
			it->second->lock_mode = false;

			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleSpawn", &idx))
				{
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleStreamIn(int vehicleid, int forplayerid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleStreamIn", &idx))
				{
					amx_Push(*j, forplayerid);
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

bool PLUGIN_CALL OnVehicleStreamOut(int vehicleid, int forplayerid)
{
	for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
	{
		if (it->second->real_id == vehicleid)
		{
			int idx;
			for (std::set<AMX*>::iterator j = global_Amx.begin(); j != global_Amx.end(); j++)
			{
				if (!amx_FindPublic(*j, "OnDynamicVehicleStreamOut", &idx))
				{
					amx_Push(*j, forplayerid);
					amx_Push(*j, it->first);
					amx_Exec(*j, NULL, idx);
				}
			}
			break;
		}
	}
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	int n = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	if (n > vLastTick_Rate)
	{
		vSync::Vehicle_Sync();
		vLastTick_Rate = n + vTick_Rate;
	}
}