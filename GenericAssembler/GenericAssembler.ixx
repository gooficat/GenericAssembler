export module GSM;
export import :Unit;
export import :Instruction;
export import :Lexer;


import std;

export namespace GSM
{
	export void Test ( )
	{
		std::cout << "Hello from GSM!" << std::endl;
	}

	export using ByteBlock = std::vector<std::uint8_t>;
};