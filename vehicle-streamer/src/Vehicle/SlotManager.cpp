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

#include "SlotManager.h"

size_t SlotManager::ID = 1;
std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> SlotManager::Slot;

size_t SlotManager::Free_ID()
{
	size_t vehicleid;
	if (Slot.empty())
	{
		vehicleid = ID++;
	}
	else
	{
		vehicleid = Slot.top();
		Slot.pop();
	}
	return vehicleid;
}

void SlotManager::Remove_ID(size_t id)
{
	Slot.push(id);
}

void SlotManager::Reset()
{
	ID = 1;
	Slot = std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>();
}