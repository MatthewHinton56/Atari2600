#include "ArithmeticLogicInstruction.h"

using namespace mos6507;

ArithmeticLogicInstruction::ArithmeticLogicInstruction
(
	uint8_t caValue, 
	instructionAddressingMode decodeMode, 
	Word PC, 
	Word operand, 
	Word registerOperand
) :
	instruction(static_cast<arithmeticLogicInstructions>(caValue)),
	decodeMode(decodeMode),
	PC(PC),

)
{
}
