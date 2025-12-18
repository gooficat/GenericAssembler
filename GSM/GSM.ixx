#include <cctype>
#include <iosfwd>
#include <memory>
#include <ostream>
#include <print>
#include <string>
#include <vector>
export module GSM;
export import :Instruction;
export import :Definitions;
export import :Utility;

import std;

export namespace GSM
{
	export class Assembler
	{
	public:
		Assembler ( )
		{
			std::println ( "Hello from GSM!" );
		}

		auto FeedString ( const std::string & input )
		{
			std::size_t i = 0;

			auto unprocessed_token = FetchUnprocessedToken (
				input , i
			);

			while ( i < input.size ( ) )
			{
				std::size_t i_before = i;

				std::string next_token = FetchUnprocessedToken ( input , i );
				if ( !next_token.size ( ) )
				{
					// next token is end of file. This means it must be an instruction
					instructions.push_back ( std::make_unique<Instruction> ( ) );
					instructions.back ( )->mnemonic = unprocessed_token;
					break;
				}
				else if ( next_token.at ( 0 ) == ':' )
				{
					InterpretLabel ( unprocessed_token );
				}
				else
				{
					i = i_before;
					auto instruction_contents = FetchInstructionArguments ( input , i );

					instructions.push_back ( std::make_unique<Instruction> ( ) );
					instructions.back ( )->mnemonic = unprocessed_token;
					std::cout << "Mnemonic: " << unprocessed_token << std::endl;

					for ( auto & arg : instruction_contents )
					{
						std::cout << "Arg:";
						for ( auto & tok : arg )
							std::cout << " " << tok;
						std::cout << std::endl;

						instructions.back ( )->AddArgument ( arg );
					}
				}

				unprocessed_token = FetchUnprocessedToken (
					input , i
				);
			}
		}

		virtual std::vector<std::vector<std::string>> FetchInstructionArguments ( const std::string & input , std::size_t & i )
		{
			std::vector<std::vector<std::string>> arguments;

			std::string buffered_token;

			for ( ;; )
			{
				arguments.emplace_back ( );

			keep_placing:
				buffered_token = FetchUnprocessedToken ( input , i );

				arguments.back ( ).push_back ( buffered_token );
				std::cout << "buffered: " << buffered_token << std::endl;

				// Potential solution to the problem of reading multi-token arguments
				if ( buffered_token.at ( 0 ) == '[' )
				{
					std::uint8_t indirection_counter = 1;
					do
					{
						buffered_token = FetchUnprocessedToken ( input , i );
						switch ( buffered_token.at ( 0 ) )
						{
						case '[':
							++indirection_counter;
							break;
						case ']':
							--indirection_counter;
						default:
							break;
						}
						std::cout << "buffered mem: " << buffered_token << std::endl;
						arguments.back ( ).push_back ( buffered_token );
					} while ( indirection_counter );
				}

				std::size_t i_before = i;
				buffered_token = FetchUnprocessedToken ( input , i ); // fetch the next one. it should be a comma or we are at the end of the argument list
				if ( buffered_token.size ( ) == 1 and buffered_token.at ( 0 ) != ',' )
				{
					arguments.back ( ).push_back ( buffered_token );
					goto keep_placing; // woo scary!
				}
				else if ( buffered_token.size ( ) == 0 or buffered_token.at ( 0 ) != ',' )
				{
					i = i_before;
					break;
				}
			}

			return arguments;
		}

		virtual void InterpretLabel ( const std::string & name )
		{
			std::cout << "Label: " << name << std::endl;
		}

		std::string FetchUnprocessedToken ( const std::string & input , std::size_t & i )
		{
			std::string buffer = "";
			if ( i >= input.size ( ) )
				return buffer;

			while ( std::isspace ( input.at ( i ) ) )
				if ( ++i >= input.size ( ) )
					return buffer;

			if ( std::isalnum ( input.at ( i ) ) )
				do
					buffer += input.at ( i++ );
			while ( std::isalnum ( input.at ( i ) ) );

			else
				buffer += input.at ( i++ );
			/*do
				buffer += input.at ( i++ );
		while ( not std::isalnum ( input.at ( i ) ) and not std::isspace ( input.at ( i ) ) );*/ // It's a nice piece of code, but it causes some small annoyances in assembly!

			return buffer;
		}
		std::vector <std::unique_ptr< Instruction >> instructions;
		//std::vector<std::string , MaxInt> labels;
	private:
	};
}