#include <warcraft3/jass/trampoline_function.h>
#include <warcraft3/event.h>
#include <warcraft3/hashtable.h>
#include <warcraft3/jass/trampoline.h>
#include <warcraft3/jass/hook.h>
#include <warcraft3/jass.h>
#include <base/util/singleton.h>
#include <base/util/do_once.h>
#include <base/hook/fp_call.h>
#include <map>

namespace warcraft3::jass {

	namespace detail {
		uintptr_t RealIsUnitInRangeXY = 0;
	
		uint32_t __cdecl FakeIsUnitInRangeXY(uint32_t unit_handle, uint32_t* x, uint32_t* y, uint32_t* dis)
		{
			if (unit_handle == 'YDWE' && x && y && dis)
			{
				return base::fast_call<uint32_t>(*x, *y, *dis);
			}
	
			return base::c_call<uint32_t>(RealIsUnitInRangeXY, unit_handle, x, y, dis);
		}

		std::map<uint64_t, trampoline> trampoline_mapping;
		uint32_t                       jump_function_id = 0;
		bool                           initialized = false;

		void trampoline_initialize()
		{
			DO_ONCE_NOTHREADSAFE()
			{
				event_game_reset([&]()
				{
					initialized = false;
					trampoline_mapping.clear();
					jump_function_id = 0;
				});
			}
			
			if (!initialized)
			{
				initialized = true;
				jump_function_id = jass::to_stringid("IsUnitInRangeXY");
				table_hook("IsUnitInRangeXY", (uintptr_t*)&detail::RealIsUnitInRangeXY, (uintptr_t)detail::FakeIsUnitInRangeXY);
			}
		}
	}

	uintptr_t trampoline_create(uintptr_t callback_, uintptr_t param1_, uintptr_t param2_)
	{
		detail::trampoline_initialize();
		const static uint8_t TEMP_REGISTER = 0xD0;

		uint64_t key = param1_ ^ param2_ ^ callback_;
		auto it = detail::trampoline_mapping.find(key);
		if (it != detail::trampoline_mapping.end())
		{
			return it->second.code();
		}

		trampoline& op = detail::trampoline_mapping[key];

		op.mov(TEMP_REGISTER, jass::OPCODE_VARIABLE_INTEGER, 'YDWE');
		op.push(TEMP_REGISTER);
		op.mov(TEMP_REGISTER, jass::OPCODE_VARIABLE_INTEGER, callback_);
		op.push(TEMP_REGISTER);
		op.mov(TEMP_REGISTER, jass::OPCODE_VARIABLE_INTEGER, param1_);
		op.push(TEMP_REGISTER);
		op.mov(TEMP_REGISTER, jass::OPCODE_VARIABLE_INTEGER, param2_);
		op.push(TEMP_REGISTER);
		op.call_native(detail::jump_function_id);
		op.set_ret(jass::RETURN_REGISTER);
		op.ret();

		return op.code();
	}

	void trampoline_clear()
	{

	}
}
