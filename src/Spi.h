/*
 * Spi.h
 *
 *  Created on: 12 sty 2017
 *      Author: jahos
 */

#ifndef SPI_H_
#define SPI_H_

#include "ISpi.h"

enum SpiE
{
		SPI1 = 0
	,	SPI2 = 1
	,	SPI3 = 2
};

int SPI1_IRQHandler();
int SPI2_IRQHandler();
int SPI3_IRQHandler();

class CSpi1 : public Spi
{
private:
	CSpi1() { ID = 1;}
	/*Instance to SPI object*/
	static CSpi1 * spiInstance;
public:
	static CSpi1 & getInstance();
	void send();
	~CSpi1() {};
};

class CSpi2 : public Spi
{
private:
	CSpi2() {ID = 2;}
	/*Instance to SPI object*/
	static CSpi2 * spiInstance;
public:
	static CSpi2 & getInstance();
	void send();
	~CSpi2() {};
};

class CSpi3 : public Spi
{
private:
	CSpi3() {ID = 3;}
	/*Instance to SPI object*/
	static CSpi3 * spiInstance;
public:

	static CSpi3 & getInstance();
	void send();
	~CSpi3() {};
};


#endif /* SPI_H_ */
