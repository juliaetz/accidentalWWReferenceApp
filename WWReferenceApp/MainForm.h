#pragma once
#include "song.h"
#include <msclr\marshal_cppstd.h>

namespace WWReferenceApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		Playlist *playlist;
		MainForm(void)
		{
			InitializeComponent();
			
			// creating the songs vector for the playlist, for this app it will be the
			// songs in Will Wood's "The Normal Album"
			vector<string> songFiles;
			songFiles.push_back(".//WWFiles//suburbia.txt");
			songFiles.push_back(".//WWFiles//2econd-2ight-2eer.txt");
			songFiles.push_back(".//WWFiles//laplaces-angel.txt");
			songFiles.push_back(".//WWFiles//i-me-myself.txt");
			songFiles.push_back(".//WWFiles//wbtta.txt");
			songFiles.push_back(".//WWFiles//outliars-and-hyppocrates.txt");
			songFiles.push_back(".//WWFiles//blackboxwarrior.txt");
			songFiles.push_back(".//WWFiles//marsha.txt");
			songFiles.push_back(".//WWFiles//love-me-normally.txt");
			songFiles.push_back(".//WWFiles//memento-mori.txt");
			playlist = new Playlist(songFiles);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lbStr;
	protected:

	private: System::Windows::Forms::TextBox^ tbUserStr;

	private: System::Windows::Forms::Label^ lbSearchResult;
	private: System::Windows::Forms::Button^ btnClear;


	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lbStr = (gcnew System::Windows::Forms::Label());
			this->tbUserStr = (gcnew System::Windows::Forms::TextBox());
			this->lbSearchResult = (gcnew System::Windows::Forms::Label());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lbStr
			// 
			this->lbStr->AutoSize = true;
			this->lbStr->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbStr->Location = System::Drawing::Point(12, 23);
			this->lbStr->Name = L"lbStr";
			this->lbStr->Size = System::Drawing::Size(215, 32);
			this->lbStr->TabIndex = 0;
			this->lbStr->Text = L"Begin writing here";
			this->lbStr->Click += gcnew System::EventHandler(this, &MainForm::lbStr_Click);
			// 
			// tbUserStr
			// 
			this->tbUserStr->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbUserStr->Location = System::Drawing::Point(12, 70);
			this->tbUserStr->Name = L"tbUserStr";
			this->tbUserStr->Size = System::Drawing::Size(707, 39);
			this->tbUserStr->TabIndex = 1;
			this->tbUserStr->TextChanged += gcnew System::EventHandler(this, &MainForm::tbUserStr_TextChanged);
			// 
			// lbSearchResult
			// 
			this->lbSearchResult->AutoSize = true;
			this->lbSearchResult->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbSearchResult->Location = System::Drawing::Point(98, 129);
			this->lbSearchResult->Name = L"lbSearchResult";
			this->lbSearchResult->Size = System::Drawing::Size(79, 32);
			this->lbSearchResult->TabIndex = 3;
			this->lbSearchResult->Text = L"label2";
			this->lbSearchResult->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// btnClear
			// 
			this->btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btnClear->BackColor = System::Drawing::Color::White;
			this->btnClear->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClear->Location = System::Drawing::Point(18, 454);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(135, 53);
			this->btnClear->TabIndex = 4;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = false;
			this->btnClear->Click += gcnew System::EventHandler(this, &MainForm::btnClear_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::RosyBrown;
			this->ClientSize = System::Drawing::Size(742, 519);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->lbSearchResult);
			this->Controls->Add(this->tbUserStr);
			this->Controls->Add(this->lbStr);
			this->MinimumSize = System::Drawing::Size(750, 575);
			this->Name = L"MainForm";
			this->Text = L"Accidental WW Reference";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
		// clears the user text when button is pressend
		this->tbUserStr->Text = "";
		this->tbUserStr->ReadOnly = false;
		this->lbSearchResult->Text = "";
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		// initilizes app UI
		this->lbSearchResult->Text = "";
	}
	private: System::Void tbUserStr_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// when user text is edited, the app cross references the new user inputed 
		// string with the album lyrics to detects any accidental refrences (substrings
		// of 5+ common words) are made by the user
		String^ userStr = this->tbUserStr->Text;
		msclr::interop::marshal_context context;
		std::string strToSearch = context.marshal_as<std::string>(userStr);

		
		String^ result = context.marshal_as<String^>(playlist->wwReference(strToSearch));
		// a message is displayed only if an accidental reference is detected
		if (result != "no") {
			this->lbSearchResult->Text = result;
			this->tbUserStr->ReadOnly = true;
		}
	}
private: System::Void lbStr_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
