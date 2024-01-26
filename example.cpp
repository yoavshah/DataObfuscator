#include "DataObfuscator.hpp"
#include <stdio.h>

#pragma region RandomValueExample
__declspec(noinline) void RandomExample()
{
	long value = DATAOBJ_RANDOM(long long, __COUNTER__, true);
	printf("value: %x\n", value);
}

#pragma endregion

#pragma region ValueObfuscatorExample
template<typename inputType, typename outputType, int K> constexpr outputType __forceinline enc_val(inputType c) { return c ^ K; }
template<typename inputType, typename outputType, int K> outputType __forceinline dec_val(inputType c) { return c ^ K; }

__declspec(noinline) void ValueObfuscatorExample()
{
	int value = DATAOBJ_OBFVALUE(long, long, 0x12345678, enc_val, dec_val, 0xA9A92121);
	printf("value: %x\n", value);
}

#pragma endregion

#pragma region StructObfuscatorExample
template<int K1, int K2> constexpr size_t __forceinline enc_struct_pos(size_t s) { return (s ^ K1) + K2; }
template<int K1, int K2> size_t __forceinline dec_struct_pos(size_t s) { return (s - K2) ^ K1; }

struct StructExample
{
	int field0;
	int field4;
	int field8;
};

StructExample st;

__declspec(noinline) void StructObfuscatorExample()
{
	
	StructExample* pst = &st;
	st.field0 = 10;
	st.field4 = 11;
	st.field8 = 12;

	int field4_val_obf = DATAOBJ_STRUCT(StructExample*,
		pst,
		field4,
		enc_struct_pos,
		dec_struct_pos, 
		0x54,
		0x23);

	printf("field4_obj: %d\n", field4_val_obf);
}
#pragma endregion

#pragma region StringObfuscator

template<typename T, int K1, int K2> constexpr T __forceinline enc_string(T c, int i) { return (c + K1 + i) ^ K2; }
template<typename T, int K1, int K2> T __forceinline dec_string(T c, int i) { return (c ^ K2) - K1 - i; }

template<typename T, unsigned int K1, unsigned int K2, unsigned long K3, unsigned int K4> constexpr T __forceinline enc_string2(T c, int i)
{
	return ((((c + K1) ^ K2) - K3) ^ K4);
}

template<typename T, unsigned int K1, unsigned int K2, unsigned long K3, unsigned int K4> T __forceinline dec_string2(T c, int i)
{
	return ((((c ^ K4) + K3) ^ K2) - K1);
}


__declspec(noinline) void StringObfuscatorExample()
{
	printf(DATAOBJ_OBFSTR("This is an encrypted string\n", enc_string, dec_string, 0x13, 0x37));

	wprintf(DATAOBJ_OBFSTR(L"This is an wide encrypted string\n", enc_string2, dec_string2, 0x11, 0x33, 0x33, 0x77));
}
#pragma endregion

#pragma region ArrayObfuscator
template<typename T, int K> constexpr T __forceinline enc_array(T c, int i) { return c + K; }
template<typename T, int K> T __forceinline dec_array(T c, int i) { return c - K; }

__declspec(noinline) void ArrayObfuscatorExample()
{
	DATAOBJ_OBFARRAY(char, data, DATAOBJ_SINGLE_ARG(enc_array<char, 0xDD>), DATAOBJ_SINGLE_ARG(dec_array<char, 0xDD>), { 'A', 'r', 'r', 'a', 'y', '\n' });
	
	printf("%s\n", data);
}
#pragma endregion


int main()
{
	RandomExample();

	ValueObfuscatorExample();

	StructObfuscatorExample();

	StringObfuscatorExample();

	ArrayObfuscatorExample();

}

