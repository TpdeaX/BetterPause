#pragma once
#include "pch.h"

namespace matdash {
	enum CallConv {
		Optcall,
		Membercall,
		Thiscall,
		Cdecl,
		Stdcall
	};

	namespace detail {
		template <class T, CallConv>
		struct ValueWrapper {
			T value;
			template <class... Args>
			ValueWrapper(Args&&... v) : value(std::forward<Args>(v)...) {}
			ValueWrapper(T v) : value(v) {}
			operator T() { return value; }
		};

		template <CallConv cc>
		struct ValueWrapper<void, cc> {};
	}

	namespace cc {
		template <class T>
		using optcall = detail::ValueWrapper<T, Optcall>;

		template <class T>
		using membercall = detail::ValueWrapper<T, Membercall>;

		template <class T>
		using thiscall = detail::ValueWrapper<T, Thiscall>;

		// cant name it cdecl :(
		template <class T>
		using c_decl = detail::ValueWrapper<T, Cdecl>;

		template <class T>
		using stdcall = detail::ValueWrapper<T, Stdcall>;
	}

	namespace detail {
		template <class F>
		struct function_ret;

		template <class R, class... Args>
		struct function_ret<R(Args...)> {
			using type = R;
		};

		template <class T, CallConv cc>
		struct extract_cc_or {
			static constexpr auto value = cc;
			using type = T;
		};

		template <class T, CallConv c, CallConv idk>
		struct extract_cc_or<ValueWrapper<T, c>, idk> {
			static constexpr auto value = c;
			using type = T;
		};

		template <class F>
		struct wrap_member_fn {
			template <auto>
			static void wrap() {}
		};

		template <class R, class T, class... Args>
		struct wrap_member_fn<R(T::*)(Args...)> {
			template <auto func>
			static R wrap(T* self, Args... args) {
				return (self->*func)(args...);
			}
		};

		template <class F>
		struct clean_fn_type { using type = F; };

		template <class R, class... Args>
		struct clean_fn_type<R(*)(Args...)> {
			using type = R(Args...);
		};

		template <class R, class T, class... Args>
		struct clean_fn_type<R(T::*)(Args...)> {
			using type = R(T*, Args...);
		};

		template <class F>
		struct remove_value_wrapper;

		template <class R, class... Args>
		struct remove_value_wrapper<R(Args...)> {
			using ret = typename extract_cc_or<R, CallConv::Cdecl>::type;
			using type = ret(Args...);
		};

		template <bool>
		struct ternary {
			template <auto a, auto b>
			static constexpr auto value = a;
		};

		template <>
		struct ternary<false> {
			template <auto a, auto b>
			static constexpr auto value = b;
		};

		namespace wrappers {
			template <auto>
			static void* tramp = nullptr;

			template <class F>
			struct thiscall;

			template <class R, class... Args>
			struct thiscall<R(Args...)> {
				template <auto func>
				static R __thiscall wrap(Args... args) {
					if constexpr (std::is_same_v<R, void>)
						func(args...);
					else
						return func(args...);
				}
				template <auto func>
				static R invoke(Args... args) {
					return reinterpret_cast<R(__thiscall*)(Args...)>(tramp<func>)(args...);
				}
			};

			template <class F>
			struct c_decl;

			template <class R, class... Args>
			struct c_decl<R(Args...)> {
				template <auto func>
				static R __cdecl wrap(Args... args) {
					if constexpr (std::is_same_v<R, void>)
						func(args...);
					else
						return func(args...);
				}
				template <auto func>
				static R invoke(Args... args) {
					return reinterpret_cast<R(__cdecl*)(Args...)>(tramp<func>)(args...);
				}
			};

			template <class F>
			struct stdcall;

			template <class R, class... Args>
			struct stdcall<R(Args...)> {
				template <auto func>
				static R __stdcall wrap(Args... args) {
					if constexpr (std::is_same_v<R, void>)
						func(args...);
					else
						return func(args...);
				}
				template <auto func>
				static R invoke(Args... args) {
					return reinterpret_cast<R(__stdcall*)(Args...)>(tramp<func>)(args...);
				}
			};

			template <class F>
			struct membercall;

			template <class F>
			struct optcall;


			template <class R, class ...Args>
			struct optcall<R(Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(Args... args) {
					return func(args...);
				}
				template <auto func>
				static decltype(auto) invoke(Args... args) {

					return reinterpret_cast<R(__fastcall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class A, class B, class C, class ...Args>
			struct optcall<R(A, B, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, B a1, C a2, Args... args) {
					float a3;
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, C a2, float a3, Args... args) {
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(A, B, C, Args...)>(tramp<func>)(a0, a1, a2, args...);
				}
			};


			template <class R, class A, class B, class ...Args>
			struct optcall<R(A, B, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, B a1, Args... args) {
					float a2;
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, float a2, Args... args) {
					__asm movss xmm2, a2
					return reinterpret_cast<R(__fastcall*)(A, B, Args...)>(tramp<func>)(a0, a1, args...);
				}
			};


			template <class R, class A, class B, class ...Args>
			struct optcall<R(A, B, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, B a1, Args... args) {
					float a2, a3;
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, float a2, float a3, Args... args) {
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(A, B, Args...)>(tramp<func>)(a0, a1, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct optcall<R(A, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, Args... args) {
					float a1;
					__asm movss a1, xmm1
					return func(a0, a1, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, Args... args) {
					__asm movss xmm1, a1
					return reinterpret_cast<R(__fastcall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};


			template <class R, class A, class C, class ...Args>
			struct optcall<R(A, float, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, C a2, Args... args) {
					float a1, a3;
					__asm movss a1, xmm1
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, C a2, float a3, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(A, C, Args...)>(tramp<func>)(a0, a2, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct optcall<R(A, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, Args... args) {
					float a1, a2;
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, float a2, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					return reinterpret_cast<R(__fastcall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct optcall<R(A, float, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(A a0, Args... args) {
					float a1, a2, a3;
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, float a2, float a3, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};


			template <class R, class ...Args>
			struct optcall<R(float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(Args... args) {
					float a0;
					__asm movss a0, xmm0
					return func(a0, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, Args... args) {
					__asm movss xmm0, a0
					return reinterpret_cast<R(__fastcall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class B, class C, class ...Args>
			struct optcall<R(float, B, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(B a1, C a2, Args... args) {
					float a0, a3;
					__asm movss a0, xmm0
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, B a1, C a2, float a3, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(B, C, Args...)>(tramp<func>)(a1, a2, args...);
				}
			};


			template <class R, class B, class ...Args>
			struct optcall<R(float, B, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(B a1, Args... args) {
					float a0, a2;
					__asm movss a0, xmm0
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, B a1, float a2, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm2, a2
					return reinterpret_cast<R(__fastcall*)(B, Args...)>(tramp<func>)(a1, args...);
				}
			};


			template <class R, class B, class ...Args>
			struct optcall<R(float, B, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(B a1, Args... args) {
					float a0, a2, a3;
					__asm movss a0, xmm0
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, B a1, float a2, float a3, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(B, Args...)>(tramp<func>)(a1, args...);
				}
			};


			template <class R, class ...Args>
			struct optcall<R(float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(Args... args) {
					float a0, a1;
					__asm movss a0, xmm0
					__asm movss a1, xmm1
					return func(a0, a1, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, float a1, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm1, a1
					return reinterpret_cast<R(__fastcall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class C, class ...Args>
			struct optcall<R(float, float, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(C a2, Args... args) {
					float a0, a1, a3;
					__asm movss a0, xmm0
					__asm movss a1, xmm1
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, float a1, C a2, float a3, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm1, a1
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(C, Args...)>(tramp<func>)(a2, args...);
				}
			};


			template <class R, class ...Args>
			struct optcall<R(float, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(Args... args) {
					float a0, a1, a2;
					__asm movss a0, xmm0
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, float a1, float a2, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					return reinterpret_cast<R(__fastcall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class ...Args>
			struct optcall<R(float, float, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __fastcall wrap(Args... args) {
					float a0, a1, a2, a3;
					__asm movss a0, xmm0
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(float a0, float a1, float a2, float a3, Args... args) {
					__asm movss xmm0, a0
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__fastcall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class ...Args>
			struct membercall<R(Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(Args... args) {
					return func(args...);
				}
				template <auto func>
				static decltype(auto) invoke(Args... args) {

					return reinterpret_cast<R(__thiscall*)(Args...)>(tramp<func>)(args...);
				}
			};


			template <class R, class A, class B, class C, class ...Args>
			struct membercall<R(A, B, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, B a1, C a2, Args... args) {
					float a3;
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, C a2, float a3, Args... args) {
					__asm movss xmm3, a3
					return reinterpret_cast<R(__thiscall*)(A, B, C, Args...)>(tramp<func>)(a0, a1, a2, args...);
				}
			};


			template <class R, class A, class B, class ...Args>
			struct membercall<R(A, B, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, B a1, Args... args) {
					float a2;
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, float a2, Args... args) {
					__asm movss xmm2, a2
					return reinterpret_cast<R(__thiscall*)(A, B, Args...)>(tramp<func>)(a0, a1, args...);
				}
			};


			template <class R, class A, class B, class ...Args>
			struct membercall<R(A, B, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, B a1, Args... args) {
					float a2, a3;
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, B a1, float a2, float a3, Args... args) {
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__thiscall*)(A, B, Args...)>(tramp<func>)(a0, a1, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct membercall<R(A, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, Args... args) {
					float a1;
					__asm movss a1, xmm1
					return func(a0, a1, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, Args... args) {
					__asm movss xmm1, a1
					return reinterpret_cast<R(__thiscall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};


			template <class R, class A, class C, class ...Args>
			struct membercall<R(A, float, C, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, C a2, Args... args) {
					float a1, a3;
					__asm movss a1, xmm1
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, C a2, float a3, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm3, a3
					return reinterpret_cast<R(__thiscall*)(A, C, Args...)>(tramp<func>)(a0, a2, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct membercall<R(A, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, Args... args) {
					float a1, a2;
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					return func(a0, a1, a2, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, float a2, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					return reinterpret_cast<R(__thiscall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};


			template <class R, class A, class ...Args>
			struct membercall<R(A, float, float, float, Args...)> {
				template <auto func>
				static decltype(auto) __thiscall wrap(A a0, Args... args) {
					float a1, a2, a3;
					__asm movss a1, xmm1
					__asm movss a2, xmm2
					__asm movss a3, xmm3
					return func(a0, a1, a2, a3, args...);
				}
				template <auto func>
				static decltype(auto) invoke(A a0, float a1, float a2, float a3, Args... args) {
					__asm movss xmm1, a1
					__asm movss xmm2, a2
					__asm movss xmm3, a3
					return reinterpret_cast<R(__thiscall*)(A, Args...)>(tramp<func>)(a0, args...);
				}
			};

		}

		template <CallConv conv>
		struct wrapper_for_cc {
			static_assert(conv == conv, "unknown cc");
		};

		template <>
		struct wrapper_for_cc<CallConv::Thiscall> {
			template <class T>
			using type = wrappers::thiscall<T>;
		};

		template <>
		struct wrapper_for_cc<CallConv::Cdecl> {
			template <class T>
			using type = wrappers::c_decl<T>;
		};

		template <>
		struct wrapper_for_cc<CallConv::Stdcall> {
			template <class T>
			using type = wrappers::stdcall<T>;
		};

		template <>
		struct wrapper_for_cc<CallConv::Membercall> {
			template <class T>
			using type = wrappers::membercall<T>;
		};

		template <>
		struct wrapper_for_cc<CallConv::Optcall> {
			template <class T>
			using type = wrappers::optcall<T>;
		};
	}
}