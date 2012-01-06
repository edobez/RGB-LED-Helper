#ifndef 	ColorLamp_H
#define	ColorLamp_H

#include <Arduino.h>

class ColorLamp	
	{
public:
	ColorLamp(int R, int G, int B);
	
	bool setRGB(int R, int G, int B);
	bool fadeRGB(int R, int G, int B, int fadeSpeed);
	
	void off();
	void on();
	void set(bool R, bool G, bool B);
	void setMinLum(byte Rmin, byte Gmin, byte Bmin);
	void setMaxLum(byte Rmax, byte Gmax, byte Bmax);
	
	int* getStatus();
	int* getPin();
	int* getTarget();
	int* getMinLum();
	int* getMaxLum();

private:
	bool _checkColor(int c);
	bool _checkColor(int c, byte led);
	
	int _pin[3];
	int _status[3];
	int _target[3];
	int _maxLum[3];
	int _minLum[3];
	
};

#endif
