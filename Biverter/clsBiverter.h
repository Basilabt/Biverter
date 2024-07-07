#pragma once




#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;



// DEC.

class clsBiverter
{

	private:

		enum enSize {
			Extendable = 1 , NotExtendable = 2
		};

		unordered_map<string, char> _hexMap;

		unordered_map<string, char> _octalMap;

		enSize _checkNumberSize(string);
		
		string _extendNumber(string);

		string _convertToDecimal(string);

		string _convertToHexadecimal(string);

		string _convertToOctal(string);

		string _shiftLeftLogical(string);

		string _shiftRightLogical(string);

		bool _checkValidInput(string);

		bool _isStrangeInput(char);

		void _initializeHexMapValues(void);

		void _initializeOctMapValues(void);
	
	public:

		clsBiverter(void);

		~clsBiverter(void);
		
	
		string convertToDecimal(string);

		string convertToHexadecimal(string);

		string convertToOctal(string);
		
		string shiftLeftLogical(string);

		string shiftRightLogical(string);

};




// DEF.


clsBiverter::clsBiverter() {
	this->_initializeHexMapValues();
	this->_initializeOctMapValues();
}

clsBiverter::~clsBiverter() {
	this->_hexMap.clear();
	this->_octalMap.clear();
}





clsBiverter::enSize clsBiverter::_checkNumberSize(string number) {

	const short sizeInBits = 32;

	return (number.length() == sizeInBits) ? clsBiverter::enSize::NotExtendable : clsBiverter::Extendable;
}

string clsBiverter::_extendNumber(string number) {

	const short sizeInBits = 32;

	short numberOfZeros = 32 - number.length();
	
	string extendedNumber = "";

	while (numberOfZeros--) {
		extendedNumber += '0';
	}

	extendedNumber = extendedNumber + number;

	return extendedNumber;
}

bool clsBiverter::_checkValidInput(string number) {

	if (number == "") {
		return false;
	}


	for (char& c : number) {
		if (this->_isStrangeInput(c)) {
			return false;
		}
	}

	return true;
}

bool clsBiverter::_isStrangeInput(char c) {
	return (c != '0') ? (c != '1') : false;
}

void clsBiverter::_initializeHexMapValues() {
	this->_hexMap["0000"] = '0';
	this->_hexMap["0001"] = '1';
	this->_hexMap["0010"] = '2';
	this->_hexMap["0011"] = '3';
	this->_hexMap["0100"] = '4';
	this->_hexMap["0101"] = '5';
	this->_hexMap["0110"] = '6';
	this->_hexMap["0111"] = '7';
	this->_hexMap["1000"] = '8';
	this->_hexMap["1001"] = '9';
	this->_hexMap["1010"] = 'A';
	this->_hexMap["1011"] = 'B';
	this->_hexMap["1100"] = 'C';
	this->_hexMap["1101"] = 'D';
	this->_hexMap["1110"] = 'E';
	this->_hexMap["1111"] = 'F';
}

void clsBiverter::_initializeOctMapValues() {
	this->_octalMap["000"] = '0';
	this->_octalMap["001"] = '1';
	this->_octalMap["010"] = '2';
	this->_octalMap["011"] = '3';
	this->_octalMap["100"] = '4';
	this->_octalMap["101"] = '5';
	this->_octalMap["110"] = '6';
	this->_octalMap["111"] = '7';
}




string clsBiverter::convertToDecimal(string number) {
	return this->_convertToDecimal(number);
}

string clsBiverter::_convertToDecimal(string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}


	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}


	unsigned long long currentValue = 1;
	unsigned long long decimalValue = 0;

	for (int i = number.length() - 1; i >= 0; i--) {
		
		decimalValue += (number[i] == '1') ? currentValue : 0;

		currentValue *= 2;
	}


	return to_string(decimalValue);
}

string clsBiverter::convertToHexadecimal(string number) {
	return this->_convertToHexadecimal(number);
}

string clsBiverter::_convertToHexadecimal(string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}


	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}




	string numberInHex = "";
	string nibble = "";

	for (int i = 0; i < number.length() ; i++) {

		nibble += number[i];

		if (nibble.length() == 4) {
			numberInHex += this->_hexMap[nibble];
			nibble = "";
		}
	
	}


	return numberInHex;
}

string clsBiverter::convertToOctal(string number) {
	return this->_convertToOctal(number);
}

string clsBiverter::_convertToOctal(string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}

	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}


	string numberInOctal = "";
	string triad = "";


	for (int i = 0; i < number.length(); i++) {

		triad += number[i];

		if (triad.length() == 3) {
			numberInOctal += this->_octalMap[triad];
			triad = "";
		}
	}


	return numberInOctal;
}




string clsBiverter::shiftLeftLogical(string number) {
	return this->_shiftLeftLogical(number);
}

string clsBiverter::_shiftLeftLogical(string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}

	number = number.substr(1) + '0';

	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}


	return number;
}

string clsBiverter::shiftRightLogical(string number) {
	return this->_shiftRightLogical(number);
}

string clsBiverter::_shiftRightLogical(string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}

	number = '0' + number.substr(0, number.length() - 1);

	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}



	return number;
}
