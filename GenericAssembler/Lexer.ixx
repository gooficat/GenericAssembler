export module GSM:Lexer;

import std;
import :Definitions;

namespace GSM
{
	export using Token = std::uint16_t;

	export class Label
	{
	public:
		std::string name;
		std::uint64_t offset;
	private:
	};

	export class Argument
	{
	public:
		virtual std::vector<Byte> GetBytes ( ) const
		{

		}
	};

	export class ImmediateArgument : public Argument
	{
	public:
		ByteBlock GetBytes ( ) const override
		{
			ByteBlock output;
			for ( std::uint8_t i = 0; i != int ( size ); ++i )
			{
				output.push_back ( ( data >> ( 8 * i ) ) & 0xFF );
			}

			return output;
		}
		ByteSize size;
	private:
		std::uint64_t data;
	};

	export class RegisterArgument : public Argument
	{
	public:
		std::vector<Byte> GetBytes ( ) const override
		{
			// TODO
		}
	private:
	};

	export class MemoryArgument : public ImmediateArgument
	{
	public:
	private:
	};


	export class Instruction
	{
	public:
		std::string mnemonic;

	private:
	};

	export class Lexer
	{
	public:
		std::unordered_map<std::string , Token> TokenMap;

		auto FetchTokensFromString ( const std::string & in )
		{
			std::vector<std::string> out;
			size_t i = 0;
			while ( i != in.size ( ) )
			{
				std::string buffer = "";
				if ( std::isspace ( in.at ( i ) ) )
				{
					++i;
					continue;
				}
				else if ( std::isalnum ( in.at ( i ) ) )
				{
					do
						buffer += in.at ( i++ );
					while ( std::isalnum ( in.at ( i ) ) );
				}
				else
				{
					do
						buffer += in.at ( i++ );
					while ( not std::isalnum ( in.at ( i ) ) and not std::isspace ( in.at ( i ) ) );
				}

				if ( TokenMap.find ( buffer ) != TokenMap.end ( ) || 1 )
				{
					out.push_back ( buffer/*TokenMap.at ( buffer )*/ );
				} // next step: turn these into "label", "instruction", etc.
			}
			return out;
		}
		auto FetchTokensFromFile ( const std::string & file_path )
		{
			return FetchTokensFromString ( DumpFile ( file_path ) );
		}
	private:
		std::string DumpFile ( const std::string & file_path )
		{
			std::fstream in_fstream ( file_path );
			std::stringstream in_sstream;
			in_sstream << in_fstream.rdbuf ( );
			in_fstream.close ( );
			return in_sstream.str ( );
		}
	};
};