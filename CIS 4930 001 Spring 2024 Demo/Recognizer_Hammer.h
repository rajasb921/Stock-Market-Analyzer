#pragma once
#include "Recognizer.h"
using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Collections::Generic;


/// <summary>
/// Derived class for recognizing hammer candlesticks
/// </summary>
public ref class Recognizer_Hammer : Recognizer
{
public:

	// Constructor
	Recognizer_Hammer() : Recognizer("Hammer", 1) {}

	// Recognize a Hammer candlestick
	bool Recognize(List<SmartCandlestick^>^ lscs, int index) override;

};

