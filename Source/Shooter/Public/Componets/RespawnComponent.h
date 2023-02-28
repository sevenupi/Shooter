// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URespawnComponent();

	void Respawn(int32 RespawnTime);

	int32 GetRespawnCountDawn()const {return RespawnCountDown;}
	bool IsRespawnInProgress() const;
protected:


private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

	void RespawnTimerUdpate();

};
