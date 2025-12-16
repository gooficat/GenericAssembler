export module GSM:Lexer;

import std;

namespace GSM
{
	export using Token = std::uint16_t;

	export class Lexer
	{
	public:
		std::unordered_map<std::string , Token> TokenMap;

		auto FetchTokensFromString ( const std::string & in )
		{
			std::vector<Token> out;
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

				if ( TokenMap.find ( buffer ) != TokenMap.end ( ) )
				{
					out.push_back ( TokenMap.at ( buffer ) );
				}
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