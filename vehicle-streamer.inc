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

#if defined _vehicle_streamer_included
	#endinput
#endif
#define _vehicle_streamer_included

// Geçersiz bir aracın kimlik değeri
#define INVALID_DYNAMIC_VEHICLE_ID (0)

// Araçlar hangi mesafede oluşturulacak?
#if !defined STREAMER_VEHICLE_DISTANCE
	#define STREAMER_VEHICLE_DISTANCE 200.0
#endif

/*
 ********************
   Native - Ayarlar
 ********************
*/

// Araçların hangi zaman aralığında kontrol edildiğinin süresini verir
native Vehicle_GetTickRate();

// Araçları hangi zaman aralığında güncelleyini ayarlar (ms cinsinden)
native Vehicle_SetTickRate(rate);

/*
 ***************************
   Native - Araç İşlemleri
 ***************************
*/

// Bir araç oluşturarak size değişken bir ID verir.
native CreateDynamicVehicle(modelid, Float: x, Float: y, Float: z, Float: r, color1, color2, respawn_delay, addsiren = 0, worldid = 0, interioid = 0, Float: dist = STREAMER_VEHICLE_DISTANCE);

// Oluşturulan bir aracı siler.
native DestroyDynamicVehicle(vehicleid);

// Oluşturulan araç bir oyuncu tarafından görünebiliyor mu?
native IsDynamicVehicleStreamedIn(vehicleid, forplayerid);

// Oluşturulan aracın pozisyonunu çeker.
native GetDynamicVehiclePos(vehicleid, &Float: x, &Float: y, &Float: z);

// Oluşturulan aracı belirli bir pozisyona ışınlar.
native SetDynamicVehiclePos(vehicleid, Float: x, Float: y, Float: z);

// Oluşturulan aracın bakış açısını çeker.
native GetDynamicVehicleZAngle(vehicleid, &Float: rotation);

// Bir aracın Quat açılarını alır.
native GetDynamicVehicleRotationQuat(vehicleid, &Float: w, &Float: x, &Float: y, &Float: z);

// Girilen pozisyonun araç ile arasındaki mesafeyi alır.
native Float: GetDynVehicleDistanceFromPoint(vehicleid, Float: x, Float: y, Float: z);

// Bir aracın bakış açısını değiştirir.
native SetDynamicVehicleZAngle(vehicleid, Float: rotation);

// Aracın Params değerlerini ayarlar.
native SetDynamicVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

// Aracın Params değerlerini çeker.
native GetDynamicVehicleParamsEx(vehicleid, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective);

// Bir araçta siren olup olmadığını kontrol eder
native GetDynVehicleParamsSirenState(vehicleid);

// Bir aracın kapılarını açıp kapatır.
native SetDynamicVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright);

// Bir aracın kapılarının açık veya kapalı olduğunu çeker.
native GetDynamicVehicleParamsCarDoors(vehicleid, &driver, &passenger, &backleft, &backright);

// Bir aracın cam değerlerini değiştirir.
native SetDynVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);

// Bir aracın cam değerlerini çekmenizi sağlar.
native GetDynVehicleParamsCarWindows(vehicleid, &driver, &passenger, &backleft, &backright);

// Bir aracı spawnlar.
native SetDynamicVehicleToRespawn(vehicleid);

// Bir aracın interior değerini değiştirir.
native SetDynamicVehicleInterior(vehicleid, interiorid);

// Bir aracın interior değerini çeker.
native GetDynamicVehicleInterior(vehicleid);

// Araca modifiye parçası ekler.
native AddDynamicVehicleComponent(vehicleid, componentid);

// Bir aracın modifiye parçasını kaldırır.
native RemoveDynamicVehicleComponent(vehicleid, componentid);

// Bir aracın rengini değiştirir.
native ChangeDynamicVehicleColor(vehicleid, color1, color2);

// Bir aracın paintjobunu değiştirir.
native ChangeDynamicVehiclePaintjob(vehicleid, paintjobid);

// Bir aracın can değerini değiştirir.
native SetDynamicVehicleHealth(vehicleid, Float: health);

// Bir aracın can değerini çeker.
native GetDynamicVehicleHealth(vehicleid, &Float: health);

// Bir aracın plakasını değiştirir.
native SetDynamicVehicleNumberPlate(vehicleid, const numberplate[]);

// Bir aracın modelini çeker
native GetDynamicVehicleModel(vehicleid);

// Bir aracın istenen slottan modifiye parçasını çeker.
native GetDynVehicleComponentInSlot(vehicleid, slot);

// Default Native -> Bir modifiye parçasının hangi slota ait olduğunu çeker.
//native GetVehicleComponentType(component);

// Bir aracı tamir eder
native RepairDynamicVehicle(vehicleid);

// Bir aracın Velocity değerlerini çeker.
native GetDynamicVehicleVelocity(vehicleid, &Float: x, &Float: y, &Float: z);

// Bir aracın Velocity değerini değiştirir.
native SetDynamicVehicleVelocity(vehicleid, Float: x, Float: y, Float: z);

// Bir aracın Angular Velocity değerini değiştirir.
native SetDynVehicleAngularVelocity(vehicleid, Float: x, Float: y, Float: z);

// Bir aracın hasar verilerini alır.
native GetDynamicVehicleDamageStatus(vehicleid, &panels, &doors, &lights, &tires);

// Bir aracın hasarlarını günceller.
native UpdateDynVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

// Default Native -> Bir araç modelinin verilerini alır.
//native GetVehicleModelInfo(vehiclemodel, infotype, &Float: x, &Float: y, &Float: z);

// Bir aracın Virtual World değerini değiştirir.
native SetDynamicVehicleVirtualWorld(vehicleid, worldid);

// Bir aracın Virtual World değerini alır.
native GetDynamicVehicleVirtualWorld(vehicleid);

// Aracın yolcu koltuğuna binmenizi sağlar.
native PutPlayerInDynamicVehicle(playerid, vehicleid, seatid);

// Bindiğiniz aracın hangi ID olduğunu çeker.
native GetPlayerDynamicVehicleID(playerid);

// Bir oyuncunun belirlenen araçta olup olmadığını çeker
native IsPlayerInDynamicVehicle(playerid, vehicleid);

// Bir aracı izleme moduna alırsınız.
native PlayerSpectateDynamicVehicle(playerid, vehicleid, mode = SPECTATE_MODE_NORMAL);

// Bir aracın ID değeri geçerli olup olmadığını kontrol eder.
native IsValidDynamicVehicle(vehicleid);

/*
 ***************************
        Geri Aramalar
 ***************************
*/

// Bir araca binileceğinde çağrılır.
forward OnPlayerEnterDynamicVehicle(playerid, vehicleid, ispassenger);

// Bir araçtan inileceği zaman çağrılır.
forward OnPlayerExitDynamicVehicle(playerid, vehicleid);

// Araç konumu senkronize edildiğinde çağrılır
forward OnUnoccupiedDynVehicleUpdate(vehicleid, playerid, passenger_seat, Float: new_x, Float: new_y, Float: new_z, Float: vel_x, Float: vel_y, Float: vel_z);

// Bir araç hasar değişikliğine uğradığında çağrılırç
forward OnDynVehicleDamageStatusUpdate(vehicleid, playerid);

// Bir araç patladığında çağrılır
forward OnDynamicVehicleDeath(vehicleid, killerid);

// Bir araç modifiye edildiğinde çağrılır.
forward OnDynamicVehicleMod(playerid, vehicleid, componentid);

// Bir aracın paintjobu değiştiğinde çağrılır.
forward OnDynamicVehiclePaintjob(playerid, vehicleid, paintjobid);

// Bir aracın rengi değiştiğinde çağrılır.
forward OnDynamicVehicleRespray(playerid, vehicleid, color1, color2);

// Bir aracın siren değeri değiştiğinde çağrılır.
forward OnDynVehicleSirenStateChange(playerid, vehicleid, newstate);

// Bir araç spawn edildiğinde çağrılır.
forward OnDynamicVehicleSpawn(vehicleid);

// Bir araç akışa alındığında çağrılır.
forward OnDynamicVehicleStreamIn(vehicleid, forplayerid);

// Bir araç akış alanından çıktığında çağrılır.
forward OnDynamicVehicleStreamOut(vehicleid, forplayerid);