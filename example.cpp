#include "DataObfuscator.hpp"
#include <stdio.h>

template<typename T, int K> constexpr T __forceinline e(T c, int i) { return c + K; }
template<typename T, int K> constexpr T __forceinline d(T c, int i) { return c - K; }

int main()
{
	OBF_DATA(long long, da, SINGLE_ARG(e<long long, 1>), SINGLE_ARG(d<long long, 1>), {0,1,2,3});

	for (size_t i = 0; i < da.getsize(); i++)
	{
		printf("%d\n", da[i]);
	}
}