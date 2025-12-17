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

	private:
	};
}