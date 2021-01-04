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

extern void* pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
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
	// Clear Vehicle Data
	VehicleData::vList.clear();

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
	REG_AMX_NATIVE(vStreamer_GetTickRate)
	REG_AMX_NATIVE(vStreamer_SetTickRate)
	
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
	return amx_Register(amx, native_list, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	Player::pList.push_back(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	auto it = std::find(Player::pList.begin(), Player::pList.end(), playerid);
	if (it != Player::pList.end())
	{
		Player::pList.erase(it);
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
