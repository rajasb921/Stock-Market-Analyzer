#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;


/// <summary>
/// Derived class for recognizing bearish engulfing candlesticks
/// </summary>
public ref class Recognizer_BearishEngulfing : Recognizer
{
public:

	// Constructor
	Recognizer_BearishEngulfing() : Recognizer("Bearish Engulfing", 2) {}

	// Recognize a BearishEngulfing candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};

