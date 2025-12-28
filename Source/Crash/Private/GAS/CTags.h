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

namespace GameplayCue
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CameraShake);
	
	namespace Hit
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reaction);
		
		namespace Crunch
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Punch);
		}
	}
}

namespace Stats
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead);
}
