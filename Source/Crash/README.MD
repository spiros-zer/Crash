## 7. Add the Jump Input Action

Use `PawnClientRestart` reccomended place to register input mappings. Once htis is triggered it wlll be the first time the player exists on client.

> Before adding an input mapping it's best to remove it first.

Use ACharacter::SetupPlayerInputComponent to bind to input actions.

## 9. Add the Move Input Action

When binding the move input action, don't use the raw `FInputActionValue` data as moving diagonally will result in something bigger than the unit vector which means we will move faster than one direction moving.

> For the move forward vector, cross product the camera's right and forward vectors and normalizing the output will be smoother in calculations.

## 10. Create the Animation Instance

NativeInitializeAnimation gathers info about stuff that won't change.

NativeThreadSafeUpdateAnimation to perform heavy calculations.

## 11. Add the Speed Attribute to Drive Ground Locomotion

To mark a funciton as thread safe (e.g. for `UAnimInstance::NativeThreadSafeUpdateAnimation` mark it with the meta specifier `meta = (BlueprintThreadSafe)).

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
