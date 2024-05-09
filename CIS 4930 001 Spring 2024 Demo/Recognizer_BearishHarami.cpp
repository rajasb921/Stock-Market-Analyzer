#include "pch.h"
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "Recognizer_BearishHarami.h"
#include "Recognizer.h"

/// <summary>
/// Recognizes whether the candlestick at the index and the one after it is a bearish harami pattern
/// Updates the patterns dictionary in the candlestick
/// </summary>
/// <param name="lscs"> The list of smart candlesticks</param>
/// <param name="index"> The index in the list where the candlestick is located</param>
/// <returns>bool: Whether the candlesticks follow a bearish harami pattern</returns>
bool Recognizer_BearishHarami::Recognize(List<SmartCandlestick^>^ lscs, int index)
{
	bool firstBullish = lscs[index]->patterns["Bullish"];
	bool secondBearish = lscs[index + 1]->patterns["Bearish"];
	double firstBottom = lscs[index]->bottomPrice;
	double firstTop = lscs[index]->topPrice;
	double secondBottom = lscs[index + 1]->bottomPrice;
	double secondTop = lscs[index + 1]->topPrice;

	return firstBullish && secondBearish && (firstBottom < secondBottom) && (firstTop > secondTop);
}