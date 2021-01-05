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

#pragma once

#include "../precompiler.h"

#define CHECK_PARAMS(n) \
	if (params[0] != (n * 4)) \
	{ \
		sampgdk::logprintf("%s: Expecting %d parameter(s), but found %d.", __func__, n, params[0] / sizeof(cell)); \
		return 0; \
	}

#define DEFINE_AMX_NATIVE(native) cell AMX_NATIVE_CALL native(AMX* amx, cell* params)
#define REG_AMX_NATIVE(native_name) {#native_name, Native::native_name},
	

namespace Native
{
	// Settings
	DEFINE_AMX_NATIVE(Vehicle_GetTickRate);
	DEFINE_AMX_NATIVE(Vehicle_SetTickRate);

	// Vehicle
	DEFINE_AMX_NATIVE(CreateDynamicVehicle);
	DEFINE_AMX_NATIVE(DestroyDynamicVehicle);
	DEFINE_AMX_NATIVE(IsDynamicVehicleStreamedIn);
	DEFINE_AMX_NATIVE(GetDynamicVehiclePos);
	DEFINE_AMX_NATIVE(SetDynamicVehiclePos);
	DEFINE_AMX_NATIVE(GetDynamicVehicleZAngle);
	DEFINE_AMX_NATIVE(GetDynamicVehicleRotationQuat);
	DEFINE_AMX_NATIVE(GetDynVehicleDistanceFromPoint);
	DEFINE_AMX_NATIVE(SetDynamicVehicleZAngle);
	DEFINE_AMX_NATIVE(SetDynamicVehicleParamsEx);
	DEFINE_AMX_NATIVE(GetDynamicVehicleParamsEx);
	DEFINE_AMX_NATIVE(GetDynVehicleParamsSirenState);
	DEFINE_AMX_NATIVE(SetDynamicVehicleParamsCarDoors);
	DEFINE_AMX_NATIVE(GetDynamicVehicleParamsCarDoors);
	DEFINE_AMX_NATIVE(SetDynVehicleParamsCarWindows);
	DEFINE_AMX_NATIVE(GetDynVehicleParamsCarWindows);
	DEFINE_AMX_NATIVE(SetDynamicVehicleToRespawn);
	DEFINE_AMX_NATIVE(SetDynamicVehicleInterior);
	DEFINE_AMX_NATIVE(GetDynamicVehicleInterior);
	DEFINE_AMX_NATIVE(AddDynamicVehicleComponent);
	DEFINE_AMX_NATIVE(RemoveDynamicVehicleComponent);
	DEFINE_AMX_NATIVE(ChangeDynamicVehicleColor);
	DEFINE_AMX_NATIVE(ChangeDynamicVehiclePaintjob);
	DEFINE_AMX_NATIVE(SetDynamicVehicleHealth);
	DEFINE_AMX_NATIVE(GetDynamicVehicleHealth);
	DEFINE_AMX_NATIVE(SetDynamicVehicleNumberPlate);
	DEFINE_AMX_NATIVE(GetDynamicVehicleModel);
	DEFINE_AMX_NATIVE(GetDynVehicleComponentInSlot);
	DEFINE_AMX_NATIVE(RepairDynamicVehicle);
	DEFINE_AMX_NATIVE(GetDynamicVehicleVelocity);
	DEFINE_AMX_NATIVE(SetDynamicVehicleVelocity);
	DEFINE_AMX_NATIVE(SetDynVehicleAngularVelocity);
	DEFINE_AMX_NATIVE(GetDynamicVehicleDamageStatus);
	DEFINE_AMX_NATIVE(UpdateDynVehicleDamageStatus);
	DEFINE_AMX_NATIVE(SetDynamicVehicleVirtualWorld);
	DEFINE_AMX_NATIVE(GetDynamicVehicleVirtualWorld);
	DEFINE_AMX_NATIVE(PutPlayerInDynamicVehicle);
	DEFINE_AMX_NATIVE(GetPlayerDynamicVehicleID);
	DEFINE_AMX_NATIVE(IsPlayerInDynamicVehicle);
	DEFINE_AMX_NATIVE(PlayerSpectateDynamicVehicle);
	DEFINE_AMX_NATIVE(IsValidDynamicVehicle);
};