export module GSM:Instruction;

import std;

namespace GSM
{
	export struct Instruction
	{
		Instruction ( ) = default;

		std::string mnemonic;
	};
};