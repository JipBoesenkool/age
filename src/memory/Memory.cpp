//
// Created by Jip Boesenkool on 07/06/2018.
//

#include "memory/Memory.h"
#include <new>
#include <algorithm>

#include <cstdlib>
#include <stdio.h>

static void* newFunc(std::size_t size)
{
	void* p = nullptr;
	while((p = Memory::malloc(size) ) == nullptr) {
		void (*l_handler)() = std::set_new_handler(NULL);
		std::set_new_handler(l_handler);
		if (l_handler == NULL) {
			return nullptr;

		}

		l_handler();
	}
	return p;
}

static void deleteFunc(void* p)
{
	if(p == nullptr) {
		return;
	}
	Memory::free(p);
}

void* operator new(std::size_t size)
{
	void* result = newFunc(size);
	if(result == nullptr) {
		throw std::bad_alloc();
	}
	return result;
}

void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw()
{
	return newFunc(size);
}

void operator delete(void * p) throw()
{
	deleteFunc(p);
}
void* operator new[](std::size_t size)
{
	void* result = newFunc(size);
	if(result == nullptr) {
		throw std::bad_alloc();
	}
	return result;
}
void operator delete[](void *p) throw()
{
	deleteFunc(p);
}

void* Memory::malloc(uintptr amt, uint32_t alignment)
{

	alignment = std::max(amt >= 16 ? 16u : 8u, alignment);
	void* ptr = ::malloc(amt + alignment + sizeof(void*) + sizeof(uintptr));
	void* result = align((uint8_t*)ptr + sizeof(void*) + sizeof(uintptr), (uintptr)alignment);
	*((void**)((uint8_t*)result - sizeof(void*))) = ptr;
	*((uintptr*)((uint8_t*)result - sizeof(void*) - sizeof(uintptr))) = amt;
	return result;
}

void* Memory::realloc(void* ptr, uintptr amt, uint32_t alignment)
{
	alignment = std::max(amt >= 16 ? 16u : 8u, alignment);
	if(ptr == nullptr) {
		return Memory::malloc(amt, alignment);
	}

	if(amt == 0) {
		Memory::free(ptr);
		return nullptr;
	}

	void* result = malloc(amt, alignment);
	uintptr size = Memory::getAllocSize(ptr);
	Memory::memcpy(result, ptr, std::min(size, amt));
	free(ptr);

	return result;
}

void* Memory::free(void* ptr)
{
	if(ptr) {
		::free(*((void**)((uint8_t*)ptr - sizeof(void*))));
	}
	return nullptr;
}

uintptr Memory::getAllocSize(void* ptr)
{
	return *((uintptr*)((uint8_t*)ptr - sizeof(void*) - sizeof(uintptr)));
}

void Memory::bigmemswap(void* a, void* b, uintptr size)
{
	uint64_t* ptr1 = (uint64_t*)a;
	uint64_t* ptr2 = (uint64_t*)b;
	while(size > GENERIC_MEMORY_SMALL_MEMSWAP_MAX) {
		uint64_t tmp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = tmp;
		size -= 8;
		ptr1++;
		ptr2++;
	}
	smallmemswap(ptr1, ptr2, size);
}

