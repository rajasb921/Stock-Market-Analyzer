#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;

/// <summary>
/// Derived class for recognizing doji candlesticks
/// </summary>
public ref class Recognizer_Doji : Recognizer
{
public:

	// Constructor
	Recognizer_Doji() : Recognizer("Doji", 1) {}

	// Recognize a Doji candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};
