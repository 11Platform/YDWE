#include <windows.h>


namespace base { namespace warcraft3 { namespace japi {
	void InitializeUnitState();
	void InitializeAbilityState();
	void InitializeItemState();
	void InitializeEventDamageData();
	void InitializeDisplayChat();
	void InitializeDisableButtonBlp();
	void InitializeEffect();
	void Initialize11API();
	void initialize()
	{
		InitializeUnitState();
		InitializeAbilityState();
		InitializeItemState();
		InitializeEventDamageData();
		InitializeDisplayChat();
		InitializeDisableButtonBlp();
		InitializeEffect();				
#if (_MSC_VER > 1800)  // YDWE  π”√VS2017
			Initialize11API();
#endif
	}
}}}
