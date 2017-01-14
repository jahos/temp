/*
 * Spi.cpp
 *
 *  Created on: 12 sty 2017
 *      Author: jahos
 */
#include <iostream>
#include "Spi.h"

using namespace std;

int (*pGetByteFunc)(Spi &sp) = 0;

CSpi1 * CSpi1::spiInstance = 0;
CSpi2 * CSpi2::spiInstance = 0;
CSpi3 * CSpi3::spiInstance = 0;

int getByte(int spiNum)
{
	int byteToSend  = BUFFER_EMPTY;
	switch(spiNum)
	{
	case 0:
	{
		CSpi1 & sp = CSpi1::getInstance();
		byteToSend = sp.getMessage();
		break;
	}
	case 1:
	{
		CSpi2 & sp = CSpi2::getInstance();
		byteToSend = sp.getMessage();
		break;
	}
	case 2:
	{
		CSpi3 & sp = CSpi3::getInstance();
		byteToSend = sp.getMessage();
		break;
	}
	}
	return byteToSend;
}

/*---------------private methods-----------------------------------------------*/

CSpi1 & CSpi1::getInstance()
{
	static CSpi1 retInstance;
	spiInstance = &retInstance;
	return retInstance;
}

CSpi2 & CSpi2::getInstance()
{
	static CSpi2 retInstance;
	spiInstance = &retInstance;
	return retInstance;
}

CSpi3 & CSpi3::getInstance()
{
	static CSpi3 retInstance;
	spiInstance = &retInstance;
	return retInstance;
}

int SPI1_IRQHandler()
{
	int result = true;
	int c = getByte(SPI1);
	if( c < BUFFER_EMPTY)
	{
		cout << "getByte(SPI1) =" << c << endl;
	}
	else
	{
//		result = false;
//		cout << "CS2(_/)" << endl;
		//GPIO_ResetBit(GPIOA,CS_PIN);
	}
	return result;
}


int SPI2_IRQHandler()
{
	int result = true;
	int c = getByte(SPI2);
	if( c < BUFFER_EMPTY)
	{
		cout << "getByte(SPI2) =" << c << endl;
	}
	else
	{
//		result = false;
//		cout << "CS3(_/)" << endl;
		//GPIO_ResetBit(GPIOA,CS_PIN);
	}
	return result;
}

int SPI3_IRQHandler()
{
	int result = true;
	int c = getByte(SPI3);

	if( c < BUFFER_EMPTY)
	{
		cout << "getByte(SPI3) =" << c << endl;
	}
	else
	{
//		result = false;
//		cout << "CS3(_/)" << endl;
		//GPIO_ResetBit(GPIOA,CS_PIN);
	}
	return result;
}

void CSpi1::send()
{
	cout << "SPI1_I2S_IT_TX_ENABLE" << endl;
}

void CSpi2::send()
{
	cout << "SPI2_I2S_IT_TX_ENABLE" << endl;
}

void CSpi3::send()
{
	cout << "SPI3_I2S_IT_TX_ENABLE" << endl;
}
