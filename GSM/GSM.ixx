export module GSM;
export import :Definitions;
export import :Instruction;
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