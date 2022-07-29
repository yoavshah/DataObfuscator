#include <initializer_list>
#include <type_traits>

#pragma optimize("", off)
namespace DataObfuscator {

	// Compile time index array.
	template<int... I>
	struct Indexes { using type = Indexes<I..., sizeof...(I)>; };

	template<int N>
	struct Make_Indexes { using type = typename Make_Indexes<N - 1>::type::type; };

	template<>
	struct Make_Indexes<0> { using type = Indexes<>; };

	namespace ArrayObfuscator {
		template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), typename Indexes> struct ArrayObfuscator;

		template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), int... I>
		struct ArrayObfuscator<T, enc_fun, dec_fun, Indexes<I...>> {

			constexpr __forceinline ArrayObfuscator(const std::initializer_list<T> list) : buffer{ encrypt(*(list.begin() + I), I) ... }, size{ sizeof...(I) }
			{ }

			inline void decrypt()
			{
				for (size_t i = 0; i < sizeof...(I); i++)
					buffer[sizeof...(I) - i - 1] = decrypt(buffer[sizeof...(I) - i - 1], sizeof...(I) - i - 1);

			}

			T operator[](int i)
			{
				return static_cast<T>(buffer[i]);
			}

			int getsize()
			{
				return size;
			}


		private:
			// compile time encryption / decryption routines.
			constexpr T __forceinline encrypt(T c, int i) const { return enc_fun(c, i); }

			T decrypt(T c, int i) { return dec_fun(c, i); }

			volatile T buffer[sizeof...(I)];
			volatile const int size;
		};

		template<typename T> constexpr unsigned int list_size(const std::initializer_list<T> list)
		{
			return list.size();
		}
	}


	namespace StringObfuscator {
		// Represent an obfuscated string, recieves type (char / wchar_t), encryption function, decryption function and Index array.
		template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), typename Indexes>
		struct StringObfuscator;


		template<typename T, T(*enc_fun)(T, int), T(*dec_fun)(T, int), int... I>
		struct StringObfuscator<T, enc_fun, dec_fun, Indexes<I...>>
		{
			// Constructor evaluated at compile time - encrypting string.
			constexpr __forceinline StringObfuscator(const T* str) : buffer_{ encrypt(str[I], I)... }
			{ }

			// Decrypting the string at runtime.
			inline const T* decrypt()
			{
				for (size_t i = 0; i < sizeof...(I); ++i)
					buffer_[sizeof...(I) - i - 1] = decrypt(buffer_[sizeof...(I) - i - 1], sizeof...(I) - i - 1);

				buffer_[sizeof...(I)] = 0;

				return const_cast<const T*>(buffer_);
			}

		private:

			// compile time encryption / decryption routines.
			constexpr T __forceinline encrypt(T c, int i) const { return enc_fun(c, i); }
			constexpr T decrypt(T c, int i) const { return dec_fun(c, i); }

			// Buffer to store the encrypted string + terminating null byte
			volatile T buffer_[sizeof...(I) + 1];
		};
	}
}
#pragma optimize("", on)


#define DATAOBJ_SINGLE_ARG(...) __VA_ARGS__
#define DATAOBJ_OBFDATA(t, var_name, enc_fun, dec_fun, ...) DataObfuscator::ArrayObfuscator::ArrayObfuscator<t, enc_fun, dec_fun, DataObfuscator::Make_Indexes<DataObfuscator::ArrayObfuscator::list_size<t>(__VA_ARGS__)>::type> var_name(__VA_ARGS__); var_name.decrypt();

#define DATAOBJ_GET_STR_TYPE(str) std::remove_const<std::remove_pointer<std::decay<decltype(str)>::type>::type>::type
#define DATAOBJ_OBFSTR(str, enc_func, dec_func, ...) (DataObfuscator::StringObfuscator::StringObfuscator<DATAOBJ_GET_STR_TYPE(str), enc_func<DATAOBJ_GET_STR_TYPE(str), ##__VA_ARGS__>, dec_func<DATAOBJ_GET_STR_TYPE(str), ##__VA_ARGS__>, DataObfuscator::Make_Indexes<sizeof(str) - 1>::type>(str)).decrypt()

#define DATAOBJ_FUNC(funcname, ...) template<typename T, ##__VA_ARGS__> constexpr T __forceinline funcname(T c, int i)
