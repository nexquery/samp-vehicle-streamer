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
#include "Native/Settings.h"
#include "Player/player.h"

extern void* pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	bool load = sampgdk::Load(ppData);
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	sampgdk::Unload();
}

extern "C" const AMX_NATIVE_INFO native_list[] =
{
	// Settings
	{"vStreamer_GetTickRate", Native::vStreamer_GetTickRate},
	{"vStreamer_SetTickRate", Native::vStreamer_SetTickRate},
	
	// Vehicle
	{"CreateDynamicVehicle", Native::CreateDynamicVehicle},

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
		vLastTick_Rate = n + vTick_Rate;
	}
}