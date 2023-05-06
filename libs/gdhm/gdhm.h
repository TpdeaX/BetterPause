#ifndef GDHM_API_H
#define GDHM_API_H

#include <cinttypes>

#define GDHM_FN __stdcall

#if GDHM_API_IMPL == 1
	#define GDHM_API __declspec(dllexport)
#else
	#if defined(__clang__)
		#define GDHM_WEAK __attribute__((weak))
	#elif defined(__GNUC__) || defined(__GNUG__)
		#define GDHM_WEAK __attribute__((weak))
	#elif defined(_MSC_VER)
		#define GDHM_WEAK 
	#endif
	#pragma comment (lib, "ToastedMarshmellow.lib")
	#define GDHM_API __declspec(dllimport) GDHM_WEAK
	#define GDHM_DEPRECARED(n)
	#include <functional>
	#include <string>
	#include <vector>
#endif

namespace gdhm
{
	// generic function callback used by the API
	using callback_t = std::function<void()>;

	// helper struct, you can change this as needed
	struct control
	{
		std::string label;
		std::string info;
		bool active = false;
		uint8_t hotkey = 0;
		control(
			const std::string& __label,
			const std::string& __info = std::string(),
			const bool __active = false,
			const uint8_t __hotkey = 0,
			const callback_t& __on_init = []() {})
			: label(__label)
			, info(__info)
			, active(__active)
			, hotkey(__hotkey)
		{
			__on_init();
		}
	};

	#if GDHM_API_IMPL != 1

	GDHM_DEPRECARED( struct Vec2 { float x = 0.f, y = 0.f; }; )

	#define gdhm_new_id																		\
		[]() -> int																			\
		{																					\
			static const auto salted = std::hash<std::string>{}(__TIME__) + __COUNTER__;	\
			return static_cast<int>(salted + 0xADAF) ;										\
		}																					\
	
	namespace gui
	{
		// This will add a new window in GDHM
		GDHM_API void GDHM_FN window(
			const char* name,
			const char* mod_file_name,
			const char* tag = nullptr,
			const callback_t& callback = []() {},
			const callback_t& header = []() {},
			const callback_t& footer = []() {},
			bool* handle = nullptr,
			const bool constraint_height = false,
			const float max_height = 0.f);

		// These will add common controls
		GDHM_API void GDHM_FN label(
			const char* label);

		GDHM_API bool GDHM_FN checkbox(
			const int unique_id,
			const char* label,
			bool* value,
			uint8_t* hotkey = nullptr,
			const callback_t& on_activate = []() {},
			const char* info = "",
			const callback_t& on_hotkey_set = []() {});

		// Helper function
		static bool GDHM_FN checkbox(
			const int unique_id,
			control* __control,
			const callback_t& on_activate = []() {},
			const callback_t& on_hotkey_set = []() {})
		{
			return checkbox(
				unique_id,
				__control->label.c_str(),
				&__control->active,
				&__control->hotkey,
				on_activate,
				__control->info.c_str(),
				on_hotkey_set);
		}

		GDHM_API bool GDHM_FN button(
			const int unique_id,
			const char* label,
			uint8_t* hotkey = nullptr,
			const callback_t& on_activate = []() {},
			const char* info = "",
			const callback_t& on_hotkey_set = []() {});

		// Helper function
		static bool GDHM_FN button(
			const int unique_id,
			control* __control,
			const callback_t& on_activate = []() {},
			const callback_t& on_hotkey_set = []() {})
		{
			return button(
				unique_id,
				__control->label.c_str(),
				&__control->hotkey,
				on_activate,
				__control->info.c_str(),
				on_hotkey_set);
		}

		GDHM_API bool GDHM_FN input_text(
			const int unique_id,
			char* buffer,
			const size_t buffer_size,
			const callback_t& on_release = []() {},
			const callback_t& on_active = []() {});

		GDHM_API bool GDHM_FN input_float(
			const int unique_id,
			float* value,
			const char* label_format = "%.3f",
			const float v_speed = 1.0f,
			const float v_min = 0.0f,
			const float v_max = 0.0f,
			const callback_t& on_release = []() {},
			const callback_t& on_active = []() {});

		GDHM_API bool GDHM_FN input_int(
			const int unique_id,
			int* value,
			const char* label_format = "%.3f",
			const float v_speed = 1.0f,
			const int v_min = 0,
			const int v_max = 0,
			const callback_t& on_release = []() {},
			const callback_t& on_active = []() {});

		GDHM_API bool GDHM_FN list_box(
			const int unique_id,
			std::uint8_t* value,
			const std::vector<std::string>& values,
			const callback_t& on_release = []() {},
			const callback_t& on_active = []() {});

		GDHM_API bool GDHM_FN input_hotkey(
			const char* label,
			std::uint8_t* key);
	}

	namespace utils
	{
		GDHM_DEPRECARED // These functions are deprecated, leaving it here for now, will clean it up later...
		( 
			// This will check whether the last item has just released
			GDHM_API bool GDHM_FN last_item_just_released();

			// These will manage window position
			GDHM_API void GDHM_FN set_window_position(const float x_value, const float y_value);
			GDHM_API Vec2 GDHM_FN get_window_position();
			static void GDHM_FN set_window_position_x(const float x_value);
			static void GDHM_FN set_window_position_y(const float y_value);

			// These will manage window size
			GDHM_API GDHM_DEPRECARED Vec2 GDHM_FN get_window_size(); 
		);
	}

	// This will check whether GDHM is loaded
	static inline bool GDHM_FN is_loaded() { return GetModuleHandle(TEXT("ToastedMarshmellow.dll")); }

	// This will check the current GDHM version
	GDHM_API std::string GDHM_FN get_version();
	#endif
}

#undef GDHM_API

#endif // GDHM_API_H