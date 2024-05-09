#include "pch.h"
#include "Form_StockPicker.h"
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "Recognizer.h"
#include "Recognizer_Bullish.h"
#include "Recognizer_Bearish.h"
#include "Recognizer_Neutral.h"
#include "Recognizer_Marubozu.h"
#include "Recognizer_Hammer.h"
#include "Recognizer_Doji.h"
#include "Recognizer_DragonflyDoji.h"
#include "Recognizer_GravestoneDoji.h"
#include "Recognizer_BullishEngulfing.h"
#include "Recognizer_BearishEngulfing.h"
#include "Recognizer_BullishHarami.h"
#include "Recognizer_BearishHarami.h"
#include "Recognizer_Peak.h"
#include "Recognizer_Valley.h"

using namespace CppCLRWinFormsProject;
using namespace System::Windows::Forms::DataVisualization::Charting;

/// <summary>
/// Creates a dataGridView and a Chart based using data on the file selected in the openFileDialog
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns>Void</returns>
Void Form_StockPicker::openFileDialog_stockPicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	// Clear any existing annotations
	chart_OHLCV->Annotations->Clear();

	// Find filepath, display as text
	array<String^>^ files = openFileDialog_stockPicker->FileNames;
	String^ filePath = files[0];
	Text = "Loading: " + Path::GetFileNameWithoutExtension(filePath);

	// Read data from file and create a list of candlesticks
	listOfSmartCandlesticks = ReadCandleStickDataFromFile(filePath);



	// Recognize all candlestick patterns
	for each (Recognizer ^ recognizer in listOfRecognizers) {
		recognizer->RecognizeAll(listOfSmartCandlesticks);
	}


	// Filter candlesticks within the required date range
	boundListOfSmartCandlesticks = filterCandlesticks(listOfSmartCandlesticks);

	// Normalize chart
	normalizeChart(boundListOfSmartCandlesticks);

	// Bind boundListOfCandlesticks to Chart
	displayChart(boundListOfSmartCandlesticks);

	for (int i = 1; i < files->Length; i++) {

		Form_StockPicker^ formsp = gcnew Form_StockPicker();

		// Clear any existing annotations
		formsp->chart_OHLCV->Annotations->Clear();

		String^ filePath = files[i];
		formsp->Text = "Loading: " + Path::GetFileNameWithoutExtension(filePath);

		// Read data from file and create a list of candlesticks
		formsp->listOfSmartCandlesticks = formsp->ReadCandleStickDataFromFile(filePath);

		// Recognize all candlestick patterns
		for each (Recognizer ^ recognizer in formsp->listOfRecognizers) {
			recognizer->RecognizeAll(formsp->listOfSmartCandlesticks);
		}

		// Filter candlesticks within the required date range
		formsp->boundListOfSmartCandlesticks = formsp->filterCandlesticks(formsp->listOfSmartCandlesticks);

		// Normalize chart
		formsp->normalizeChart(formsp->boundListOfSmartCandlesticks);

		// Bind boundListOfCandlesticks to Chart
		formsp->displayChart(formsp->boundListOfSmartCandlesticks);

		// Show the form
		formsp->Show();
	}
}

/// <summary>
/// Updates the boundListOfCandlesticks based on the newly specified date range
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns>Void</returns>
Void Form_StockPicker::button_UpdatePicker_Click(System::Object^ sender, System::EventArgs^ e) {
	// Clear any existing annotations
	chart_OHLCV->Annotations->Clear();

	// Filter candlesticks within new data range
	filterCandlesticks();

	// Normalize the chart
	normalizeChart();

	// Bind new boundListOfCandlesticks to Chart
	displayChart();
}

/// <summary>
/// This reads data from the file.
/// </summary>
/// <param name="filePath">This is the path to the file to be read</param>
/// <returns>This will return a list of candlesticks</returns>
List<SmartCandlestick^>^ Form_StockPicker::ReadCandleStickDataFromFile(String^ filePath)
{
	// Clear existing listOfCandlesticks
	listOfSmartCandlesticks->Clear();

	if (File::Exists(filePath))
	{
		// Create reader for file
		StreamReader^ reader = gcnew StreamReader(filePath);

		// Skip header line
		String^ line = reader->ReadLine();

		// Loop through each row in the file
		while ((line = reader->ReadLine()) != nullptr)
		{
			// Create a new candlestick object using data from the Excel row
			Candlestick^ candlestick = gcnew Candlestick(line);
			SmartCandlestick^ smartCandlestick = gcnew SmartCandlestick(candlestick);
			// Add candlestick to the listOfCandlesticks
			listOfSmartCandlesticks->Add(smartCandlestick);

		}

		reader->Close();

	}
	else
	{
		// If file does not exist
		Console::Write("Error: File not found\n");

	}

	// Return listOfCandlesticks
	return listOfSmartCandlesticks;
}

/// <summary>
/// Calls ReadCandleStickDataFromFile by passing in the filepath from the openFileDialog
/// </summary>
/// <returns>Void</returns>
Void Form_StockPicker::ReadCandleStickDataFromFile() {
	// Call readCandleStickFromFile by passing in the chosen file
	listOfSmartCandlesticks = ReadCandleStickDataFromFile(openFileDialog_stockPicker->FileName);
}

/// <summary>
/// This filters the listOfCandlesticks according to the date range specified by the dateTimePickers
/// </summary>
/// <param name="loc">listOfCandlesticks that have to be filtered</param>
/// <returns>Returns a BindingList of Candlesticks, filtered by the required date range</returns>
BindingList<SmartCandlestick^>^ Form_StockPicker::filterCandlesticks(List<SmartCandlestick^>^ losc)
{
	// Create new list of selected candlesticks
	List<SmartCandlestick^>^ selectedSmartCandlesticks = gcnew List<SmartCandlestick^>(losc->Count);

	// Loop through all candlesticks and choose the ones required
	for (int i = 0; i < losc->Count; i++)
	{
		SmartCandlestick^ scs = losc[i];
		// Break if candlestick has passed end date
		if (dateTimePicker_End->Value < scs->Date) {
			break;
		}

		// Check if candlestick is in the required date range
		if (dateTimePicker_Start->Value <= scs->Date && scs->Date <= dateTimePicker_End->Value) {
			selectedSmartCandlesticks->Add(scs);
		}
	}

	// Create a BindingList from the selected candlesticks & return it
	BindingList<SmartCandlestick^>^ resultingBindingList = gcnew BindingList<SmartCandlestick^>(selectedSmartCandlesticks);
	return resultingBindingList;

}

/// <summary>
/// Calls filterCandlesticks which filters a listOfCandlesticks according to the date range specified by the dateTimePickers
/// </summary>
/// <returns>Void</returns>
Void Form_StockPicker::filterCandlesticks(){
	// Filter the listOfCandlesticks according to the range specified by the dateTimePickers
	boundListOfSmartCandlesticks = filterCandlesticks(listOfSmartCandlesticks);
}

/// <summary>
/// Normalizes the y-axis for chartArea_OHLC according to the maximum high and minimum low of the candlesticks
/// </summary>
/// <param name="bloc"></param>
/// <returns>Void</returns>
Void Form_StockPicker::normalizeChart(BindingList<SmartCandlestick^>^ blosc) {

	// Skip if boundListOfCandlesticks is empty
	if (blosc->Count == 0) { return; }

	// Initialize max_High and min_Low variables
	double max_High = blosc[0]->High;
	double min_Low = blosc[0]->Low;

	// Loop through the binding list of candlesticks
	for (int i = 0; i < blosc->Count; i++) {

		// cs will be Candlestick at current index
		SmartCandlestick^ scs = blosc[i];

		// If Candlestick high greater than current high
		if (scs->High > max_High) { max_High = scs->High; }

		// If Candlestick low lower than current low
		if (scs->Low < min_Low) { min_Low = scs->Low; }

	}
	
	// Increase max_High by 2%
	max_High = max_High * 1.02;

	// Increase min_Low by 2%
	min_Low = min_Low * 1.02;

	// Set chart area axis y maximum to max_High
	chart_OHLCV->ChartAreas[0]->AxisY->Maximum = max_High;

	// Set chart area axis y minimum to min_Low
	chart_OHLCV->ChartAreas[0]->AxisY->Minimum = min_Low;
}

/// <summary>
/// Calls normalizeChart which normalizes the y-axis for chartArea_OHLC according to the maximum high and minimum low of the candlesticks
/// </summary>
/// <returns>Void</returns>
Void Form_StockPicker::normalizeChart() {
	// Normalize y-axis for the chart
	normalizeChart(boundListOfSmartCandlesticks);
}

/// <summary>
/// Displays a chart using the boundListOfCandlesticks. The chart shows the candlesticks along with their volume
/// </summary>
/// <param name="bloc"></param>
/// <returns>Void</returns>
Void Form_StockPicker::displayChart(BindingList<SmartCandlestick^>^ blosc) {

	// Set chart source to be the bound list of candlesticks & return
	chart_OHLCV->DataSource = blosc;
	chart_OHLCV->DataBind();

}

/// <summary>
/// Calls displayChart which displays a chart using the boundListOfCandlesticks
/// </summary>
/// <returns>Void</returns>
Void Form_StockPicker::displayChart() {
	// Display the chart using data from the boundListOfCandlesticks
	displayChart(boundListOfSmartCandlesticks);
}


/// <summary>
/// Initializes the comboBox with the patterns found in the boundListOfCandlesticks
/// </summary>
/// <param name="blosc"></param>
/// <returns>Void</returns>
Void Form_StockPicker::initializeComboBox(BindingList<SmartCandlestick^>^ blosc) {
	
	// Empty blosc
	if (blosc->Count == 0) { return; }

	// Create a new SmartCandlestick object for the first candlestick in the list
	SmartCandlestick^ scs = blosc[0];

	// Clear the comboBox
	comboBox_Patterns->Items->Clear();

    // Check if the selectedCandlestick is not null and has patterns
	if (scs != nullptr && scs->patterns != nullptr)
	{
		// Get the patterns dictionary from the selectedCandlestick
		Dictionary<String^, bool>^ patterns = scs->patterns;

		// Add keys from the patterns dictionary to the combo box
		for each (String ^key in patterns->Keys)
		{
			comboBox_Patterns->Items->Add(key);  // Add the key to the comboBox
		}
	}
}



/// <summary>
/// Event handler for the comboBox.
/// Adds arrow annotations to the chart according to the pattern selected in the comboBox
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns>Void</returns>
Void Form_StockPicker::comboBox_Patterns_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	// Clear existing annotations
	chart_OHLCV->Annotations->Clear();

	// Get the selected pattern from the combo box
	String^ selectedPattern = comboBox_Patterns->SelectedItem->ToString();

	// Iterate through the candlesticks in the boundListOfSmartCandlesticks
	if (boundListOfSmartCandlesticks == nullptr) { return; }
	for (int i = 0; i < boundListOfSmartCandlesticks->Count; i++) {
		SmartCandlestick^ scs = boundListOfSmartCandlesticks[i];


		// Check if the selected pattern is true for the current candlestick
		if (scs->patterns[selectedPattern]) {
			// Create a new RectangleAnnotation object
			RectangleAnnotation^ rectangle = gcnew RectangleAnnotation();

			// Set the anchor point to the candlestick data point
			rectangle->AnchorDataPoint = chart_OHLCV->Series["Series_OHLC"]->Points[i];
			rectangle->IsSizeAlwaysRelative = false;

			// Set the rectangle properties
			rectangle->BackColor = Drawing::Color::Transparent;
			rectangle->LineWidth = 1;
			rectangle->LineColor = Drawing::Color::Black;

			// Calculate height, width, position based on the select pattern
			int numCandlesticks = 0;
			for each(Recognizer ^ lr in listOfRecognizers)
			{
				if (lr->patternName == selectedPattern)
				{
					numCandlesticks = lr->patternLength;
				}
			}

			if (numCandlesticks == 1) {
				rectangle->Width = 1;
				rectangle->Height = (scs->Range);
				rectangle->X = i + 0.5;
				rectangle->Y = scs->Low;
			}
			else if (numCandlesticks == 2) {
				if (i == boundListOfSmartCandlesticks->Count - 1) { break; }
				SmartCandlestick^ scsNext = boundListOfSmartCandlesticks[i + 1];
				rectangle->Width = 2;
				rectangle->Height = Math::Max(scs->High, scsNext->High) - Math::Min(scs->Low, scsNext->Low);
				rectangle->X = i + 0.5;
				rectangle->Y = Math::Min(scs->Low, scsNext->Low);
			}
			else if (numCandlesticks == 3) {
				if (i ==0 || i == boundListOfSmartCandlesticks->Count - 1) { break; }
				SmartCandlestick^ scsNext = boundListOfSmartCandlesticks[i + 1];
				SmartCandlestick^ scsPrev = boundListOfSmartCandlesticks[i - 1];
				rectangle->Width = 3;
				rectangle->X = i - 0.5;
				double low = Math::Min(scs->Low, scsNext->Low);
				low = Math::Min(low, scsPrev->Low);
				double high = Math::Max(scs->High, scsNext->High);
				high = Math::Max(high, scsPrev->High);
				rectangle->Height = high - low;
				rectangle->Y = low;
			}
			// Add the annotation to the chart
			chart_OHLCV->Annotations->Add(rectangle);
		}
	}
}

/// <summary>
/// Initlializes the member variable listOfRecognizers with the Recognizers
/// </summary>
/// <returns>Void</returns>
Void Form_StockPicker::initializeRecognizers() {
	// Initialize the list of recognizers
	listOfRecognizers = gcnew List<Recognizer^>();

	// Add each recognizer to the list
	listOfRecognizers->Add(gcnew Recognizer_Bullish());
	listOfRecognizers->Add(gcnew Recognizer_Bearish());
	listOfRecognizers->Add(gcnew Recognizer_Neutral());
	listOfRecognizers->Add(gcnew Recognizer_Marubozu());
	listOfRecognizers->Add(gcnew Recognizer_Hammer());
	listOfRecognizers->Add(gcnew Recognizer_Doji());
	listOfRecognizers->Add(gcnew Recognizer_DragonflyDoji());
	listOfRecognizers->Add(gcnew Recognizer_GravestoneDoji());
	listOfRecognizers->Add(gcnew Recognizer_BullishEngulfing());
	listOfRecognizers->Add(gcnew Recognizer_BearishEngulfing());
	listOfRecognizers->Add(gcnew Recognizer_BullishHarami());
	listOfRecognizers->Add(gcnew Recognizer_BearishHarami());
	listOfRecognizers->Add(gcnew Recognizer_Peak());
	listOfRecognizers->Add(gcnew Recognizer_Valley());
	
	// Fill comboBox
	for each (Recognizer^ recognizer in listOfRecognizers) {
		comboBox_Patterns->Items->Add(recognizer->patternName);
	}
}