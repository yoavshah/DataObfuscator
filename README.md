# DataObfuscator

  ## DataObfuscator is a lightweight header file that grants usefull preprocessor definitions for compile time encryptions and obfuscations

  ## Usage

  * Look at example.cpp

  * Create Encryption and Decryption routines.
 
  * Obfuscate your data with fixed or compiled time generated keys.
 

  ## Capabilities

  This library can:

	* Generate random number (any type and any size) at compile time
	* Generate custom encryptions
	* Encrypt a value of any data type and decrypt it at runtime with a custom encryption and decryption routine
	* Obfuscate access to structures fields
	* Obfuscate strings, also automating the string encryption and decryption when using wide strings
	* Obfuscate arrays of any data types

 ## Images
 This is an example of obfuscating a value, as you can see in the disassembler the value 0x12345678 is being encrypted to 0xBB9D7759 at compile time, then using the key 0xA9A92121 it is being decrypted at runtime
 <img align="center" src="https://raw.githubusercontent.com/yoavshah/DataObfuscator/master/imgs/ValueObfuscator.png" />

 This is an example of obfuscating a struct access, in this example we want to access field4 of the struct, in a normal access like pst->field4, the disassembler will be [pst+4], but in this example the value 4 is being encrypted at compile time, then it is being decrypted at runtime and at last it uses [rax+rcx] to get the field
 <img align="center" src="https://raw.githubusercontent.com/yoavshah/DataObfuscator/master/imgs/StructObfuscator.png" />

 This is an example of string obfuscation of wide character string and normal string
 <img align="center" src="https://raw.githubusercontent.com/yoavshah/DataObfuscator/master/imgs/StringObfuscator.png" />


  ### Real thanks for [andrivet](https://github.com/andrivet) and his [project](https://github.com/andrivet/ADVobfuscator)