#include <print>
import GSM;

std::unordered_map<std::string , GSM::Register> Registers = {
	{ "a", 0x00 },
	{ "x", 0x01 },
	{ "y", 0x02 },
	{ "pc", 0x03 },
	{ "s", 0x04 },
	{ "p", 0x05 } // this is not how it really works on a 6502, it's just for testing purposes
};

static const std::string test_data = R"(
main:
	lda x, [32]
)";

class Instruction : public GSM::Instruction
{
public:
	GSM::Register FindRegister ( const std::string & mnemonic ) const override
	{
		return Registers.at ( mnemonic );
	}

	std::vector<GSM::Byte> Encode ( ) const override
	{
		std::vector<GSM::Byte> out;
		return out;
	}

	std::uint8_t DeduceLength ( ) const override
	{
		return 0;
	}

};

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