#include "DataObfuscator.hpp"
#include <stdio.h>


template<typename T, int K> constexpr T __forceinline e1(T c, int i) { return c + K; }
template<typename T, int K> T __forceinline d1(T c, int i) { return c - K; }

template<typename T, unsigned int K1, unsigned long K2, unsigned int K3, unsigned int K4> constexpr T __forceinline e2(T c, int i) { return (((((c + K1) ^ K2) - K3) ^ K4) - i); }
template<typename T, unsigned int K1, unsigned long K2, unsigned int K3, unsigned int K4> constexpr T __forceinline d2(T c, int i) { return (((((c + i) ^ K4) + K3) ^ K2) - K1); }

DATAOBJ_FUNC(e3, unsigned int K1, unsigned int K2, unsigned long K3, unsigned int K4)
{
	return ((((c + K1) ^ K2) - K3) ^ K4);
}

DATAOBJ_FUNC(d3, unsigned int K1, unsigned int K2, unsigned long K3, unsigned int K4)
{
	return ((((c ^ K4) + K3) ^ K2) - K1);
}

char* data_global;
unsigned int size;

void create_global()
{
	DATAOBJ_OBFARRAY(char, data_g, DATAOBJ_SINGLE_ARG(e1<char, 0xDD>), DATAOBJ_SINGLE_ARG(d1<char, 0xDD>), { 'G', 'L', 'O', 'B', 'A', 'L', '\n' });

	data_global = data_g.copy();
	size = data_g.getsize();

}

template<typename T, typename F> constexpr F __forceinline ee(T c) { return c + 5; }
template<typename T, typename F> constexpr T __forceinline dd(F c) { return c - 5; }




int main()
{


	printf("%llx\n", DATAOBJ_RANDOM(long long, __COUNTER__, true));
	printf("%llx\n", DATAOBJ_RANDOM(long long, __COUNTER__, true));


	for (size_t i = 0; i < 3; i++)
	{
		auto x = DATAOBJ_OBFVALUE(int, long, 100, ee, dd);
		printf("%d\n", x);
	}
	return 0;

	/*
		Encrypting at compile time using e3 and decrypte at run-time using d3 with keys K1=0xFF, K2=0xEEEE, K3=0x12, K4=0x333333
	*/
	DATAOBJ_OBFARRAY(unsigned long long, data1, DATAOBJ_SINGLE_ARG(e3<unsigned long long, 0xFF, 0xEEEE, 0x12, 0x333333>), DATAOBJ_SINGLE_ARG(d3<unsigned long long, 0xFF, 0xEEEE, 0x12, 0x333333>), {0x1111111111111111, 0x3333333333333333, 0x3333333333333333, 0x7777777777777777});
	for (size_t i = 0; i < data1.getsize(); i++)
	{
		printf("(data1): Obfuscated var at %d : %llx\n", i, data1[i]);
	}

	printf("\n");
	
	unsigned long long* data1_pointer = data1;
	for (size_t i = 0; i < data1.getsize(); i++)
	{
		printf("(data1_pointer): Obfuscated var at %d : %llx\n", i, data1_pointer[i]);
	}

	printf("\n");

	DATAOBJ_OBFARRAY(char, data2, DATAOBJ_SINGLE_ARG(e1<char, 0xFF>), DATAOBJ_SINGLE_ARG(d1<char, 0xFF>), { 'A', 'B', 'C', 'D', '\n'});
	for (size_t i = 0; i < data2.getsize(); i++)
	{
		printf("(data2) Obfuscated var at %d : %c\n", i, data2[i]);
	}

	printf("\n");

	create_global();
	for (size_t i = 0; i < size; i++)
	{
		printf("(data_global) Obfuscated var at %d : %c\n", i, data_global[i]);
	}

	// OBF(str, e, d, K, W)
	printf(DATAOBJ_OBFSTR("This is an encrypted string 1\n", e1, d1, 0x01));

	printf(DATAOBJ_OBFSTR("This is an encrypted string 2\n", e2, d2, 0x11, 0x33, 0x33, 0x77));

	wprintf(DATAOBJ_OBFSTR(L"This is an encrypted string 3\n", e3, d3, 0x11, 0x33, 0x33, 0x77));
	
}

