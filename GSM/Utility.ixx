export module GSM:Utility;

import std;
import :Definitions;

namespace GSM
{
	export namespace Utility
	{
		export std::vector<Byte> ExtractBytes ( const std::uint64_t value , ByteLength length )
		{
			std::vector<Byte> output;
			for ( auto i = 0; i != std::uint8_t ( length ); ++i )
			{
				output.push_back ( ( ( value >> ( i * 8 ) ) & 0xFF ) );
			}
			return output;
		}

		export ByteLength DetermineMinimumByteLength ( const std::uint64_t value )
		{
			if ( value > 0xFFFFFFFF )
				return ByteLength::QWord;
			else if ( value > 0xFFFF )
				return ByteLength::DWord;
			else if ( value > 0xFF )
				return ByteLength::Word;
			else
				return ByteLength::Byte;
		}
	}
}