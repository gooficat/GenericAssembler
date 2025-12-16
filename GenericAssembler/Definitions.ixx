export module GSM:Definitions;

import std;

namespace GSM
{
	export using Byte = std::uint8_t;

	export enum class ByteSize
	{
		BYTE = 1 ,
		WORD = 2 ,
		DWORD = 4 ,
		QWORD = 8 ,
		OWORD = 16// 
	};

	export using ByteBlock = std::vector<Byte>;
};