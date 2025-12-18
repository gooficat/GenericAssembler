import GSM;

std::unordered_map<std::string , GSM::Register> Registers = {
	{ "x", 0x00 },
	{ "y", 0x01 },
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