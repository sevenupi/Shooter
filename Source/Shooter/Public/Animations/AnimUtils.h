#pragma once

class AnimUtils
{
public:
	template<typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if(!Animation) return nullptr;
		
		const auto NotifieEvents = Animation->Notifies;
		for(auto NotifieEvent: NotifieEvents)
		{
			auto AnimNotifie =Cast<T>(NotifieEvent.Notify);
			if(AnimNotifie)
			{
				return AnimNotifie;
			}
		}
		return nullptr;
	}
};