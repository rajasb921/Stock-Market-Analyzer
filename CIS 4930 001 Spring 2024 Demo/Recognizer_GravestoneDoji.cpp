#include "pch.h"
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "Recognizer_GravestoneDoji.h"
#include "Recognizer.h"

/// <summary>
/// Recognizes whether the candlestick at the index is Gravestone Doji
/// Updates the patterns dictionary in the candlestick
/// </summary>
/// <param name="lscs"> The list of smart candlesticks</param>
/// <param name="index"> The index in the list where the candlestick is located</param>
/// <returns>bool: Whether the candlestick is Gravestone Doji</returns>
bool Recognizer_GravestoneDoji::Recognize(List<SmartCandlestick^>^ lscs, int index)
{
	return (lscs[index]->bodyRange < 0.1 * lscs[index]->Range) && (lscs[index]->lowerTail < 0.02 * lscs[index]->Range);

}