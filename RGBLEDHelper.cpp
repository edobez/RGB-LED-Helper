#include <ColorLamp.h>

// Costruttore dell'oggetto ColorLamp
ColorLamp::ColorLamp(int Rpin, int Gpin, int Bpin)	{
	
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
// FUNZIONI DI MODIFICA _private
// ***

// RETURNS: pointer to private _status
int* ColorLamp::getStatus()	{
	return _status;
}

// RETURNS: pointer to private _pinout
int* ColorLamp::getPin()	{
	return _pin;
}

// RETURNS: pointer to private _target
int* ColorLamp::getTarget()	{
	return _target;
}

// RETURNS: pointer to private _minLum
int* ColorLamp::getMinLum()	{
	return _minLum;
}

// RETURNS: pointer to private _maxLum
int* ColorLamp::getMaxLum()	{
	return _maxLum;
}

// Setta il massimo dei valori possibili per il led
void ColorLamp::setMinLum(byte Rmin, byte Gmin, byte Bmin)	{
	if (_checkColor(Rmin) && _checkColor(Gmin) && _checkColor(Bmin))	{
		_minLum[0] = Rmin;
		_minLum[1] = Gmin;
		_minLum[2] = Bmin;
	}
	else Serial.println("Error - setMinLum");
}

// Setta il minimo dei valori possibili per il led
void ColorLamp::setMaxLum(byte Rmax, byte Gmax, byte Bmax)	{
	if (_checkColor(Rmax) && _checkColor(Gmax) && _checkColor(Bmax))	{
		_maxLum[0] = Rmax;
		_maxLum[1] = Gmax;
		_maxLum[2] = Bmax;
	}
	else Serial.println("Error - setMaxLum");
}



// ***
// FUNZIONI DI AZIONE
// ***


// Setta il colore
bool ColorLamp::setRGB(int R, int G, int B)	{
	if (_checkColor(R,0) && _checkColor(G,1) && _checkColor(B,2))	{	//controlla che i valori siano accettabili
		Serial.println("Eseguo setRGB");
		
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
		Serial.println("Valori errati RGB");
		return 0;
	}
	
}

// Sfuma il colore verso il colore input con velocità variabile
bool ColorLamp::fadeRGB(int R, int G, int B, int fadeSpeed)	{
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
		Serial.println("Valori errati RGB");
		return 0;
	} 
}

// I comandi qui sotto non risentono delle limitazioni di min e max lum.

// Spegne il led
void ColorLamp::off()	{
	for (int i=0; i<3; i++)	{
		digitalWrite(_pin[i],LOW);
		_status[i] = 0;
	}
}

// Accende il led
void ColorLamp::on()	{
	for (int i=0; i<3; i++)	{
		digitalWrite(_pin[i],HIGH);
		_status[i] = 255;
	}
}

// Accende i led marcati con 1 e spegne gli altri
void ColorLamp::set(bool R, bool G, bool B)	{
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
// FUNZIONI UTILITY
// ***


// RETURN: true if color is acceptable, false if not
bool ColorLamp::_checkColor(int c) {
	if (c >= 0 && c <= 255)	return 1;
	else return 0;
}

bool ColorLamp::_checkColor(int c, byte led)	{
	if (c >= _minLum[led] && c <= _maxLum[led])	return 1;
	else return 0;
}

