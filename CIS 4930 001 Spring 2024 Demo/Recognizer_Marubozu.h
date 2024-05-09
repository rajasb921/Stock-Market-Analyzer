#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;

/// <summary>
/// Derived class for recognizing marubozu candlesticks
/// </summary>
public ref class Recognizer_Marubozu : Recognizer
{
public:

	// Constructor
	Recognizer_Marubozu() : Recognizer("Marubozu", 1) {}

	// Recognize a Marubozu candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};

