#pragma once
#include "Candlestick.h"
#include "SmartCandlestick.h"
#include "Recognizer.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form_StockPicker
	/// </summary>
	public ref class Form_StockPicker : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_Start;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_End;
	private: System::Windows::Forms::Label^ label_Start;
	private: System::Windows::Forms::Label^ label_End;
	private: System::Windows::Forms::Label^ label_ComboBox;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_OHLCV;
	private: System::Windows::Forms::Button^ button_UpdatePicker;

	// Member variables
	private:List<Candlestick^>^ listOfCandlesticks;
	private:List<SmartCandlestick^>^ listOfSmartCandlesticks;
	private:BindingList<Candlestick^>^ boundListOfCandlesticks;
	private: List<Recognizer^>^ listOfRecognizers;
	private: System::Windows::Forms::ComboBox^ comboBox_Patterns;
	private: BindingList<SmartCandlestick^>^ boundListOfSmartCandlesticks;

	public:
		Form_StockPicker(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			listOfCandlesticks = gcnew List<Candlestick^>(1024);
			listOfSmartCandlesticks = gcnew List<SmartCandlestick^>(1024);
			initializeRecognizers();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_StockPicker()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_StockPicker;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_stockPicker;



	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea7 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea8 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button_StockPicker = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_stockPicker = (gcnew System::Windows::Forms::OpenFileDialog());
			this->dateTimePicker_Start = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_End = (gcnew System::Windows::Forms::DateTimePicker());
			this->label_Start = (gcnew System::Windows::Forms::Label());
			this->label_End = (gcnew System::Windows::Forms::Label());
			this->chart_OHLCV = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button_UpdatePicker = (gcnew System::Windows::Forms::Button());
			this->comboBox_Patterns = (gcnew System::Windows::Forms::ComboBox());
			this->label_ComboBox = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_OHLCV))->BeginInit();
			this->SuspendLayout();
			// 
			// button_StockPicker
			// 
			this->button_StockPicker->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button_StockPicker->Font = (gcnew System::Drawing::Font(L"Roboto", 14));
			this->button_StockPicker->Location = System::Drawing::Point(843, 176);
			this->button_StockPicker->Margin = System::Windows::Forms::Padding(2);
			this->button_StockPicker->Name = L"button_StockPicker";
			this->button_StockPicker->Size = System::Drawing::Size(185, 49);
			this->button_StockPicker->TabIndex = 0;
			this->button_StockPicker->Text = L"Pick Ticker";
			this->button_StockPicker->UseVisualStyleBackColor = false;
			this->button_StockPicker->Click += gcnew System::EventHandler(this, &Form_StockPicker::button_StockPicker_Click);
			// 
			// openFileDialog_stockPicker
			// 
			this->openFileDialog_stockPicker->FileName = L"*.csv";
			this->openFileDialog_stockPicker->Filter = L"All Files|*.CSV|Monthly|*-Month.CSV|Weekly|*-Week.CSV|Daily|*-Day.CSV";
			this->openFileDialog_stockPicker->Multiselect = true;
			this->openFileDialog_stockPicker->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_StockPicker::openFileDialog_stockPicker_FileOk);
			// 
			// dateTimePicker_Start
			// 
			this->dateTimePicker_Start->Location = System::Drawing::Point(843, 39);
			this->dateTimePicker_Start->Margin = System::Windows::Forms::Padding(2);
			this->dateTimePicker_Start->Name = L"dateTimePicker_Start";
			this->dateTimePicker_Start->Size = System::Drawing::Size(216, 20);
			this->dateTimePicker_Start->TabIndex = 2;
			this->dateTimePicker_Start->Value = System::DateTime(2022, 1, 1, 0, 0, 0, 0);
			// 
			// dateTimePicker_End
			// 
			this->dateTimePicker_End->Location = System::Drawing::Point(843, 108);
			this->dateTimePicker_End->Margin = System::Windows::Forms::Padding(2);
			this->dateTimePicker_End->Name = L"dateTimePicker_End";
			this->dateTimePicker_End->Size = System::Drawing::Size(216, 20);
			this->dateTimePicker_End->TabIndex = 3;
			this->dateTimePicker_End->Value = System::DateTime(2024, 1, 1, 0, 0, 0, 0);
			// 
			// label_Start
			// 
			this->label_Start->AutoSize = true;
			this->label_Start->BackColor = System::Drawing::SystemColors::Control;
			this->label_Start->Location = System::Drawing::Point(840, 22);
			this->label_Start->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_Start->Name = L"label_Start";
			this->label_Start->Size = System::Drawing::Size(61, 15);
			this->label_Start->TabIndex = 4;
			this->label_Start->Text = L"Start Date";
			// 
			// label_End
			// 
			this->label_End->AutoSize = true;
			this->label_End->Location = System::Drawing::Point(840, 91);
			this->label_End->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_End->Name = L"label_End";
			this->label_End->Size = System::Drawing::Size(58, 15);
			this->label_End->TabIndex = 6;
			this->label_End->Text = L"End Date";
			// 
			// chart_OHLCV
			// 
			chartArea7->AxisX->LabelStyle->Enabled = false;
			chartArea7->AxisX->LabelStyle->IsEndLabelVisible = false;
			chartArea7->AxisX->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Stacked;
			chartArea7->AxisY->IsStartedFromZero = false;
			chartArea7->AxisY2->IsStartedFromZero = false;
			chartArea7->Name = L"ChartArea_OHLC";
			chartArea8->AlignWithChartArea = L"ChartArea_OHLC";
			chartArea8->Name = L"ChartArea_Volume";
			this->chart_OHLCV->ChartAreas->Add(chartArea7);
			this->chart_OHLCV->ChartAreas->Add(chartArea8);
			legend4->Enabled = false;
			legend4->Name = L"Legend1";
			this->chart_OHLCV->Legends->Add(legend4);
			this->chart_OHLCV->Location = System::Drawing::Point(11, 11);
			this->chart_OHLCV->Margin = System::Windows::Forms::Padding(2);
			this->chart_OHLCV->Name = L"chart_OHLCV";
			series7->ChartArea = L"ChartArea_OHLC";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series7->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
			series7->IsXValueIndexed = true;
			series7->Legend = L"Legend1";
			series7->Name = L"Series_OHLC";
			series7->XValueMember = L"Date";
			series7->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series7->YValueMembers = L"High,Low,Open,Close";
			series7->YValuesPerPoint = 4;
			series7->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series8->ChartArea = L"ChartArea_Volume";
			series8->IsXValueIndexed = true;
			series8->Legend = L"Legend1";
			series8->Name = L"Series_Volume";
			series8->XValueMember = L"Date";
			series8->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			series8->YValueMembers = L"Volume";
			series8->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt64;
			this->chart_OHLCV->Series->Add(series7);
			this->chart_OHLCV->Series->Add(series8);
			this->chart_OHLCV->Size = System::Drawing::Size(814, 446);
			this->chart_OHLCV->TabIndex = 7;
			this->chart_OHLCV->Text = L"chart_OHLCV";
			// 
			// button_UpdatePicker
			// 
			this->button_UpdatePicker->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button_UpdatePicker->Font = (gcnew System::Drawing::Font(L"Roboto", 14));
			this->button_UpdatePicker->Location = System::Drawing::Point(843, 239);
			this->button_UpdatePicker->Margin = System::Windows::Forms::Padding(2);
			this->button_UpdatePicker->Name = L"button_UpdatePicker";
			this->button_UpdatePicker->Size = System::Drawing::Size(185, 50);
			this->button_UpdatePicker->TabIndex = 8;
			this->button_UpdatePicker->Text = L"Update";
			this->button_UpdatePicker->UseVisualStyleBackColor = false;
			this->button_UpdatePicker->Click += gcnew System::EventHandler(this, &Form_StockPicker::button_UpdatePicker_Click);
			// 
			// comboBox_Patterns
			// 
			this->comboBox_Patterns->FormattingEnabled = true;
			this->comboBox_Patterns->Location = System::Drawing::Point(843, 336);
			this->comboBox_Patterns->Name = L"comboBox_Patterns";
			this->comboBox_Patterns->Size = System::Drawing::Size(189, 21);
			this->comboBox_Patterns->TabIndex = 9;
			this->comboBox_Patterns->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_StockPicker::comboBox_Patterns_SelectedIndexChanged);
			// 
			// label_ComboBox
			// 
			this->label_ComboBox->AutoSize = true;
			this->label_ComboBox->Location = System::Drawing::Point(840, 318);
			this->label_ComboBox->Name = L"label_ComboBox";
			this->label_ComboBox->Size = System::Drawing::Size(149, 15);
			this->label_ComboBox->TabIndex = 10;
			this->label_ComboBox->Text = L"Select Candlestick Pattern";
			// 
			// Form_StockPicker
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1064, 474);
			this->Controls->Add(this->label_ComboBox);
			this->Controls->Add(this->comboBox_Patterns);
			this->Controls->Add(this->button_UpdatePicker);
			this->Controls->Add(this->chart_OHLCV);
			this->Controls->Add(this->label_End);
			this->Controls->Add(this->label_Start);
			this->Controls->Add(this->dateTimePicker_End);
			this->Controls->Add(this->dateTimePicker_Start);
			this->Controls->Add(this->button_StockPicker);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Form_StockPicker";
			this->Text = L"Form_StockPicker";
			this->Load += gcnew System::EventHandler(this, &Form_StockPicker::Form_StockPicker_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_OHLCV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region
	/// <summary>
	/// Loads the form
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	/// <returns>Void</returns>
	private: System::Void Form_StockPicker_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	// Methods and event handlers
	
	/// <summary>
	/// Opens a fileDialog
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	/// <returns>Void</returns>
	private: System::Void button_StockPicker_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Open file explorer
		openFileDialog_stockPicker->ShowDialog();
	}

	/// <summary>
	/// Creates a dataGridView and a Chart based using data on the file selected in the openFileDialog
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	/// <returns>Void</returns>
	private: System::Void openFileDialog_stockPicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	
	/// <summary>
	/// Updates the boundListOfCandlesticks based on the newly specified date range
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	/// <returns>Void</returns>
	private: System::Void button_UpdatePicker_Click(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// This reads data from the file.
	/// </summary>
	/// <param name="filePath">This is the path to the file to be read</param>
	/// <returns>This will return a list of candlesticks</returns>
	public: List<SmartCandlestick^>^ ReadCandleStickDataFromFile(String^ filePath);

	/// <summary>
	/// Calls ReadCandleStickDataFromFile by passing in the filepath from the openFileDialog
	/// </summary>
	/// <returns>Void</returns>
	public: Void ReadCandleStickDataFromFile();	

	/// <summary>
	/// Filters a listOfCandlesticks according to the date range specified by the dateTimePickers
	/// </summary>
	/// <param name="loc">listOfCandlesticks that has to be filtered</param>
	/// <returnsA boundListOfCandlesticks></returns>
	public: BindingList<SmartCandlestick^>^ filterCandlesticks(List<SmartCandlestick^>^ losc);

	/// <summary>
	/// Calls filterCandlesticks which filters a listOfCandlesticks according to the date range specified by the dateTimePickers
	/// </summary>
	/// <returns>Void</returns>
	public: Void filterCandlesticks();
	
	/// <summary>
	/// Normalizes the y-axis for chartArea_OHLC according to the maximum high and minimum low of the candlesticks
	/// </summary>
	/// <param name="bloc"></param>
	/// <returns>Void</returns>
	public: Void normalizeChart(BindingList<SmartCandlestick^>^ blosc);

	/// <summary>
	/// Calls normalizeChart which normalizes the y-axis for chartArea_OHLC according to the maximum high and minimum low of the candlesticks
	/// </summary>
	/// <returns>Void</returns>
	public: Void normalizeChart();


	/// <summary>
	/// Displays a chart using the boundListOfCandlesticks. The chart shows the candlesticks along with their volume
	/// </summary>
	/// <param name="bloc"></param>
	/// <returns>Void</returns>
	public: Void displayChart(BindingList<SmartCandlestick^>^ blosc);

	/// <summary>
	/// Calls displayChart which displays a chart using the boundListOfCandlesticks
	/// </summary>
	/// <returns>Void</returns>
	public: Void displayChart();

	/// <summary>
	/// Initializes the comboBox with the patterns found in the boundListOfCandlesticks
	/// </summary>
	/// <param name="blosc"></param>
	/// <returns>Void</returns>
	public: Void initializeComboBox(BindingList<SmartCandlestick^>^ blosc);


	/// <summary>
	/// Event handler for the comboBox.
	/// Adds arrow annotations to the chart according to the pattern selected in the comboBox
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	/// <returns>Void</returns>
	public: Void comboBox_Patterns_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	
	/// <summary>
	/// Initlializes the member variable listOfRecognizers with the Recognizers
	/// </summary>
	/// <returns>Void</returns>
	public: Void initializeRecognizers();

#pragma endregion
};


}
