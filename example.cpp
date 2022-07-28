#include "DataObfuscator.hpp"
#include <stdio.h>

template<typename T, int K> constexpr T __forceinline e1(T c, int i) { return c + K; }
template<typename T, int K> T __forceinline d1(T c, int i) { return c - K; }

template<typename T, unsigned int K1, unsigned int K2, unsigned int K3, unsigned int K4> constexpr T __forceinline e2(T c, int i) { return ((((c + K1) ^ K2) - K3) ^ K4); }
template<typename T, unsigned int K1, unsigned int K2, unsigned int K3, unsigned int K4> constexpr T __forceinline d2(T c, int i) { return ((((c ^ K4) + K3) ^ K2) - K1); }

DATAOBJ_FUNC(e3, unsigned int K1, unsigned int K2, unsigned int K3, unsigned int K4)
{
	return ((((c + K1) ^ K2) - K3) ^ K4);
}

DATAOBJ_FUNC(d3, unsigned int K1, unsigned int K2, unsigned int K3, unsigned int K4)
{
	return ((((c ^ K4) + K3) ^ K2) - K1);
}

int main()
{
	DATAOBJ_OBFDATA(long long, data1, DATAOBJ_SINGLE_ARG(e1<long long, 1>), DATAOBJ_SINGLE_ARG(d1<long long, 1>), {0,1,2,3});
	for (size_t i = 0; i < data1.getsize(); i++)
	{
		printf("Obfuscated var at %d : %d\n", i, data1[i]);
	}

	DATAOBJ_OBFDATA(unsigned int, data2, DATAOBJ_SINGLE_ARG(e3<unsigned int, 0xFF, 0xEEEE, 0x12, 0x333333>), DATAOBJ_SINGLE_ARG(d3<unsigned int, 0xFF, 0xEEEE, 0x12, 0x333333>), {0x11111111, 0x33333333, 0x33333333, 0x77777777});
	for (size_t i = 0; i < data2.getsize(); i++)
	{
		printf("Obfuscated var at %d : %x\n", i, data2[i]);
	}

	// OBF(str, e, d, K, W)
	printf(DATAOBJ_OBFSTR("This is an encrypted string 1\n", e1, d1, 0x01));

	printf(DATAOBJ_OBFSTR("This is an encrypted string 2\n", e2, d2, 0x11, 0x33, 0x33, 0x77));

	wprintf(DATAOBJ_OBFSTR(L"This is an encrypted string 3\n", e3, d3, 0x11, 0x33, 0x33, 0x77));


}