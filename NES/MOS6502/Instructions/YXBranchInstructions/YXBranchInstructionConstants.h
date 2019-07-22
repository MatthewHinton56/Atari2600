
namespace mos6502
{
	enum class YXBranchInstructionAddressingMode
	{
		immediate = 0,
		zeroPage,
		impl,
		absolute,
		relative,
		xZeroPage,
		impl_two,
		absoluteX
	};

	enum class YXBranchInstructions
	{
		iSty,
		iDey,
		iBcc,
		iTya,
		iLdy,
		iTay,
		iBcs,
		iClv,
		iCpy,
		iIny,
		iBne,
		iCld,
		iCpx,
		iInx,
		iBeq,
		iSed
	};

	static std::map<uint8_t, YXBranchInstructions> YXBHexToInstructions
	{
		{0x84, YXBranchInstructions::iSty},
		{0x88, YXBranchInstructions::iDey},
		{0x8C, YXBranchInstructions::iSty},
		{0x90, YXBranchInstructions::iBcc},
		{0x94, YXBranchInstructions::iSty},
		{0x98, YXBranchInstructions::iTya},

		{0xA0, YXBranchInstructions::iLdy},
		{0xA4, YXBranchInstructions::iLdy},
		{0xA8, YXBranchInstructions::iTay},
		{0xAC, YXBranchInstructions::iLdy},
		{0xB0, YXBranchInstructions::iBcs},
		{0xB4, YXBranchInstructions::iLdy},
		{0xB8, YXBranchInstructions::iClv},
		{0xBC, YXBranchInstructions::iLdy}
	};

}