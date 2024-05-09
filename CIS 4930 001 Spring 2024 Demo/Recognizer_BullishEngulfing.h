#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;

/// <summary>
/// Derived class for recognizing bullish engulfing candlesticks
/// </summary>
public ref class Recognizer_BullishEngulfing : Recognizer
{
public:

	// Constructor
	Recognizer_BullishEngulfing() : Recognizer("Bullish Engulfing", 2) {}

	// Recognize a BullishEngulfing candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};

