#pragma once

namespace mos6502
{
	enum class YXBranchInstructionAddressingMode : uint8_t
	{
		immediate = 0,
		zeroPage,
		implied,
		absolute,
		relative,
		xZeroPage,
		impl_two,
		absoluteX
	};

	enum class YXBranchInstructions : uint8_t
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
		{0xBC, YXBranchInstructions::iLdy},

		{0xC0, YXBranchInstructions::iCpy},
		{0xC4, YXBranchInstructions::iCpy},
		{0xC8, YXBranchInstructions::iIny},
		{0xCC, YXBranchInstructions::iCpy},
		{0xD0, YXBranchInstructions::iBne},
		{0xD8, YXBranchInstructions::iCld},

		{0xE0, YXBranchInstructions::iCpx},
		{0xE4, YXBranchInstructions::iCpx},
		{0xE8, YXBranchInstructions::iInx},
		{0xEC, YXBranchInstructions::iCpx},
		{0xF0, YXBranchInstructions::iBeq},
		{0xF8, YXBranchInstructions::iSed}
	};

	static std::map<YXBranchInstructionAddressingMode, uint8_t> YXBcycleTimes
	{
		{YXBranchInstructionAddressingMode::immediate, 2},
		{YXBranchInstructionAddressingMode::zeroPage, 3},
		{YXBranchInstructionAddressingMode::implied, 2},
		{YXBranchInstructionAddressingMode::absolute, 4},
		{YXBranchInstructionAddressingMode::relative, 2},
		{YXBranchInstructionAddressingMode::xZeroPage, 4},
		{YXBranchInstructionAddressingMode::absoluteX, 4}
	};

	static std::map<YXBranchInstructionAddressingMode, uint8_t> YXBInstructionSizes
	{
		{YXBranchInstructionAddressingMode::relative, 2},
		{YXBranchInstructionAddressingMode::zeroPage, 2},
		{YXBranchInstructionAddressingMode::immediate, 2},
		{YXBranchInstructionAddressingMode::absolute, 3},
		{YXBranchInstructionAddressingMode::xZeroPage, 2},
		{YXBranchInstructionAddressingMode::absoluteX, 3},
		{YXBranchInstructionAddressingMode::implied, 1}
	};

}