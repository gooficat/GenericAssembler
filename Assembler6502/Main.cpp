#include <print>;
import GSM;

class Instruction : public GSM::Instruction
{

};

class Assembler : public GSM::Assembler
{
public:
	Assembler ( ) : GSM::Assembler ( )
	{
		std::println ( "Hello from My 6502 Assembler!" );

	}
private:
};

auto main ( ) -> void
{
	auto assembler = Assembler ( );
}