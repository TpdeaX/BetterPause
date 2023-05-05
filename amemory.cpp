/*
 * -----------------------------------------------------------------------------
 * Internal Memory Utility by Adafcaefc v.2022.1.2
 * -----------------------------------------------------------------------------
 *
 * This project is used in Hackermode, LotusInternal, and many other projects made by Adafcaefc
 * Special thanks to Andre for helping me
 * Darkqtp Is Here :v
 *
 */
#include "pch.h"
#include "amemory.h"
#include <climits>

namespace amemory
{
	bool write_bytes_protect(
		const std::uintptr_t address,
		const std::vector<std::uint8_t>& bytes)
	{
		DWORD oldProtect, newProtect;

		if (VirtualProtect(
			(LPVOID)address, bytes.size(),
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			if (write_bytes(address, bytes))
			{
				return VirtualProtect((LPVOID)address, bytes.size(), oldProtect, &newProtect);
			}
		}

		return false;
	}

	std::uintptr_t load_pointer(
		const std::uintptr_t base,
		const std::vector<std::uintptr_t>& offsets)
	{
		DWORD oldProtect, newProtect;
		std::uint32_t address = base;

		for (size_t i = 0; i < offsets.size(); ++i)
		{
			if (VirtualProtect(
				reinterpret_cast<LPVOID>(address),
				sizeof(address),
				PAGE_EXECUTE_READWRITE,
				&oldProtect))
			{
				VirtualProtect(
					reinterpret_cast<LPVOID>(address),
					sizeof(address),
					oldProtect,
					&newProtect);
			}
			else
			{
				return NULL;
			}
			address = read<std::uint32_t>(address);
			address += offsets.at(i);
		}

		return address;
	}

	bool write_bytes(
		const std::uintptr_t address,
		const std::vector<std::uint8_t>& bytes)
	{
		return WriteProcessMemory(
			GetCurrentProcess(),
			reinterpret_cast<LPVOID>(address),
			bytes.data(),
			bytes.size(),
			nullptr);
	}

	bool place_jump(
		const std::uintptr_t address,
		const std::uintptr_t destination_address,
		const size_t length)
	{
		DWORD oldProtect, newProtect;
		const std::uint32_t relativeAddress = destination_address - address - 5;

		if (!VirtualProtect(
			reinterpret_cast<LPVOID>(address),
			length,
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			return false;
		}

		write<std::uint8_t>(address, 0xE9);
		write<std::uint32_t>(address + 1, relativeAddress);

		for (size_t i = 5; i < length; ++i)
		{
			write<std::uint8_t>(address + i, 0x90);
		}

		return VirtualProtect(
			reinterpret_cast<LPVOID>(address),
			length,
			oldProtect,
			&newProtect);
	}

	std::uintptr_t get_base()
	{
		return reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));
	}

	std::vector<std::uint8_t> read_bytes(
		const std::uintptr_t address,
		const size_t length)
	{
		std::vector<std::uint8_t> buffer;
		for (size_t i = 0; i < length; ++i)
		{
			buffer.push_back(
				read<std::uint8_t>(
					address + i));
		}
		return buffer;
	}

	std::vector<std::uint8_t> read_bytes_protect(
		const std::uintptr_t address,
		const size_t length)
	{
		std::vector<std::uint8_t> empty_vector;

		DWORD oldProtect, newProtect;
		if (!VirtualProtect(
			reinterpret_cast<LPVOID>(address),
			length,
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			return empty_vector;
		}

		auto buffer = read_bytes(address, length);

		VirtualProtect(
			reinterpret_cast<LPVOID>(address),
			length,
			oldProtect,
			&newProtect);

		return buffer;
	}

	bool push_write(
		const std::uintptr_t address,
		const DWORD destination_address)
	{
		DWORD oldProtect, newProtect;

		if (VirtualProtect(
			(LPVOID)address, 4,
			PAGE_EXECUTE_READWRITE,
			&oldProtect))
		{
			if (WriteProcessMemory(
				GetCurrentProcess(),
				reinterpret_cast<LPVOID>(address),
				&destination_address,
				4,
				nullptr))
			{
				return VirtualProtect((LPVOID)address, 4, oldProtect, &newProtect);
			}
		}

		return false;
	}

	bool patch_toggle(
		uintptr_t addr,
		const std::vector<uint8_t>& bytes,
		bool replace)
	{

		static std::unordered_map<uintptr_t, uint8_t*> values;
		if (values.find(addr) == values.end()) {
			auto data = new uint8_t[bytes.size()];
			memcpy(data, reinterpret_cast<void*>(addr), bytes.size());
			values[addr] = data;
		}
		DWORD old_prot;
		VirtualProtect(reinterpret_cast<void*>(addr), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot);
		memcpy(reinterpret_cast<void*>(addr), replace ? bytes.data() : values[addr], bytes.size());
		VirtualProtect(reinterpret_cast<void*>(addr), bytes.size(), old_prot, &old_prot);

		return false;
	}


	std::string get_address_pointer(
		const std::uintptr_t base)
	{
		std::string tr;
		auto address = read_bytes_protect(base, 4);
		reverse(address.begin(), address.end());
		std::ostringstream convert;
		for (int a = 0; a < address.size(); a++) {
			convert << std::uppercase << std::hex << (int)address[a];
		}

		return convert.str();
	}

}