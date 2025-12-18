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
					auto instruction_contents = FetchInstructionArguments ( input , i , next_token );

					Instruction instruction;
					instruction.mnemonic = unprocessed_token;

					for ( auto & arg : instruction_contents )
					{
						for ( auto & tok : arg )
							std::cout << tok << std::endl;

						instruction.AddArgument ( arg );
					}
				}

				unprocessed_token = FetchUnprocessedToken (
					input , i
				);
			}
		}

		virtual std::vector<std::vector<std::string>> FetchInstructionArguments ( const std::string & input , std::size_t & i , std::string buffered_token )
		{
			std::vector<std::vector<std::string>> arguments {
				{
					buffered_token
				}
			};

			for ( ;; )
			{
				if ( buffered_token == "" )
					break;
				else if ( buffered_token == "," )
					arguments.emplace_back ( );
				else
					arguments.back ( ).push_back ( buffered_token );

				buffered_token = FetchUnprocessedToken ( input , i );
			}

			return arguments;
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
				do
					buffer += input.at ( i++ );
			while ( not std::isalnum ( input.at ( i ) ) and not std::isspace ( input.at ( i ) ) );

			return buffer;
		}

	private:
	};
}