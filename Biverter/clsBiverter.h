#pragma once




#include<iostream>
#include<unordered_map>
#include<string>




// DEC.

class clsBiverter
{

	private:

		enum enSize {
			Extendable = 1 , NotExtendable = 2
		};

		std::unordered_map<std::string, char> _hexMap;

		std::unordered_map<std::string, char> _octalMap;

		enSize _checkNumberSize(std::string);
		
		std::string _extendNumber(std::string);

		std::string _convertToDecimal(std::string);

		std::string _convertToHexadecimal(std::string);

		std::string _convertToOctal(std::string);

		std::string _shiftLeftLogical(std::string);

		std::string _shiftRightLogical(std::string);

		bool _checkValidInput(std::string);

		bool _isStrangeInput(char);

		void _initializeHexMapValues(void);

		void _initializeOctMapValues(void);
	
	public:

		clsBiverter(void);

		~clsBiverter(void);
		
	
		std::string convertToDecimal(std::string);

		std::string convertToHexadecimal(std::string);

		std::string convertToOctal(std::string);
		
		std::string shiftLeftLogical(std::string);

		std::string shiftRightLogical(std::string);

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





clsBiverter::enSize clsBiverter::_checkNumberSize(std::string number) {

	const short sizeInBits = 32;

	return (number.length() == sizeInBits) ? clsBiverter::enSize::NotExtendable : clsBiverter::Extendable;
}

std::string clsBiverter::_extendNumber(std::string number) {

	const short sizeInBits = 32;

	short numberOfZeros = 32 - number.length();
	
	std::string extendedNumber = "";

	while (numberOfZeros--) {
		extendedNumber += '0';
	}

	extendedNumber = extendedNumber + number;

	return extendedNumber;
}

bool clsBiverter::_checkValidInput(std::string number) {

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




std::string clsBiverter::convertToDecimal(std::string number) {
	return this->_convertToDecimal(number);
}

std::string clsBiverter::_convertToDecimal(std::string number) {

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


	return std::to_string(decimalValue);
}

std::string clsBiverter::convertToHexadecimal(std::string number) {
	return this->_convertToHexadecimal(number);
}

std::string clsBiverter::_convertToHexadecimal(std::string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}


	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}




	std::string numberInHex = "";
	std::string nibble = "";

	for (int i = 0; i < number.length() ; i++) {

		nibble += number[i];

		if (nibble.length() == 4) {
			numberInHex += this->_hexMap[nibble];
			nibble = "";
		}
	
	}


	return numberInHex;
}

std::string clsBiverter::convertToOctal(std::string number) {
	return this->_convertToOctal(number);
}

std::string clsBiverter::_convertToOctal(std::string number) {

	if (!this->_checkValidInput(number)) {
		return "ERROR";
	}

	enSize result = this->_checkNumberSize(number);

	if (result == enSize::Extendable) {
		number = this->_extendNumber(number);
	}


	std::string numberInOctal = "";
	std::string triad = "";


	for (int i = 0; i < number.length(); i++) {

		triad += number[i];

		if (triad.length() == 3) {
			numberInOctal += this->_octalMap[triad];
			triad = "";
		}
	}


	return numberInOctal;
}




std::string clsBiverter::shiftLeftLogical(std::string number) {
	return this->_shiftLeftLogical(number);
}

std::string clsBiverter::_shiftLeftLogical(std::string number) {

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

std::string clsBiverter::shiftRightLogical(std::string number) {
	return this->_shiftRightLogical(number);
}

std::string clsBiverter::_shiftRightLogical(std::string number) {

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
