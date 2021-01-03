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
#define INVALID_VEHICLE_ID (0)

// Araçlar hangi mesafede oluşturulacak?
#if !defined STREAMER_VEHICLE_DISTANCE
	#define STREAMER_VEHICLE_DISTANCE 150.0
#endif

/*
 ********************
 * Native - Ayarlar
 ********************
 */

// Araçlar hangi zaman aralığında kontrol edildiğinin süresini verir
native vStreamer_GetTickRate();

// Araçları hangi zaman aralığında güncelleyini ayarlar (ms cinsinden)
native vStreamer_SetTickRate(rate);

/*
 ***************************
 * Native - Araç İşlemleri
 ***************************
 */

// Bir araç oluşturarak size değişken bir ID verir.
native CreateDynamicVehicle(modelid, Float: x, Float: y, Float: z, Float: r, color1, color2, respawn_delay, addsiren = 0, interioid = 0, worldid = 0, dist = STREAMER_VEHICLE_DISTANCE);