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

	export ByteBlock ExtractBytes ( const std::uint64_t data , const ByteSize & size )
	{
		ByteBlock output;
		for ( std::uint8_t i = 0; i != int ( size ); ++i )
		{
			output.push_back ( ( data >> ( 8 * i ) ) & 0xFF );
		}

		return output;
	}
};