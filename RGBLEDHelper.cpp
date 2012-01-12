#include <RGBLEDHelper.h>

/* CONSTRUCTOR
 	PARAMS: pin of the anodes.
	
	Set the initial status and target to 0, the minimum luminosity to 0 and the max to 255, and the pinmode to Output.
*/
RgbLed::RgbLed(int Rpin, int Gpin, int Bpin)	{
	
	_pin[0] = Rpin;
	_pin[1] = Gpin;
	_pin[2] = Bpin;
	
	for (int i=0; i<3; i++)	{
		
		pinMode(_pin[i], OUTPUT);
		_status[i] = 0;
		_target[i] = 0;
		_minLum[i] = 0;
		_maxLum[i] = 255;
	}

}

// ***
// ACCESSORS OF _private
// ***

// RETURNS: array of private _status
int * RgbLed::getStatus()	{
	return _status;
}

// RETURNS: array of private _pinout
int * RgbLed::getPin()	{
	return _pin;
}

// RETURNS: array of private _target
int * RgbLed::getTarget()	{
	return _target;
}

// RETURNS: array of private _minLum
int * RgbLed::getMinLum()	{
	return _minLum;
}

// RETURNS: array of private _maxLum
int * RgbLed::getMaxLum()	{
	return _maxLum;
}

// Set the minimum luminisity of each pin		
void RgbLed::setMinLum(byte Rmin, byte Gmin, byte Bmin)	{
	if (_checkColor(Rmin) && _checkColor(Gmin) && _checkColor(Bmin))	{
		_minLum[0] = Rmin;
		_minLum[1] = Gmin;
		_minLum[2] = Bmin;
	}
	else Serial.println("Error - setMinLum");
}

// Set the maximum luminisity of each pin	
void RgbLed::setMaxLum(byte Rmax, byte Gmax, byte Bmax)	{
	if (_checkColor(Rmax) && _checkColor(Gmax) && _checkColor(Bmax))	{
		_maxLum[0] = Rmax;
		_maxLum[1] = Gmax;
		_maxLum[2] = Bmax;
	}
	else Serial.println("Error - setMaxLum");
}



// ***
// MODIFIERS
// ***


// Set the color of the LED.
bool RgbLed::setRGB(int R, int G, int B)	{
	if (_checkColor(R,0) && _checkColor(G,1) && _checkColor(B,2))	{	//checks if the values are acceptable
		Serial.println("Running setRGB");
		
		_target[0] = R;
		analogWrite(_pin[0],R);
		_status[0] = R;
		
		_target[1] = G;
		analogWrite(_pin[1],G);
		_status[1] = G;
		
		_target[2] = B;
		analogWrite(_pin[2],B);
		_status[2] = B;
		
		return 1;
	}
	
	else {
		Serial.println("Non-acceptable RGB values");
		return 0;
	}
	
}

// Fade the LED to the input color with variable speed.
bool RgbLed::fadeRGB(int R, int G, int B, int fadeSpeed)	{
	if (_checkColor(R,0) && _checkColor(G,1) && _checkColor(B,2))	{
		
		_target[0] = R;
		_target[1] = G; 
		_target[2] = B;  
		
		while(!(	(_status[0] == _target[0]) && 
					(_status[1] == _target[1]) && 
					(_status[2] == _target[2])
				))	
		{
			for (int i=0; i<3; i++)	{
				if (_status[i] < _target[i]) {
					_status[i]++;
					analogWrite(_pin[i],_status[i]);
					}
				else if (_status[i] > _target[i])	{
					_status[i]--;
					analogWrite(_pin[i],_status[i]);
					}
			}
			delay(fadeSpeed);
			
		} // end while
		
		return 1;
		
	} // end if
	
	else	{
		Serial.println("Non-acceptable RGB values");
		return 0;
	} 
}

// I comandi qui sotto non risentono delle limitazioni di min e max lum.

// Turn OFF the LED.
void RgbLed::off()	{
	for (int i=0; i<3; i++)	{
		digitalWrite(_pin[i],LOW);
		_status[i] = 0;
	}
}

// Turn ON the LED.
void RgbLed::on()	{
	for (int i=0; i<3; i++)	{
		digitalWrite(_pin[i],HIGH);
		_status[i] = 255;
	}
}

// Turn ON/OFF each LED component.
// 1 to enable, 0 to disable.
void RgbLed::set(bool R, bool G, bool B)	{
	if (R)	{
		digitalWrite(_pin[0],HIGH);
		_status[0] = 255;
	}
	else	{
		digitalWrite(_pin[0],LOW);
		_status[0] = 0;
	}
	
	if (G)	{
		digitalWrite(_pin[1],HIGH);
		_status[1] = 255;
	}
	else	{
		digitalWrite(_pin[1],LOW);
		_status[1] = 0;
	}
	
	if (B)	{
		digitalWrite(_pin[2],HIGH);
		_status[2] = 255;
	}
	else	{
		digitalWrite(_pin[2],LOW);
		_status[2] = 0;
	}
	
}


// ***
// UTILITY FUNCTIONS
// ***


// RETURN: true if color is acceptable, false if not
bool RgbLed::_checkColor(int c) {
	if (c >= 0 && c <= 255)	return 1;
	else return 0;
}

// RETURN: true if color is acceptable for the led, false if not
bool RgbLed::_checkColor(int c, byte led)	{
	if (c >= _minLum[led] && c <= _maxLum[led])	return 1;
	else {
		Serial.print("Wrong color: ");
		Serial.print(c);
		Serial.print(" - Led: ");
		Serial.println(led);
		return 0;
	}
}

