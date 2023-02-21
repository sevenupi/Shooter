// First shooter developed by Sevenupi

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BaseAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifieSognature, USkeletalMeshComponent*);

UCLASS()
class SHOOTER_API UBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)  override;
	FOnNotifieSognature OnNotified;
};
