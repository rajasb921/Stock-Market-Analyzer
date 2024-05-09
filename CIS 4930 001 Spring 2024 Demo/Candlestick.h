#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;

/// <summary>
/// Candlestick class which contains the Date, Open, High, Low, Close and Volume
/// </summary>
public ref class Candlestick
{
public:
	property DateTime Date;				// Date for the stock candlestick
	property double Open;				// Open price for the stock
	property double High;				// High price of the stock
	property double Low;				// Low price of the stock
	property double Close;				// Close price of the stock
	property unsigned long long Volume; // Volume of stock that was traded

	// Default constructor
	Candlestick() {};

	// Constructor that takes a a CSV lines as input
	Candlestick(String^ csvLine);

};


