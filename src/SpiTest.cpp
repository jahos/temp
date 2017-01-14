//============================================================================
// Name        : SpiTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#include "HumSensor.h"
#include "Spi.h"


using namespace std;

bool finish = true;

void* receiver(void * args)
{
	Spi * sp = reinterpret_cast<Spi*>(args);
	int (*wsk)() = 0;
	switch(sp->ID)
	{
	case 1:
		wsk = SPI1_IRQHandler;
		break;
	case 2:
		wsk = SPI2_IRQHandler;
		break;
	case 3:
		wsk = SPI3_IRQHandler;
		break;
	}
	while(finish)
	{
		finish = wsk();
		SPI1_IRQHandler();
	}
	pthread_exit(NULL);
}

void wyslij()
{

	int a;
	while((a != 1) && (a != 2) && (a != 3))
	{
		cout << "ktory SPI?" << endl;
		cin >> a;
	}
	int b;
	cout << "Podaj liczbe do wyslania:";
	cin >> b ;
	switch(a)
	{
	case 1:
	{
		CSpi1 & sp = CSpi1::getInstance();
		sp.addToQ(b);
		break;
	}
	case 2:
	{
		CSpi2 & sp = CSpi2::getInstance();
		sp.addToQ(b);
		break;
	}
	case 3:
	{
		CSpi3 & sp = CSpi3::getInstance();
		sp.addToQ(b);
		break;
	}
	default:
		cout << "Jakims cudem tu sie znalazlem!" << endl;
	}
}

int main() {

	pthread_t receiveThread1;
	pthread_t receiveThread2;
	pthread_t receiveThread3;

	CSpi1 & sp1 = CSpi1::getInstance();
	CSpi2 & sp2 = CSpi2::getInstance();
	CSpi3 & sp3 = CSpi3::getInstance();

//	int a = 10;
//	while(a != 10)
//	{
//		cout << "Ktory watek uruchomic? " << endl;
//		cin >> a;
//		switch(a)
//		{
//		case 10:
//		{
//			finish = false;
//			break;
//		}
//		case 1:
//		{
//			pthread_create(&receiveThread1, NULL, receiver, reinterpret_cast<void*>(&sp1));
//			break;
//		}
//		case 2:
//		{
//			pthread_create(&receiveThread2, NULL, receiver, reinterpret_cast<void*>(&sp2));
//			break;
//		}
//		case 3:
//		{
//			pthread_create(&receiveThread3, NULL, receiver, reinterpret_cast<void*>(&sp3));
//			break;
//		}
//		case 4:
//		{
//			wyslij();
//			break;
//		}
//		default:
//			break;
//		}
//	}
//	finish = false;
//
//	pthread_exit(NULL);

	sp2.addToQ(0xAA);
	sp2.addToQ(0xAA);
	sp2.addToQ(0xAA);
	sp2.addToQ(0xAA);
	sp2.send();

	HumSensor & hs = HumSensor::getInstance();
//	hs.measurementRequest();
	hs.collectMeasuremets();
	cout.precision(4);
	cout << "hum[" << hs.getHumidity() << "]" << endl;
	cout << "tem[" << hs.getTemperature() << "]" << endl;
	return 0;
}
