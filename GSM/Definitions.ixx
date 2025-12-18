export module GSM:Definitions;

import std;

namespace GSM
{
	export using Byte = std::uint8_t;
	export using Word = std::uint16_t;
	export using DWord = std::uint32_t;
	export using QWord = std::uint64_t;
	export using MaxInt = QWord;

	export using Token = std::uint8_t;

	export enum class ByteLength : std::uint8_t
	{
		Byte = 1 ,
		Word = 2 ,
		DWord = 4 ,
		QWord = 8 ,
	};

	export enum class ArgumentType : Token
	{
		Immediate ,
		Register ,
		Memory ,
	};

	export enum class Operator : Token
	{
		ADD = '+' ,
		SUB = '-' ,
		MUL = '*' ,
		DIV = '/' ,
		SCP = ':'
	};

	// the user should inherit these types in an enum class

	// most systems have different register types, for example x86-64 has general, stack pointer, index, segment, and floating point
	export using RegisterType = std::uint8_t;
	// for the individual registers, like rax, rbx, rcx, rsi, rdi, et cetera.
	export using Register = std::uint8_t;
}