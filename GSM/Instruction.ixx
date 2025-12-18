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

	export struct Argument : IArgument
	{
		Argument ( const ArgumentType & type ) : type ( type )
		{ }
		const ArgumentType type;
		bool operator==( const ArgumentType & other )
		{
			return this->type == other;
		}
	};

	export struct RegisterArgument : Argument
	{
		RegisterArgument ( const Register value ) : Argument ( ArgumentType::Register ) , value ( value )
		{ }

		virtual std::vector<Byte> GetBytes ( ) const override
		{
			return { value };
		}

		const Register value;
	};

	export struct ImmediateArgument : Argument
	{
		ImmediateArgument ( const MaxInt value , const ByteLength byte_length ) : Argument ( ArgumentType::Immediate ) , value ( value ) , byte_length ( byte_length )
		{ }

		virtual std::vector<Byte> GetBytes ( ) const override
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

		virtual std::vector<Byte> GetBytes ( ) const override
		{
			return std::vector<Byte> ( ); // perhaps there is a way to avoid this?
		} // this one is different because it is always dependent on the system. There is no "catch-all" solution for encoding. So this is really a placeholder.
	};

	export struct InstructionProfile
	{
		const std::string mnemonic;
		const std::vector<ArgumentType> arguments;
	};

	export struct Instruction
	{
		std::string mnemonic;
		std::vector <std::unique_ptr< Argument >> arguments;

		auto operator== ( const Instruction & other )
		{
			if ( mnemonic == other.mnemonic or
				arguments.size ( ) != other.arguments.size ( ) )
				return false;

			for ( std::uint8_t i = 0; i != arguments.size ( ); ++i )
				if ( arguments.at ( i )->type != other.arguments.at ( i )->type )
					return false;

			return true;
		}

		auto AddArgument ( const std::vector<std::string> & argument_tokens )
		{
			auto argument = ParseArgument ( argument_tokens );
			arguments.emplace_back ( argument );
		}

		virtual std::vector<GSM::Byte> Encode ( ) const // this should be overriden
		{
			return std::vector<GSM::Byte> ( );
		}

		virtual std::uint8_t DeduceLength ( ) const // this one too
		{
			return 1 + std::uint8_t ( arguments.size ( ) );
		}

		Argument * ParseArgument ( const std::vector<std::string> & argument_tokens )
		{
			if ( argument_tokens.at ( 0 ).at ( 0 ) == '[' ) // beginning of a memory argument
			{
				return InterpretMemoryArgument ( argument_tokens );
			}
			else if ( std::isdigit ( argument_tokens.at ( 0 ).at ( 0 ) ) )
			{
				return InterpretImmediateArgument ( argument_tokens.at ( 0 ) );
			}
			else
			{
				return InterpretAlphaArgument ( argument_tokens.at ( 0 ) );
			}
		}

		Argument * InterpretAlphaArgument ( const std::string & token )
		{
			// TODO this will require there to be something which gives it the labels and the registers so that it may determine which it is. If it is a label it must become an immediate argument. For now, let's treat it as registers.
			return InterpretRegisterArgument ( token );
		}

		virtual Register FindRegister ( const std::string & mnemonic ) const
		{
			return Register ( 0x02 ); // TODO
		}

		RegisterArgument * InterpretRegisterArgument ( const std::string & token )
		{
			return new RegisterArgument ( FindRegister ( token ) );
		}

		MemoryArgument * InterpretMemoryArgument ( const std::vector<std::string> & tokens )
		{
			auto base = ParseArgument ( { tokens.at ( 1 ) } );

			std::vector<OperatingArgument> operations;

			for ( auto i = 2; i < tokens.size ( ) - 1; ++i )
			{
				auto op = Operator ( tokens.at ( i ).at ( 0 ) );
				auto left = ParseArgument ( { tokens.at ( ++i ) } );

				operations.emplace_back ( left , op );
			}

			auto argument = new MemoryArgument ( base , operations );

			return argument;
		}

		ImmediateArgument * InterpretImmediateArgument ( const std::string & token )
		{
			auto value = std::stoull ( token.c_str ( ) );
			return new ImmediateArgument ( value , Utility::DetermineMinimumByteLength ( value ) );
		}
	};
}