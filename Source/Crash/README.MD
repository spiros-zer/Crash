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