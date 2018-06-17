#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

//TODO: move to common file
typedef int64_t intptr;
typedef uint64_t uintptr;

void* operator new(size_t size)
{
	return malloc(size, sizeof(char));
};

void operator delete(void* mem)
{
	free(mem);
};

// Don’t forget the array version of new/delete
void* operator new[](size_t size)
{
	return malloc(size, sizeof(char));
};

void operator delete[](void* mem)
{
	free(mem);
};

#ifdef DEBUG
#define assertCheck assert
#else
#define assertCheck (void)
#endif

#ifdef COMPILER_MSVC
	#define FORCEINLINE __forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#else
	#define FORCEINLINE inline
#endif

#define GENERIC_MEMORY_SMALL_MEMSWAP_MAX 16

/**
 * Various memory functions.
 *
 * Rather than use C's memory functions directly, they are encapsulated in a
 * this struct so they can potentially be optimized for various platforms.
 *
 * Additionally, this struct contains a few memory functions that are not part
 * of C's memory library.
 *
 * I suspect this is overkill, but might be usefull for custom memory allocation
 */
struct Memory
{
	static FORCEINLINE void* memmove(void* dest, const void* src, uintptr amt)
	{
		return memmove(dest, src, amt);
	}

	static FORCEINLINE int32_t memcmp(const void* dest, const void* src, uintptr amt)
	{
		return memcmp(dest, src, amt);
	}

	template<typename T>
	static FORCEINLINE void* memset(void* destIn, T val, uintptr amt)
	{
		T* dest = (T*)destIn;
		uintptr amtT = amt/sizeof(T);
		uintptr remainder = amt % sizeof(T);
		for(uintptr i = 0; i < amtT; ++i, ++dest) {
			memcpy(dest, &val, sizeof(T));
		}
		memcpy(dest, &val, remainder);
		return destIn;
	}

	static FORCEINLINE void* memzero(void* dest, uintptr amt)
	{
		return memset(dest, 0, amt);
	}

	static FORCEINLINE void* memcpy(void* dest, const void* src, uintptr amt)
	{
		return memcpy(dest, src, amt);
	}

	static void memswap(void* a, void* b, uintptr size)
	{
		if(size <= GENERIC_MEMORY_SMALL_MEMSWAP_MAX) {
			smallmemswap(a, b, size);
		} else {
			bigmemswap(a, b, size);
		}
	}

	enum
	{
		DEFAULT_ALIGNMENT = 16,
		MIN_ALIGNMENT = 8
	};

	template<typename T>
	static FORCEINLINE constexpr T align(const T ptr, uintptr alignment)
	{
		return (T)(((intptr)ptr + alignment - 1) & ~(alignment-1));
	}

	static void* malloc(uintptr amt, uint32_t alignment=DEFAULT_ALIGNMENT);
	static void* realloc(void* ptr, uintptr amt, uint32_t alignment=DEFAULT_ALIGNMENT);
	static void* free(void* ptr);
	static uintptr getAllocSize(void* ptr);
private:
	static void bigmemswap(void* a, void* b, uintptr size);
	static void smallmemswap(void* a, void* b, uintptr size)
	{
		assertCheck(size <= GENERIC_MEMORY_SMALL_MEMSWAP_MAX);
		char temp_data[GENERIC_MEMORY_SMALL_MEMSWAP_MAX];
		void* temp = (void*)&temp_data;
		Memory::memcpy(temp, a, size);
		Memory::memcpy(a, b, size);
		Memory::memcpy(b, temp, size);
	}
};

template<>
FORCEINLINE void* Memory::memset(void* dest, uint8_t val, uintptr amt)
{
	return memset(dest, val, amt);
}

#endif //MEMORY_H
