#pragma once

UENUM(BlueprintType)
enum class StatsEnum : uint8
{
    Defence      UMETA(DisplayName = "Defence"),
    MovementSpeed    UMETA(DisplayName = "Movement Speed"),
    Accuracy     UMETA(DisplayName = "Accuracy"),
    ThrowPower   UMETA(DisplayName = "Throw Power"),
    Jump    UMETA(DisplayName = "Jump Power"),
	Health       UMETA(DisplayName = "Health"),
	Shield       UMETA(DisplayName = "Shield"),
	AdditionalEffects UMETA(DisplayName = "Additional Effect")

};