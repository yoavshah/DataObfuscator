#include <initializer_list>
		

namespace DataObfuscator {

	// Compile time index array.
	template<int... I>
	struct Indexes { using type = Indexes<I..., sizeof...(I)>; };

	template<int N>
	struct Make_Indexes { using type = typename Make_Indexes<N - 1>::type::type; };

	template<>
	struct Make_Indexes<0> { using type = Indexes<>; };


	template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), typename Indexes> struct DataObfuscator;

	template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), int... I>
	struct DataObfuscator<T, enc_fun, dec_fun, Indexes<I...>> {

		constexpr __forceinline DataObfuscator(const std::initializer_list<T> list) : _buffer{ encrypt(*(list.begin() + I), I) ... }
		{ }

		inline const void decrypt()
		{
			for (size_t i = 0; i < sizeof...(I); i++)
				_buffer[i] = decrypt(_buffer[i], i);
		}

		volatile T _buffer[sizeof...(I)];

	private:
		// compile time encryption / decryption routines.
		constexpr T __forceinline encrypt(T c, int i) const { return enc_fun(c, i); }
		constexpr T decrypt(T c, int i) const { return dec_fun(c, i); }

	};

	constexpr unsigned int list_size(const std::initializer_list<int> list)
	{
		return list.size();
	}
}

#define SINGLE_ARG(...) __VA_ARGS__
#define OBF_GET_OVERALL_TYPE(t, enc_fun, dec_fun, ...) DataObfuscator::DataObfuscator<t, enc_fun, dec_fun, DataObfuscator::Make_Indexes<DataObfuscator::list_size(__VA_ARGS__)>::type>
#define OBF_DATA(t, var_name, enc_fun, dec_fun, ...) OBF_GET_OVERALL_TYPE(t, enc_fun, dec_fun, __VA_ARGS__) var_name(__VA_ARGS__); var_name.decrypt();
