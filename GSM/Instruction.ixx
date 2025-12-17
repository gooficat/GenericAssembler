export module GSM:Instruction;

import std;
import :Definitions;
import :Utility;

namespace GSM
{
	export struct Argument
	{
		Argument ( const ArgumentType & type ) : type ( type )
		{ }
		const ArgumentType type;

		virtual std::vector<Byte> GetBytes ( ) const = 0;
	};

	export struct RegisterArgument : Argument
	{
		RegisterArgument ( const Register value ) : Argument ( ArgumentType::Register ) , value ( value )
		{ }

		virtual std::vector<Byte> GetBytes ( )
		{
			return { value };
		}

		const Register value;
	};

	export struct ImmediateArgument : Argument
	{
		ImmediateArgument ( const MaxInt value , const ByteLength byte_length ) : Argument ( ArgumentType::Immediate ) , value ( value ) , byte_length ( byte_length )
		{ }

		virtual std::vector<Byte> GetBytes ( )
		{
			return Utility::ExtractBytes ( value , byte_length );
		}

		const MaxInt value;
		const ByteLength byte_length;
	};



	export struct Instruction
	{
		std::string mnemonic;
		std::vector<Argument> arguments;

		bool operator== ( const Instruction & other )
		{
			if ( mnemonic == other.mnemonic or
				arguments.size ( ) != other.arguments.size ( ) )
				return false;

			for ( std::uint8_t i = 0; i != arguments.size ( ); ++i )
				if ( arguments.at ( i ).type != other.arguments.at ( i ).type )
					return false;

			return true;
		}
	};
}