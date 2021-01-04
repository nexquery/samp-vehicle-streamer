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

constexpr auto INVALID_REAL_ID = -1;

struct vdata
{
	int real_id;

	int modelid;
	float x;
	float y;
	float z;
	float rotation;
	int color1;
	int color2;
	int respawn;
	int addsiren;
	int world;
	int interior;
	float distance;

	int modifiye[14];

	int paintjob;

	float arac_hp;

	std::string plaka;

	int engine;
	int lights;
	int alarm;
	int doors;
	int bonnet;
	int boot;
	int objective;

	int kapi_driver;
	int kapi_passenger;
	int kapi_backleft;
	int kapi_backright;

	int cam_driver;
	int cam_passenger;
	int cam_backleft;
	int cam_backright;

	int hasar_panels;
	int hasar_doors;
	int hasar_lights;
	int hasar_tires;
};

class VehicleData
{
	public:
		static std::unordered_map<size_t, std::unique_ptr<vdata>> vList;
};