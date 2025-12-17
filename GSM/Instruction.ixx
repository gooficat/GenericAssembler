export module GSM:Instruction;

import std;
import :Definitions;
import :Utility;

namespace GSM
{
	export struct IArgument
	{
		virtual std::vector<Byte> GetBytes ( ) const = 0;
	};

	export struct Argument
	{
		Argument ( const ArgumentType & type ) : type ( type )
		{ }
		const ArgumentType type;
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

	export struct OperatingArgument
	{
		OperatingArgument ( Argument * argument , const Operator operation ) : operation ( operation )
		{
			this->argument = std::shared_ptr<Argument> ( argument );
		}

		std::shared_ptr<Argument> argument;
		Operator operation;
	};

	export struct MemoryArgument : Argument
	{
		MemoryArgument ( Argument * _base , const std::vector<OperatingArgument> & applications ) :
			Argument ( ArgumentType::Memory )
		{
			//for ( auto & op : applications )
			//{
			//	this->applications.emplace_back ( )
			//}
			this->applications = applications;
			this->base = std::unique_ptr <Argument> ( _base );
		}
		std::unique_ptr<Argument> base; // the "base" argument, can be any of the other types of argument
		std::vector<OperatingArgument> applications; // the other arguments that may be applied onto the base one

		virtual std::vector<Byte> GetBytes ( ) const = 0; // this one is different because it is always dependent on the system. There is no "catch-all" solution for encoding
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