## 7. Add the Jump Input Action

Use `PawnClientRestart` recommended place to register input mappings. Once htis is triggered it wlll be the first time the player exists on client.

> Before adding an input mapping it's best to remove it first.

Use ACharacter::SetupPlayerInputComponent to bind to input actions.

## 9. Add the Move Input Action

When binding the move input action, don't use the raw `FInputActionValue` data as moving diagonally will result in something bigger than the unit vector which means we will move faster than one direction moving.

> For the move forward vector, cross product the camera's right and forward vectors and normalizing the output will be smoother in calculations.

## 10. Create the Animation Instance

NativeInitializeAnimation gathers info about stuff that won't change.

NativeThreadSafeUpdateAnimation to perform heavy calculations.

## 11. Add the Speed Attribute to Drive Ground Locomotion

To mark a function as thread safe (e.g. for `UAnimInstance::NativeThreadSafeUpdateAnimation` mark it with the meta specifier `meta = (BlueprintThreadSafe)).

Use Synchronization Groups to sync animations that don't match and/or have different paces.

> Sync markers are used for syncing groups which can be added by right-clicking in animation and selection `Add Sync Marker`.
> The anim sequence marked as `Group Leader` doesn't change or shift. Everything else follows this by stretching its time.

## 19 Add the Health and Mana Attribute to the Attribute Set

Use `AbilitySystem.DebugAttribute Attribute1 ...` editor command to show a graphic with the attributes' values.

## 20 What is a Gameplay Effect and How to Apply Them

Gameplay Effects are like configurations. They are specified from BPs and then through code are instantiated. These instances are the gameplay effect specs that's why during their creation a class of the GE is passed.

> GE_Init will initialize max HP and Mana.

## 21. Setup the Server Client Call Chain

`APlayerController::OnPossess` called on server and `AcknowledgePossession` called on client. These are used to `InitAbilityActorInfo`.

## 22. Apply the Gameplay Effects and Replicate the Attributes

> GE_FullStat uses the Attribute Based magnitude calculation to set its health and mana to the max counterparts.

## 25. Add the Gameplay Widget Blueprint

> Due to `APlayerController::AcknowledgePossession` being called on the server as well in listen server scenarios, spawning the gameplay widget there means that if left unchecked the listen server will try to create it for the other player controllers as well. To avoid this we check if  `IsLocalPlayerController()`. 

## 28. Make the Over Head Widget Display Hidden for Local Player Character

Locally controlled characters will have a Player Controller associated with them. This is usually one character (unless there is split-screen) in clients, but not in the case of listen servers. There all the player controllers and characters are present. Using `ACharacter::IsLocallyControlled` solves this.

`ACharacter::PossessedBy` is only called on server, so if the controller that possessed the character is AI perform server side initializations. 

## 30. Add the Base Ability Class and the Combo Ability

> Abilities of level 0 are not learned yet.

## 31. Add the Animation Montage Play for the Combo Ability

Ability tasks are ending and garbage collected when the ability ends by default.

`K2_` variants of the `UGameplayAbility` member functions can be used instead of their counterparts for ease.

> By wrapping the `UAbilityTask_PlayMontageAndWait` in `HasAuthorityOrPredictionKey` we allow either the server or the owner of the ability with the prediction key to execute this task to not wait server's replication. This local execution is the prediction happening, and when the replication from the server comes back, the data will be synchronized. These predictions must _only_ happen on cosmetic stuff and even then os things you can get away with.

## 34. Use an Enum to Represent the Input ID for Given Abilities

In order to match abilities to enhanced input actions, the `InputID` is used. This utilizes integers to trigger input actions. 

> One way to is to create an enum that then is converted to an int and given to the ASC's Press Input ID.

## 35. Add Input Action Binding for Abilities in the Player Character Class

In C++, aside from `UAbilitySystemComponent::PressInputID` there are also `UAbilitySystemComponent::AbilityLocalInputPressed` and `UAbilitySystemComponent::AbilityLocalInputReleased` which can trigger the ability, but also cancel it.

Also note that `LogAbilitySystem: Warning: AbilityLocalInputPressed: Default__BP_GA_Combo_Crunch_C is InstancedPerExecution. This is unreliable for Input as you may only interact with the latest spawned Instance`.

## 36. Create the Send Gameplay Event Animation Notify

Overriding a `UFUNCTION(BlueprintNativeEvent)` is possible by overriding its counterpart in the .generated file.

## 37. Handle the Combo Change Event in the Combo Ability

Animation notifies can be triggered in later moments from where they were supposed to. That is usually okay for cosmetic, but for mission-critical ones (like combos) they need to be precise at the point they are triggered. To solve this, in the Details panel for the anim notify, in Category set `Montage Tick Type` to `Branching Point`.

## 40. Create the Animation Notify to Send Sweep Location Data in a Gameplay Event

In order to send location data through `FGameplayEventData`, `FGameplayAbilityTargetData_LocationInfo` simplifies stuff. In order to set it up properly `new` has to be used when creating the pointer. This is because, when added to the `FGameplayEventData::Data` it is converted to a shared pointer. _If a smart pointer is used instead, it will crash because two smart pointers will point to the same thing, which isn't allowed by the reference manager._

As per the comment in `FGameplayAbilityTargetDataHandle::Add`: Adds a new target data to handle, it must have been created with new

## 41. Define the Target Sockets and Configure the Target Notifies

Branching points in animation montages have to be on different frames or else they won't fire.

## 44. Clamp the Attributes

Clamping the values is needed in two places. `UAttributeSet::PreAttributeChange` is called when the helper macro functions change the attribute and is made to perform an initial clamping. But, gameplay effects could have calculations happening without triggering this function (like gameplay effect Executions). `UAttributeSet::PostGameplayEffectExecute` is the place to clamp.

## 45. Add Punch VFX and Gameplay Cue

In a static gameplay cue: 

- `On Active` is triggered on duration based cues.
- `While Active` is used for operations while the cue is active.
- `Executed` is for one-off cues.

## 47. Add Camera Shake and Hit Reaction Animation

In order for the anim montages to not interact with one-another slotting them in different groups allows for playing them simultaneously.

> Especially useful for hit-react interactions.

## 48. Add Death Signal With durational Gameplay Effect and Death Tag

A death state can be achieved using gameplay effects. Destroying, respawning and re-setting everything on the pawn isn't ideal in any scenario. This also takes care of any replication.

> A duration gameplay effect that lasts as long as the respawn time.

## 51. Enable Ragdoll When Dead

> Transitioning to ragdoll physics at the end of the death animation would be snappy and show. If the transition happens mid-animation it will be much smoother and more difficult to observe.

## 54. Add the TeamID to the Player Controller and Player Character

> Adding the team id to the player controller makes it easier for retrieving locations and respawning. 
 
> We also implement this on the pawn because it needs to be aware of the team it belongs to. This could also store a reference of the player controller's, but in a multiplayer scenario it may not replicate properly.
> Setting the CCharacter::TeamId in the CPlayerController::OnPossess means that the team id on the controller needs to be set _prior_ to it being called.

Will not be using ragdoll at all. It needs extra setting up as indicated here `LogPhysics: Warning: Invalid Simulate Options: Body (BP_CPlayerCharacter1.CharacterMesh0 Crunch_Black_Site) is set to simulate physics but Collision Enabled is incompatible`.

## 56. Respawn Player Character At Their Start Spot

Utilizing the start spot, we can assign a spawn spot to a player and spawn them always there.

> StartSpot is only server side as it isn't replicated to the client.

## 58. Add AI and Configure the AI TeamID and Sight Perception

`AIController` already implements the `IGenericTeamAgentInterface`

## 221. Create the Lobby Level and Spawn the Lobby Widget

Set `AGameModeBase::bUseSeamlessTravel = true` in order to allow the player state to copy its contents to the next player state.

## 224. Create the Player Selection Structure

When using a `FUniqueNetIdRepl` it can be accessed through the player state.

## 226. Connect the Lobby Widget with The Player Slot Selection System

When a widget is generated, it is not guaranteed that its game state is updated to the correct type.

## 227. Switch To Hero Selection

`StartHeroSelectionButtonClicked` works so that when pressed by one player, every player will swap to the hero selection screen.

## 234. Issue and Update Player Character Selection on the Lobby Widget

The player state may initialize after the widget has been constructed.

## 236. Handle the Spawning and Updating Logic of the Character Display

> When `GetOwningPlayer()->SetViewTarget(CharacterDisplay);` was called in the `LobbyWidget`, it was prior to the pawn spawning and the player controller auto activating the default camera. This causes the pawn to be visible for a moment and then the controller activated the camera and the view was changed. To solve this, `ALobbyPlayerController::bAutoManageActiveCameraTarget` was set to `false`. That way the camera doesn't change when the pawn is possessed.