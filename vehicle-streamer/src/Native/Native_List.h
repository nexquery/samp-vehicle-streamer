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

namespace Native
{
	// Settings
	cell AMX_NATIVE_CALL vStreamer_GetTickRate(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL vStreamer_SetTickRate(AMX* amx, cell* params);

	// Vehicle
	cell AMX_NATIVE_CALL CreateDynamicVehicle(AMX* amx, cell* params);
};