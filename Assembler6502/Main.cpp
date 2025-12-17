#include <print>
import GSM;

std::string test_data = R"(

lda x, 32

)";

//class Instruction : public GSM::Instruction
//{
//
//};

class Assembler : public GSM::Assembler
{
public:
	Assembler ( ) : GSM::Assembler ( )
	{
		std::println ( "Hello from My 6502 Assembler!" );

		FeedString ( test_data );
	} // 145
private:
};

auto main ( ) -> int
{
	auto assembler = Assembler ( );
}