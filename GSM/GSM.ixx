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
				std::cout << unprocessed_token << std::endl;

				std::string next_token = FetchUnprocessedToken ( input , i );
				if ( !next_token.size ( ) )
				{
					// next token is end of file. This means it must be an instruction
					InterpretInstruction ( { unprocessed_token } );
					break;
				}
				else if ( next_token.at ( 0 ) == ':' )
				{
					InterpretLabel ( unprocessed_token );
				}
				else
				{
					auto instruction_contents = FetchInstructionArguments ( input , i );
				}

				unprocessed_token = FetchUnprocessedToken (
					input , i
				);
			}
		}

		virtual std::vector<std::unique_ptr<Argument>> FetchInstructionArguments ( const std::string & input , std::size_t & i )
		{
			std::vector<std::unique_ptr<Argument>> arguments;
			bool exit = false;
			while ( !exit )
			{
				auto token_str = FetchUnprocessedToken ( input , i );
				if ( token_str.at ( i ) == '' )
			}
		}

		virtual void InterpretLabel ( const std::string & name )
		{
			std::cout << "This is a label marked as " << name << "!" << std::endl;
		}

		virtual void InterpretInstruction ( const std::vector<std::string> & input )
		{
			//Instruction * out;
			std::cout << "This is an instruction with mnemonic " << input.at ( 0 ) << "!" << std::endl;
		}

		std::string FetchUnprocessedToken ( const std::string & input , std::size_t & i )
		{
			while ( std::isspace ( input.at ( i ) ) )
				if ( ++i >= input.size ( ) )
					return "";

			std::string buffer = "";

			if ( std::isalnum ( input.at ( i ) ) )
				do
					buffer += input.at ( i++ );
			while ( std::isalnum ( input.at ( i ) ) );

			else
				do
					buffer += input.at ( i++ );
			while ( not std::isalnum ( input.at ( i ) ) and not std::isspace ( input.at ( i ) ) );

			return buffer;
		}

	private:
	};
}