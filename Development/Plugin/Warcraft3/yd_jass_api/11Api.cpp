#include <base/warcraft3/jass.h>
#include <base/warcraft3/jass/hook.h>
#include <base/warcraft3/war3_searcher.h>
#include <base/hook/fp_call.h>

namespace base {
	namespace warcraft3 {
		namespace japi {

			jass::jboolean_t __cdecl EXNetConsume(uint32_t player_handle, jass::jinteger_t coin)
			{
				(void)player_handle;
				(void)coin;
				return false;
			}

			jass::jboolean_t __cdecl EXNetCommonConsume(uint32_t player_handle, jass::jinteger_t coin)
			{
				(void)player_handle;
				(void)coin;
				return false;
			}
			
			jass::jstring_t _cdecl EXGetPlayerRealName(uint32_t player_handle)
			{
				(void)player_handle;
				return jass::create_string("Test");
			}
			
			jass::jboolean_t __cdecl EXNetUseItem(uint32_t player_handle, jass::jstring_t ItemId, jass::jinteger_t coin)
			{
				(void)player_handle;
				(void)ItemId;
				(void)coin;
				return false;
			}
			
			jass::jstring_t _cdecl EXNetGetTime()
			{
				return jass::create_string("");
			}

			jass::jboolean_t __cdecl EXNetStatRemoteData(int32_t pid, jass::jstring_t rkey, jass::jstring_t rvalue)
			{
				(void)pid;
				(void)rkey;
				(void)rvalue;
				return false;
			}

			jass::jboolean_t __cdecl EXNetSaveRemoteData(int32_t pid, jass::jstring_t rkey, jass::jstring_t rvalue)
			{
				(void)pid;
				(void)rkey;
				(void)rvalue;
				return false;
			}

			jass::jboolean_t __cdecl EXNetLoadRemoteData(int32_t pid, jass::jstring_t rkey)
			{
				(void)pid;
				(void)rkey;
				return true;
			}

			void Initialize11API()
			{
				jass::japi_add((uintptr_t)EXNetConsume, "EXNetConsume", "(Hplayer;I)B");
				jass::japi_add((uintptr_t)EXNetCommonConsume, "EXNetCommonConsume", "(Hplayer;I)B");
				jass::japi_add((uintptr_t)EXGetPlayerRealName, "EXGetPlayerRealName", "(Hplayer;)S");
				jass::japi_add((uintptr_t)EXNetUseItem, "EXNetUseItem", "(Hplayer;SI)B");
				jass::japi_add((uintptr_t)EXNetGetTime, "EXNetGetTime", "()S");
				jass::japi_add((uintptr_t)EXNetStatRemoteData, "EXNetStatRemoteData", "(ISS)B");
				jass::japi_add((uintptr_t)EXNetSaveRemoteData, "EXNetSaveRemoteData", "(ISS)B");
				jass::japi_add((uintptr_t)EXNetLoadRemoteData, "EXNetLoadRemoteData", "(IS)B");
			}
		}
	}
}
