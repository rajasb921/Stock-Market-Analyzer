#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;

/// <summary>
/// Derived class for recognizing bearish candlesticks
/// </summary>
public ref class Recognizer_Bearish : Recognizer
{
public:

	// Constructor
	Recognizer_Bearish() : Recognizer("Bearish", 1) {}

	// Recognize a bearish candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};
