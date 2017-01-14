/*
 * ISpi.cpp
 *
 *  Created on: 14 sty 2017
 *      Author: jahos
 */
#include <iostream>
#include "ISpi.h"

using namespace std;

int Spi::getMessage()
{
	int msg = BUFFER_EMPTY;

	if(!(outBuffer.empty()))
	{
		CommandS command = outBuffer.front();
		msg = command.msg;

		//update D/C# anc CS# line
		//GPIO_ResetBit(GPIOA,CS_PIN,ENABLE);
		//GPIO_WriteBit(GPIOA,D_C_PIN, (BitAction)command.d_c);
		cout << "CS(\\_)";
		if(command.d_c)
		{
			cout << "	D_C(_/)";
		}
		else
		{
			cout << "	D_C(\\_)";
		}

		cout << endl;

		//remove job from queue
		outBuffer.pop();
	}
	return msg;
}

void Spi::storeData(int byte)
{
	inBuffer.push(byte);
}

int Spi::getData()
{
	int retVal = BUFFER_EMPTY;
	if(inBuffer.size() != 0)
	{
		retVal = inBuffer.front();
		inBuffer.pop();
	}
	return retVal;
}

void Spi::addToQ(int msg,CommandE d_c)
{
	CommandS command;
	command.msg = msg;
	command.d_c = d_c;
	outBuffer.push(command);
	storeData(msg); //skrocilem sobie aby sprawdzic algorytm
}



