// Spyridon Zervos

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace Ability
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(BasicAttack);

	namespace Combo
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Change);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(End);
	}
}
