import GSM;

import std;


auto main ( ) -> int
{
	GSM::Test ( );

	GSM::Unit AssemblyUnit;
	GSM::Lexer Lexer;

	auto tokens = Lexer.FetchTokensFromString (
		R"(main:
	lda a, 32
)"
);


	for ( auto & token : tokens )
	{
		std::cout << "tk: " << token << std::endl;
	}

	return 0;
}