/*
 * -----------------------------------------------------------------------------
 * Internal Memory Utility by Adaf v.2021.1.1
 * -----------------------------------------------------------------------------
 *
 * This project is used in Hackermode, LotusInternal, and many other projects made by Adaf
 * Special thanks to Andre for helping me
 *
 * -- Adaf --
 * Github:  https://github.com/adafcaefc
 * YouTube: https://www.youtube.com/channel/UCDnlxnVCzm-rdK7b13eDkRQ
 * Website: https://adaf.xyz/adaf/
 * Discord: https://discord.com/invite/GQbFHR6jNW
 *
 * -- Andre --
 * Github:  https://github.com/andreNIH
 * YouTube: https://www.youtube.com/channel/UCma4AXxP0Yn23YZQ67mUf2w
 *
 * -----------------------------------------------------------------------------
 * Requirements
 * -----------------------------------------------------------------------------
 *
 * The recommended version of C++ is C++17
 * Recommended C++ compilers
 *
 * Visual Studio https://visualstudio.microsoft.com/
 * MinGW		 https://sourceforge.net/projects/mingw/
 * CMake		 https://cmake.org/
 *
 */

#ifndef A_MEMORY_H
#define A_MEMORY_H

#include <Windows.h>
#include <vector>
#include <string>

namespace amemory
{
	// Get the application base address
	std::uintptr_t get_base();

	// Write array of bytes to memory
	bool write_bytes(
		const std::uintptr_t			 address,
		const std::vector<std::uint8_t>& bytes);

	// Write array of bytes to memory with Virtual Protect bypass
	bool write_bytes_protect(
		const std::uintptr_t			 address,
		const std::vector<std::uint8_t>& bytes);

	// Read array of bytes
	std::vector<std::uint8_t> read_bytes(
		const std::uintptr_t address,
		const size_t		 length);

	// Read array of bytes with Virtual Protect bypass
	std::vector<std::uint8_t> read_bytes_protect(
		const std::uintptr_t address,
		const size_t		 length);

	// Load pointer address with offsets
	std::uintptr_t load_pointer(
		const std::uintptr_t			   address,
		const std::vector<std::uintptr_t>& offsets);

	// Create a manual detour
	bool place_jump(
		const std::uintptr_t address,
		const std::uintptr_t destination_address,
		const size_t		 length);

	// Write memory using typename
	template <typename T>
	void write(
		const std::uintptr_t address,
		T value)
	{
		WriteProcessMemory(
			GetCurrentProcess(),
			reinterpret_cast<LPVOID>(address),
			&value,
			sizeof(value),
			nullptr);
	}

	//Write memory using push pointer 
	bool push_write(
		const std::uintptr_t address,
		const DWORD destination_address);

	//Writes memory using bool and without need patch reset
	bool patch_toggle(
		uintptr_t addr,
		const std::vector<uint8_t>& bytes,
		bool replace);

	// Write memory using typename with Virtual Protect bypass
	template <typename T>
	bool write_protect(
		const std::uintptr_t address,
		const T value)
	{
		DWORD oldProtect, newProtect;

		if (VirtualProtect((LPVOID)address,
			sizeof(value),
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			write<T>(address, value);
			return VirtualProtect((LPVOID)address, sizeof(value), oldProtect, &newProtect);
		}

		return false;
	}

	// Read memory using typename
	template <typename T>
	T read(const std::uintptr_t address)
	{
		T buffer;
		ReadProcessMemory(
			GetCurrentProcess(),
			reinterpret_cast<LPCVOID>(address),
			&buffer,
			sizeof(T),
			nullptr);
		return buffer;
	}

	// Read memory using typename
	template <typename T>
	T read_protect(const std::uintptr_t address)
	{
		DWORD oldProtect, newProtect;

		if (VirtualProtect((LPVOID)address,
			sizeof(T),
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			auto buffer = read<T>(address);
			VirtualProtect((LPVOID)address, sizeof(T), oldProtect, &newProtect);
			return buffer;
		}

		return false;
	}

	std::string get_address_pointer(
		const std::uintptr_t base);


}



#endif
