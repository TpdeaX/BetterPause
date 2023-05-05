#ifndef PCH_H
#define PCH_H
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "Comdlg32.lib")

#include "framework.h"
#include <winsock2.h>
#include <iostream>
#include "framework.h"
#include <Windows.h>
#include <cocos2d.h>
#include <gd.h>
#include "amemory.h"
#include <fmod.h>
#include <fmod.hpp>
#include <MinHook.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <thread>
#include <shellapi.h>
#include <detours.h>
#include <cmath>
#include <cfloat>
#include <utility>
#include <type_traits>
#include <consoleapi.h>
#include "matdash.h"
#include "mindash.h"
#include "console.h"
#include <list>
#include <deque>
#include <regex>
#include <string>
#include <iomanip>
#include <commdlg.h>

#define RCAST(type, class) reinterpret_cast<type>(class)
#define SCAST(type, class) static_cast<type>(class)
#define MEMBERBYOFFSET(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)
#define MBO MEMBERBYOFFSET
#define NEWRESO(x, y) cocos2d::CCDirector::sharedDirector()->getOpenGLView()->setFrameSize(x, y)

#define public_cast(value, member) [](auto* v) { \
	class FriendClass__; \
	using T = typename std::remove_pointer<decltype(v)>::type; \
	class FriendeeClass__: public T { \
	protected: \
		friend FriendClass__; \
	}; \
	class FriendClass__ { \
	public: \
		auto& get(FriendeeClass__* v) { return v->member; } \
	} c; \
	return c.get(reinterpret_cast<FriendeeClass__*>(v)); \
}(value)

#define offset_cast(value, member) [](auto* v) { \
	class FriendClass__; \
	using T = typename std::remove_pointer<decltype(v)>::type; \
	class FriendeeClass__: public T { \
	protected: \
		friend FriendClass__; \
	}; \
	class FriendClass__ { \
	public: \
		auto get(FriendeeClass__* v) { return offsetof(FriendeeClass__, member); } \
	} c; \
	return c.get(reinterpret_cast<FriendeeClass__*>(v)); \
}(value)



#endif 
