// Spyridon Zervos


#include "CTags.h"

namespace Ability
{
	UE_DEFINE_GAMEPLAY_TAG(BasicAttack, "Ability.BasicAttack");

	namespace Combo
	{
		UE_DEFINE_GAMEPLAY_TAG(Change, "Ability.Combo.Change");
		
		UE_DEFINE_GAMEPLAY_TAG(Damage, "Ability.Combo.Damage");
		
		UE_DEFINE_GAMEPLAY_TAG(End, "Ability.Combo.End");
	}
}

namespace GameplayCue
{
	UE_DEFINE_GAMEPLAY_TAG(CameraShake, "GameplayCue.CameraShake");
	
	namespace Hit
	{
		UE_DEFINE_GAMEPLAY_TAG(Reaction, "GameplayCue.Hit.Reaction");
		
		namespace Crunch
		{
			UE_DEFINE_GAMEPLAY_TAG(Punch, "GameplayCue.Hit.Crunch.Punch");
		}
	}
}
