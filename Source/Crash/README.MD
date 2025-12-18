## 7. Add the Jump Input Action

Use `PawnClientRestart` reccomended place to register input mappings. Once htis is triggered it wlll be the first time the player exists on client.

> Before adding an input mapping it's best to remove it first.

Use ACharacter::SetupPlayerInputComponent to bind to input actions.

## 9. Add the Move Input Action

When binding the move input action, don't use the raw `FInputActionValue` data as moving diagonally will result in something bigger than the unit vector which means we will move faster than one direction moving.

> For the move forward vector, cross product the camera's right and forward vectors and normalizing the output will be smoother in calculations.

