# DataObfuscator

  ## DataObfuscator is the best project written for CPP for obfuscating data in compile time.

  ## IT IS THE BEST LIBRARY EVER CREATED!!!

  ## Usage

  * Look at example.cpp
  * Look at example.cpp
  * Look at example.cpp

  * Create Encryption and Decryption routines.
  ```
  template<typename T, (AS MUCH ARGUMENTS YOU WANT)> constexpr T __forceinline e(T c, int i) { return (c ^ K1) + K2; }
  template<typename T, (AS MUCH ARGUMENTS YOU WANT)> constexpr T __forceinline d(T c, int i) { return (c - K2) ^ K1; }
  
  // OR

  OBF_FUNC(e, K1, K2, .....) { ALGO } // You can use the var c and int i (index).

  ```

  * Obfuscating Strings.

  ```
  // This one will encrypt the char array at compile time.
  DATAOBJ_OBFSTR("char array", e, d, (K1 VALUE), (K2 VALUE))

  // Works automaticly on wide characters.
  DATAOBJ_OBFSTR(L"char array", e, d, (K1 VALUE), (K2 VALUE))
  ```


  * Obfuscating Arrays.

  ```
  // This one will encrypt the char array at compile time.
  DATAOBJ_OBFARRAY(<your type>, <new var name>, DATAOBJ_SINGLE_ARG(e1<your type, K1, ...>), DATAOBJ_SINGLE_ARG(d1<yout type, K1, ...>), { <Your array of data> });

  ```
 
  This library will help you hide strings \ data (AES encryption constants for example) from AntiViruses and Reversers!


  ### REAL THANKS FOR [andrivet](https://github.com/andrivet) and his [project](https://github.com/andrivet/ADVobfuscator)