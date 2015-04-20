#include <iostream>
#include <cstring>
#include <cmath>

void input();
inline int clamp(const int& val);
int classifyInstruction(const int& instruction);
void fetchExecuteCycle();
void executeInstruction();
void reset();

// processor properties
const int WORD_LENGTH = 4;
const int MAXIMUM_VALUE = std::pow(2.0f,WORD_LENGTH);

// memory structures
int R0 = 0;
int R1 = 0;
int instructionPointer = 0;
int instructionStore [2] = {0};
int memory[MAXIMUM_VALUE] = {0};

int main(){

	input();
	fetchExecuteCycle();

	return 0;
}

void reset(){

	R0 = R1 = instructionPointer = 0;
	std::memset(instructionStore,0,sizeof(instructionStore));
	std::memset(memory,0,sizeof(memory));
}

inline int clamp(const int& val){

	return val % MAXIMUM_VALUE;
}

void input(){

	int instruction = -1;
	int i = 0;

	while( std::cin >> instruction )
		memory[i++] = clamp(instruction);
}

void fetchExecuteCycle(){

	do{
		int instructionSize = classifyInstruction(memory[instructionPointer]);

		// The instruction at the address given by the instruction pointer 
		// is loaded into the instruction store.
		// The instruction pointer is incremented by 1 or 2 
		// depending on whether the instruction store is a 1 or 2 byte instruction.
		if (1 == instructionSize)
			instructionStore[0] = memory[instructionPointer++];
		else if (2 == instructionSize){
			instructionStore[0] = memory[instructionPointer];
			instructionStore[1] = memory[instructionPointer+1];
			instructionPointer += 2;
		}

		// The instruction in the instruction store is executed.
		executeInstruction();

	}while(0 != instructionStore[0]);
}

int classifyInstruction(const int& instruction){

	// 8 , 16 respresents a specific instruction set , therefore not generic
	if (instruction < 8 && instruction >= 0)
		return 1;
	else if (instruction < 16 && instruction >= 8)
		return 2;
	else
		return -1;
}

void executeInstruction(){

	switch(instructionStore[0]){

		case 1:
		R0 = clamp(R0 + R1);
		break;

		case 2:
		R0 = clamp(R0 - R1);
		break;

		case 3:
		R0 = clamp(R0 + 1);
		break;

		case 4:
		R1 = clamp(R1 + 1);
		break;

		case 5:
		R0 = clamp(R0 - 1);
		break;

		case 6:
		R1 = clamp(R1 - 1);
		break;

		case 7:
		std::cout << "DING DONG ";
		break;

		case 8:
		std::cout << instructionStore[1] << " ";
		break;

		case 9:
		R0 = instructionStore[1];
		break;

		case 10:
		R1 = instructionStore[1];
		break;

		case 11:
		memory[instructionStore[1]] = R0;
		break;

		case 12:
		memory[instructionStore[1]] = R1;
		break;

		case 13:
		instructionPointer = instructionStore[1];
		break;

		case 14:
		if (0 == R0)
			instructionPointer = instructionStore[1];
		break;

		case 15:
		if (0 != R0)
			instructionPointer = instructionStore[1];
		break;
	}
}
