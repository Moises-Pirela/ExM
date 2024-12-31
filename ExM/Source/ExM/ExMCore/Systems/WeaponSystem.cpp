// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#include "WeaponSystem.h"

void UWeaponSystem::Process(EntityContainer* entityContainer, float deltaTime) {

	TArray<int> _weaponEntities = entityContainer->archetypes[ARCHETYPE_WEAPON].entities;

	for(auto _weaponEntityId : _weaponEntities) {
		
	}
}

ESystemTickType UWeaponSystem::GetSystemTickType() {
	return SYSTEM_TICK;
}
