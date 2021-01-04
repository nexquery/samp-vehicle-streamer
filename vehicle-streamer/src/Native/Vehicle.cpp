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
#include "../Vehicle/Func.h"
#include "../Service.h"

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
	v->lock_mode = false;
	v->modelid = modelid;
	v->x = x;
	v->y = y;
	v->z = z;

	v->cx = x;
	v->cy = y;
	v->cz = z;

	v->rotation = r;
	v->cr = r;

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

	v->cam_driver = 1;
	v->cam_passenger = 1;
	v->cam_backleft = 1;
	v->cam_backright = 1;

	v->hasar_panels = 0;
	v->hasar_doors = 0;
	v->hasar_lights = 0;
	v->hasar_tires = 0;

	VehicleData::vList.insert(std::make_pair(vehicleid, std::move(v)));

	return static_cast<cell>(vehicleid);
}

cell AMX_NATIVE_CALL Native::DestroyDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		SlotManager::Remove_ID(vehicleid);
		if (it->second->real_id != INVALID_REAL_ID)
		{
			DestroyVehicle(it->second->real_id);
		}
		VehicleData::vList.erase(it);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::IsDynamicVehicleStreamedIn(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int forplayerid  = static_cast<int>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id == INVALID_REAL_ID) {
			return 0;
		}
		return IsVehicleStreamedIn(it->second->real_id, forplayerid);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehiclePos(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id == INVALID_REAL_ID)
		{
			Service::Native_SetFloat(amx, params[2], it->second->x);
			Service::Native_SetFloat(amx, params[3], it->second->y);
			Service::Native_SetFloat(amx, params[4], it->second->z);
		}
		else
		{
			float x, y, z;
			GetVehiclePos(it->second->real_id, &x, &y, &z);
			Service::Native_SetFloat(amx, params[2], x);
			Service::Native_SetFloat(amx, params[3], y);
			Service::Native_SetFloat(amx, params[4], z);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehiclePos(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float x = static_cast<float>(amx_ctof(params[2]));
	float y = static_cast<float>(amx_ctof(params[3]));
	float z = static_cast<float>(amx_ctof(params[4]));
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->x = x;
		it->second->y = y;
		it->second->z = z;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			it->second->lock_mode = true;
			SetVehiclePos(it->second->real_id, x, y, z);
			it->second->lock_mode = false;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleZAngle(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			float r;
			GetVehicleZAngle(it->second->real_id, &r);
			Service::Native_SetFloat(amx, params[2], r);
		}
		else
		{
			Service::Native_SetFloat(amx, params[2], it->second->rotation);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleRotationQuat(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			float w, x, y, z;
			GetVehicleRotationQuat(it->second->real_id, &w, &x, &y, &z);
			Service::Native_SetFloat(amx, params[2], w);
			Service::Native_SetFloat(amx, params[3], x);
			Service::Native_SetFloat(amx, params[4], y);
			Service::Native_SetFloat(amx, params[5], z);
		}
		else
		{
			Service::Native_SetFloat(amx, params[2], 0.5f);
			Service::Native_SetFloat(amx, params[3], 0.5f);
			Service::Native_SetFloat(amx, params[4], 0.5f);
			Service::Native_SetFloat(amx, params[5], 0.5f);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynVehicleDistanceFromPoint(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float x          = static_cast<float>(amx_ctof(params[2]));
	float y          = static_cast<float>(amx_ctof(params[3]));
	float z          = static_cast<float>(amx_ctof(params[4]));
	float dist       = 999999.0;
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			dist = GetVehicleDistanceFromPoint(it->second->real_id, x, y, z);
		}
		else
		{
			dist = vFunction::Veh_Dist(x, y, z, it->second->x, it->second->y, it->second->z);
		}
	}
	return amx_ftoc(dist);
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleZAngle(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float r = static_cast<float>(amx_ctof(params[2]));
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			it->second->lock_mode = true;
			SetVehicleZAngle(it->second->real_id, r);
			it->second->lock_mode = false;
		}
		else
		{
			it->second->rotation = r;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleParamsEx(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int engine       = static_cast<int>(params[2]);
	int lights       = static_cast<int>(params[3]);
	int alarm        = static_cast<int>(params[4]);
	int doors        = static_cast<int>(params[5]);
	int bonnet       = static_cast<int>(params[6]);
	int boot         = static_cast<int>(params[7]);
	int objective    = static_cast<int>(params[8]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->engine = engine;
		it->second->lights = lights;
		it->second->alarm = alarm;
		it->second->doors = doors;
		it->second->bonnet = bonnet;
		it->second->boot = boot;
		it->second->objective = objective;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleParamsEx(it->second->real_id, engine, lights, alarm, doors, bonnet, boot, objective);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleParamsEx(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			int engine, ligths, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(it->second->real_id, &engine, &ligths, &alarm, &doors, &bonnet, &boot, &objective);
			Service::Native_SetInt(amx, params[2], engine);
			Service::Native_SetInt(amx, params[3], ligths);
			Service::Native_SetInt(amx, params[4], alarm);
			Service::Native_SetInt(amx, params[5], doors);
			Service::Native_SetInt(amx, params[6], bonnet);
			Service::Native_SetInt(amx, params[7], boot);
			Service::Native_SetInt(amx, params[8], objective);
		}
		else
		{
			Service::Native_SetInt(amx, params[2], it->second->engine);
			Service::Native_SetInt(amx, params[3], it->second->lights);
			Service::Native_SetInt(amx, params[4], it->second->alarm);
			Service::Native_SetInt(amx, params[5], it->second->doors);
			Service::Native_SetInt(amx, params[6], it->second->bonnet);
			Service::Native_SetInt(amx, params[7], it->second->boot);
			Service::Native_SetInt(amx, params[8], it->second->objective);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynVehicleParamsSirenState(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			return GetVehicleParamsSirenState(it->second->real_id);
		}
		else
		{
			return it->second->addsiren;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleParamsCarDoors(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int driver = static_cast<int>(params[2]);
	int passenger = static_cast<int>(params[3]);
	int backleft = static_cast<int>(params[4]);
	int backright = static_cast<int>(params[5]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->kapi_driver = driver;
		it->second->kapi_passenger = passenger;
		it->second->kapi_backleft = backleft;
		it->second->kapi_backright = backright;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleParamsCarDoors(it->second->real_id, driver, passenger, backleft, backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleParamsCarDoors(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			int driver, passenger, backleft, backright;
			GetVehicleParamsCarDoors(it->second->real_id, &driver, &passenger, &backleft, &backright);
			Service::Native_SetInt(amx, params[2], !!driver);
			Service::Native_SetInt(amx, params[3], !!passenger);
			Service::Native_SetInt(amx, params[4], !!backleft);
			Service::Native_SetInt(amx, params[5], !!backright);
		}
		else
		{
			Service::Native_SetInt(amx, params[2], it->second->kapi_driver);
			Service::Native_SetInt(amx, params[3], it->second->kapi_passenger);
			Service::Native_SetInt(amx, params[4], it->second->kapi_backleft);
			Service::Native_SetInt(amx, params[5], it->second->kapi_backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynVehicleParamsCarWindows(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int driver       = static_cast<int>(params[2]);
	int passenger    = static_cast<int>(params[3]);
	int backleft     = static_cast<int>(params[4]);
	int backright    = static_cast<int>(params[5]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->cam_driver = driver;
		it->second->cam_passenger = passenger;
		it->second->cam_backleft = backleft;
		it->second->cam_backright = backright;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleParamsCarWindows(it->second->real_id, driver, passenger, backleft, backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynVehicleParamsCarWindows(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			int driver, passenger, backleft, backright;
			GetVehicleParamsCarWindows(it->second->real_id, &driver, &passenger, &backleft, &backright);
			Service::Native_SetInt(amx, params[2], !!driver);
			Service::Native_SetInt(amx, params[3], !!passenger);
			Service::Native_SetInt(amx, params[4], !!backleft);
			Service::Native_SetInt(amx, params[5], !!backright);
		}
		else
		{
			Service::Native_SetInt(amx, params[2], it->second->cam_driver);
			Service::Native_SetInt(amx, params[3], it->second->cam_passenger);
			Service::Native_SetInt(amx, params[4], it->second->cam_backleft);
			Service::Native_SetInt(amx, params[5], it->second->cam_backright);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleToRespawn(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->x = it->second->cx;
		it->second->y = it->second->cy;
		it->second->z = it->second->cz;
		it->second->rotation = it->second->cr;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			it->second->lock_mode = true;
			SetVehicleToRespawn(it->second->real_id);
			it->second->lock_mode = false;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleInterior(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int interiorid   = static_cast<int>(params[2]);

	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->interior = interiorid;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			it->second->lock_mode = true;
			LinkVehicleToInterior(it->second->real_id, interiorid);
			it->second->lock_mode = false;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleInterior(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		return static_cast<int>(it->second->interior);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::AddDynamicVehicleComponent(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int componentid = static_cast<int>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		int slot = GetVehicleComponentType(componentid);
		it->second->modifiye[slot] = componentid;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			AddVehicleComponent(it->second->real_id, componentid);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::RemoveDynamicVehicleComponent(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int componentid = static_cast<int>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		int slot = GetVehicleComponentType(componentid);

		if (it->second->modifiye[slot] == componentid)
		{
			it->second->modifiye[slot] = 0;
		}

		if (it->second->real_id != INVALID_REAL_ID)
		{
			RemoveVehicleComponent(it->second->real_id, componentid);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::ChangeDynamicVehicleColor(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int color1 = static_cast<int>(params[2]);
	int color2 = static_cast<int>(params[3]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->color1 = color1;
		it->second->color2 = color2;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			ChangeVehicleColor(it->second->real_id, color1, color2);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::ChangeDynamicVehiclePaintjob(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int paintjob = static_cast<int>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->paintjob = paintjob;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			ChangeVehiclePaintjob(it->second->real_id, paintjob);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleHealth(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float hp         = static_cast<float>(amx_ctof(params[2]));
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->arac_hp = hp;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleHealth(it->second->real_id, hp);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleHealth(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			float hp;
			GetVehicleHealth(it->second->real_id, &hp);
			Service::Native_SetFloat(amx, params[2], hp);
		}
		else
		{
			Service::Native_SetFloat(amx, params[2], it->second->arac_hp);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleNumberPlate(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->plaka = Service::Get_String(amx, params[2]);
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleNumberPlate(it->second->real_id, it->second->plaka.c_str());
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleModel(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		return static_cast<int>(it->second->modelid);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynVehicleComponentInSlot(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int slot         = static_cast<int>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (slot > 0 && slot <= 13)
		{
			return static_cast<int>(it->second->modifiye[slot]);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::RepairDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		// Hp & Damage Update
		it->second->arac_hp = 1000.0f;

		it->second->hasar_doors = 0;
		it->second->hasar_lights = 0;
		it->second->hasar_panels = 0;
		it->second->hasar_tires = 0;

		if (it->second->real_id != INVALID_REAL_ID)
		{
			RepairVehicle(it->second->real_id);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleVelocity(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			float x, y, z;
			GetVehicleVelocity(it->second->real_id, &x, &y, &z);
			Service::Native_SetFloat(amx, params[2], x);
			Service::Native_SetFloat(amx, params[3], y);
			Service::Native_SetFloat(amx, params[4], z);
		}
		else
		{
			Service::Native_SetFloat(amx, params[2], 0.0f);
			Service::Native_SetFloat(amx, params[3], 0.0f);
			Service::Native_SetFloat(amx, params[4], 0.0f);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleVelocity(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float x          = static_cast<float>(amx_ctof(params[2]));
	float y          = static_cast<float>(amx_ctof(params[3]));
	float z          = static_cast<float>(amx_ctof(params[4]));
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleVelocity(it->second->real_id, x, y, z);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynVehicleAngularVelocity(AMX* amx, cell* params)
{
	CHECK_PARAMS(4);
	size_t vehicleid = static_cast<size_t>(params[1]);
	float x = static_cast<float>(amx_ctof(params[2]));
	float y = static_cast<float>(amx_ctof(params[3]));
	float z = static_cast<float>(amx_ctof(params[4]));
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleAngularVelocity(it->second->real_id, x, y, z);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleDamageStatus(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			int panels, doors, lights, tires;
			GetVehicleDamageStatus(it->second->real_id, &panels, &doors, &lights, &tires);
			Service::Native_SetInt(amx, params[2], panels);
			Service::Native_SetInt(amx, params[3], doors);
			Service::Native_SetInt(amx, params[4], lights);
			Service::Native_SetInt(amx, params[5], tires);
		}
		else
		{
			Service::Native_SetInt(amx, params[2], it->second->hasar_panels);
			Service::Native_SetInt(amx, params[3], it->second->hasar_doors);
			Service::Native_SetInt(amx, params[4], it->second->hasar_lights);
			Service::Native_SetInt(amx, params[5], it->second->hasar_tires);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::UpdateDynVehicleDamageStatus(AMX* amx, cell* params)
{
	CHECK_PARAMS(5);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int panels       = static_cast<int>(params[2]);
	int doors        = static_cast<int>(params[3]);
	int lights       = static_cast<int>(params[4]);
	int tires        = static_cast<int>(params[5]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->hasar_panels = panels;
		it->second->hasar_doors = doors;
		it->second->hasar_lights = lights;
		it->second->hasar_tires = tires;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			UpdateVehicleDamageStatus(it->second->real_id, panels, doors, lights, tires);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::SetDynamicVehicleVirtualWorld(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	size_t vehicleid = static_cast<size_t>(params[1]);
	int worldid      = static_cast<size_t>(params[2]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		it->second->world = worldid;
		if (it->second->real_id != INVALID_REAL_ID)
		{
			SetVehicleVirtualWorld(it->second->real_id, worldid);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetDynamicVehicleVirtualWorld(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		return static_cast<int>(it->second->world);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::PutPlayerInDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);

	int playerid     = static_cast<int>(params[1]);
	size_t vehicleid = static_cast<size_t>(params[2]);
	int seat         = static_cast<int>(params[3]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID)
		{
			PutPlayerInVehicle(playerid, it->second->real_id, seat);
		}
		else
		{
			it->second->lock_mode = true;
			vFunction::Vehicle_Create(it->first);
			PutPlayerInVehicle(playerid, it->second->real_id, seat);
			it->second->lock_mode = false;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::GetPlayerDynamicVehicleID(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	int playerid = static_cast<int>(params[1]);
	if (IsPlayerInAnyVehicle(playerid))
	{
		int vehicleid = GetPlayerVehicleID(playerid);
		for (std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.begin(); it != VehicleData::vList.end(); it++)
		{
			if (it->second->real_id == vehicleid)
			{
				return static_cast<int>(it->first);
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::IsPlayerInDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	int playerid     = static_cast<int>(params[1]);
	size_t vehicleid = static_cast<size_t>(params[2]);

	if (IsPlayerInAnyVehicle(playerid))
	{
		std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
		if (it != VehicleData::vList.end())
		{
			if (it->second->real_id == INVALID_REAL_ID) {
				return 0;
			}
			return IsPlayerInVehicle(playerid, it->second->real_id);
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::PlayerSpectateDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	int playerid = static_cast<int>(params[1]);
	size_t vehicleid = static_cast<size_t>(params[2]);
	int mode = static_cast<int>(params[3]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end())
	{
		if (it->second->real_id != INVALID_REAL_ID) 
		{
			PlayerSpectateVehicle(playerid, it->second->real_id, mode);
		}
		else
		{
			it->second->lock_mode = true;
			vFunction::Vehicle_Create(it->first);
			PlayerSpectateVehicle(playerid, it->second->real_id, mode);
			it->second->lock_mode = false;
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::IsValidDynamicVehicle(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	size_t vehicleid = static_cast<size_t>(params[1]);
	std::unordered_map<size_t, std::unique_ptr<vdata>>::iterator it = VehicleData::vList.find(vehicleid);
	if (it != VehicleData::vList.end()) {
		return 1;
	}
	return 0;
}