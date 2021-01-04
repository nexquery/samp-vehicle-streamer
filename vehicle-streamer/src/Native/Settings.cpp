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

#include "Settings.h"

cell AMX_NATIVE_CALL Native::vStreamer_GetTickRate(AMX* amx, cell* params)
{
	return static_cast<cell>(vTick_Rate);
}

cell AMX_NATIVE_CALL Native::vStreamer_SetTickRate(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	int rate = static_cast<int>(params[1]);
	if (rate < 1)
	{
		rate = 1;
	}
	vTick_Rate = rate;
	return 1;
}