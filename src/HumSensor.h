/*
 * HumSensor.h
 *
 *  Created on: 13 sty 2017
 *      Author: jahos
 */

#ifndef HUMSENSOR_H_
#define HUMSENSOR_H_

#include "Spi.h"

class HumSensor {
private:

	HumSensor();

	static HumSensor * humSensInstance;
	CSpi2 & spi;

	float humidity;
	float temperature;

public:
	static HumSensor & getInstance()
	{
		static HumSensor hum;
		humSensInstance = &hum;
		return *humSensInstance;
	}

	void measurementRequest();

	void dataFetch();

	void collectMeasuremets();

	float getHumidity() {return humidity;}
	float getTemperature() {return temperature; }

	virtual ~HumSensor();
};

#endif /* HUMSENSOR_H_ */
