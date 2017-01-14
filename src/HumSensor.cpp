/*
 * HumSensor.cpp
 *
 *  Created on: 13 sty 2017
 *      Author: jahos
 */

#include "HumSensor.h"
#include <iostream>
#include <bitset>

using namespace std;

HumSensor* HumSensor::humSensInstance = 0;

HumSensor::HumSensor() : spi(CSpi2::getInstance())
						,humidity(0)
						,temperature(0)
{

}

HumSensor::~HumSensor() {

}

void HumSensor::measurementRequest()
{
	spi.addToQ(0xFF);
	spi.send();
}

void HumSensor::dataFetch()
{
	spi.addToQ(0xFF);
	spi.addToQ(0xFF);
	spi.addToQ(0xFF);
	spi.addToQ(0xFF);
	spi.send();
}

void HumSensor::collectMeasuremets()
{
	int tmp = 0;
	unsigned int pomiar = 0;

	do
	{
		tmp = spi.getData();

		if(tmp != BUFFER_EMPTY)
		{
			pomiar = (pomiar << 8);
			pomiar |= tmp;
		}
	}while(tmp != BUFFER_EMPTY);

//	cout << "pomiar: " << std::bitset<32>(pomiar) << endl;

	int h = (pomiar >> 16 ) & 0x3FFF;
	int t = (pomiar >> 2 ) & 0x3FFF;

	humidity 	= (((float)h * 100) / 16382);
	temperature = (((float)t * 165) / 16382)-40;
}

