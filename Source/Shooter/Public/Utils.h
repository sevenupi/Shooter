#pragma once


class UUtils
{
public:
	template<typename T>
	static T* GetShooterPlayerComponent(APawn* PlayerPawn)
	{
		if(!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};