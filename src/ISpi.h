/*
 * ISpi.h
 *
 *  Created on: 13 sty 2017
 *      Author: jahos
 */

#ifndef ISPI_H_
#define ISPI_H_

#include <stdint-gcc.h>
#include <array>
#include <queue>
#include "stab.h"

/*Pins Config SPI1
 * CLK 	PA5
 * MOSI	PA7
 * CS	PA4
 *
 * D_C	PA6
 * RES	PC4
 * */

#define CLK_PIN		GPIO_Pin_5
#define CS_PIN  	GPIO_Pin_4
#define MOSI_PIN	GPIO_Pin_7
#define D_C_PIN 	GPIO_Pin_6
#define RES_PIN 	GPIO_Pin_4

#define BUFFER_EMPTY	256

class Spi;

enum CommandE
{
		COMMAND = 0
	,	DATA	= 1
};

struct CommandS
{
	int msg;
	CommandE d_c;
};

class Spi {
private:
	/*queue for as buffer of command*/
	std::queue<CommandS> outBuffer;
	std::queue<int> inBuffer;
public:
	int ID;
	/**
	 * @brief  Get message from Queue
	 * @param  Instance of SPI object
	 * @retval None
	 */
	int getMessage();

	/**
	 * @brief  store data from Rx buffer
	 * @param  byte from buffer
	 * @retval None
	 */
	void storeData(int byte);

	int getData();

	/**
	 * @brief  Add message to Queue
	 * @param  Message which should be send
	 * @retval None
	 */
	void addToQ(int msg,CommandE d_c = COMMAND);

	/*destructor*/
	virtual ~Spi() {};
};

#endif /* ISPI_H_ */
