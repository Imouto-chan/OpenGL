#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{



	public:

	public:

	public:

		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static bool resetLightPos = false;
		static bool resetMonkeyPos = false;
		static bool radioMoveLightValue = true;
		static bool radioColorPositionValue = false;
		static bool radioCubesToSphereValue = false;
		static int specularStrength = 4;
		static int specularRedChannel = 100;
		static int specularGreenChannel = 100;
		static int specularBlueChannel = 100;

	public: System::Windows::Forms::RadioButton^ radioMoveLight;
	public: System::Windows::Forms::RadioButton^ radioColorPosition;
	public: System::Windows::Forms::RadioButton^ radioCubesToSphere;
	public:

	public:


	private: System::Windows::Forms::Button^ btnResetLightPosition;
	private: System::Windows::Forms::TrackBar^ barSpecularStrength;
	private: System::Windows::Forms::TrackBar^ barSpecularRedChannel;
	private: System::Windows::Forms::TrackBar^ barSpecularGreenChannel;
	private: System::Windows::Forms::TrackBar^ barSpecularBlueChannel;



	private: System::Windows::Forms::Button^ btnResetMonkeyPosition;





	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ lblSpecularStrength;
	private: System::Windows::Forms::Label^ lblSpecularRedChannel;
	private: System::Windows::Forms::Label^ lblSpecularGreenChannel;
	private: System::Windows::Forms::Label^ lblSpecularBlueChannel;

		   static bool RenderBlueChannel;

	public:
		ToolWindow(void)
		{
			InitializeComponent();
			//RenderRedChannel = checkBoxRedChannel->Checked;
			//RenderGreenChannel = checkBoxGreenChannel->Checked;
			//RenderBlueChannel = checkBoxBlueChannel->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->radioMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioColorPosition = (gcnew System::Windows::Forms::RadioButton());
			this->radioCubesToSphere = (gcnew System::Windows::Forms::RadioButton());
			this->btnResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->barSpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->barSpecularRedChannel = (gcnew System::Windows::Forms::TrackBar());
			this->barSpecularGreenChannel = (gcnew System::Windows::Forms::TrackBar());
			this->barSpecularBlueChannel = (gcnew System::Windows::Forms::TrackBar());
			this->btnResetMonkeyPosition = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->lblSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->lblSpecularRedChannel = (gcnew System::Windows::Forms::Label());
			this->lblSpecularGreenChannel = (gcnew System::Windows::Forms::Label());
			this->lblSpecularBlueChannel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularRedChannel))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularGreenChannel))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularBlueChannel))->BeginInit();
			this->SuspendLayout();
			// 
			// radioMoveLight
			// 
			this->radioMoveLight->AutoSize = true;
			this->radioMoveLight->Checked = true;
			this->radioMoveLight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioMoveLight->Location = System::Drawing::Point(13, 13);
			this->radioMoveLight->Name = L"radioMoveLight";
			this->radioMoveLight->Size = System::Drawing::Size(88, 17);
			this->radioMoveLight->TabIndex = 0;
			this->radioMoveLight->TabStop = true;
			this->radioMoveLight->Text = L"Move Light";
			this->radioMoveLight->UseVisualStyleBackColor = true;
			this->radioMoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioMoveLight_CheckedChanged);
			// 
			// radioColorPosition
			// 
			this->radioColorPosition->AutoSize = true;
			this->radioColorPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioColorPosition->Location = System::Drawing::Point(13, 281);
			this->radioColorPosition->Name = L"radioColorPosition";
			this->radioColorPosition->Size = System::Drawing::Size(121, 17);
			this->radioColorPosition->TabIndex = 1;
			this->radioColorPosition->Text = L"Color By Position";
			this->radioColorPosition->UseVisualStyleBackColor = true;
			this->radioColorPosition->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioColorPosition_CheckedChanged);
			// 
			// radioCubesToSphere
			// 
			this->radioCubesToSphere->AutoSize = true;
			this->radioCubesToSphere->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->radioCubesToSphere->Location = System::Drawing::Point(13, 353);
			this->radioCubesToSphere->Name = L"radioCubesToSphere";
			this->radioCubesToSphere->Size = System::Drawing::Size(158, 17);
			this->radioCubesToSphere->TabIndex = 2;
			this->radioCubesToSphere->Text = L"Move Cubes To Sphere";
			this->radioCubesToSphere->UseVisualStyleBackColor = true;
			this->radioCubesToSphere->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioCubesToSphere_CheckedChanged);
			// 
			// btnResetLightPosition
			// 
			this->btnResetLightPosition->Location = System::Drawing::Point(47, 37);
			this->btnResetLightPosition->Name = L"btnResetLightPosition";
			this->btnResetLightPosition->Size = System::Drawing::Size(124, 23);
			this->btnResetLightPosition->TabIndex = 3;
			this->btnResetLightPosition->Text = L"Reset Light Position";
			this->btnResetLightPosition->UseVisualStyleBackColor = true;
			this->btnResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::btnResetLightPosition_Click);
			// 
			// barSpecularStrength
			// 
			this->barSpecularStrength->Location = System::Drawing::Point(117, 70);
			this->barSpecularStrength->Maximum = 128;
			this->barSpecularStrength->Minimum = 1;
			this->barSpecularStrength->Name = L"barSpecularStrength";
			this->barSpecularStrength->Size = System::Drawing::Size(316, 45);
			this->barSpecularStrength->TabIndex = 4;
			this->barSpecularStrength->Value = 4;
			this->barSpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::barSpecularStrength_Scroll);
			// 
			// barSpecularRedChannel
			// 
			this->barSpecularRedChannel->Location = System::Drawing::Point(117, 121);
			this->barSpecularRedChannel->Maximum = 300;
			this->barSpecularRedChannel->Name = L"barSpecularRedChannel";
			this->barSpecularRedChannel->Size = System::Drawing::Size(316, 45);
			this->barSpecularRedChannel->TabIndex = 5;
			this->barSpecularRedChannel->Value = 100;
			this->barSpecularRedChannel->Scroll += gcnew System::EventHandler(this, &ToolWindow::barSpecularRedChannel_Scroll);
			// 
			// barSpecularGreenChannel
			// 
			this->barSpecularGreenChannel->Location = System::Drawing::Point(117, 172);
			this->barSpecularGreenChannel->Maximum = 300;
			this->barSpecularGreenChannel->Name = L"barSpecularGreenChannel";
			this->barSpecularGreenChannel->Size = System::Drawing::Size(316, 45);
			this->barSpecularGreenChannel->TabIndex = 6;
			this->barSpecularGreenChannel->Value = 100;
			this->barSpecularGreenChannel->Scroll += gcnew System::EventHandler(this, &ToolWindow::barSpecularGreenChannel_Scroll);
			// 
			// barSpecularBlueChannel
			// 
			this->barSpecularBlueChannel->Location = System::Drawing::Point(117, 224);
			this->barSpecularBlueChannel->Maximum = 300;
			this->barSpecularBlueChannel->Name = L"barSpecularBlueChannel";
			this->barSpecularBlueChannel->Size = System::Drawing::Size(316, 45);
			this->barSpecularBlueChannel->TabIndex = 7;
			this->barSpecularBlueChannel->Value = 100;
			this->barSpecularBlueChannel->Scroll += gcnew System::EventHandler(this, &ToolWindow::barSpecularBlueChannel_Scroll);
			// 
			// btnResetMonkeyPosition
			// 
			this->btnResetMonkeyPosition->Location = System::Drawing::Point(47, 313);
			this->btnResetMonkeyPosition->Name = L"btnResetMonkeyPosition";
			this->btnResetMonkeyPosition->Size = System::Drawing::Size(137, 23);
			this->btnResetMonkeyPosition->TabIndex = 8;
			this->btnResetMonkeyPosition->Text = L"Reset Suzzane Position";
			this->btnResetMonkeyPosition->UseVisualStyleBackColor = true;
			this->btnResetMonkeyPosition->Click += gcnew System::EventHandler(this, &ToolWindow::btnResetMonkeyPosition_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 70);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Specular Strength";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 121);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Specular Color";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(96, 121);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(15, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"R";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(96, 172);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"G";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(99, 224);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"B";
			// 
			// lblSpecularStrength
			// 
			this->lblSpecularStrength->AutoSize = true;
			this->lblSpecularStrength->Location = System::Drawing::Point(440, 70);
			this->lblSpecularStrength->Name = L"lblSpecularStrength";
			this->lblSpecularStrength->Size = System::Drawing::Size(13, 13);
			this->lblSpecularStrength->TabIndex = 14;
			this->lblSpecularStrength->Text = L"4";
			// 
			// lblSpecularRedChannel
			// 
			this->lblSpecularRedChannel->AutoSize = true;
			this->lblSpecularRedChannel->Location = System::Drawing::Point(440, 121);
			this->lblSpecularRedChannel->Name = L"lblSpecularRedChannel";
			this->lblSpecularRedChannel->Size = System::Drawing::Size(28, 13);
			this->lblSpecularRedChannel->TabIndex = 15;
			this->lblSpecularRedChannel->Text = L"1.00";
			// 
			// lblSpecularGreenChannel
			// 
			this->lblSpecularGreenChannel->AutoSize = true;
			this->lblSpecularGreenChannel->Location = System::Drawing::Point(443, 172);
			this->lblSpecularGreenChannel->Name = L"lblSpecularGreenChannel";
			this->lblSpecularGreenChannel->Size = System::Drawing::Size(28, 13);
			this->lblSpecularGreenChannel->TabIndex = 16;
			this->lblSpecularGreenChannel->Text = L"1.00";
			// 
			// lblSpecularBlueChannel
			// 
			this->lblSpecularBlueChannel->AutoSize = true;
			this->lblSpecularBlueChannel->Location = System::Drawing::Point(443, 224);
			this->lblSpecularBlueChannel->Name = L"lblSpecularBlueChannel";
			this->lblSpecularBlueChannel->Size = System::Drawing::Size(28, 13);
			this->lblSpecularBlueChannel->TabIndex = 17;
			this->lblSpecularBlueChannel->Text = L"1.00";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(479, 413);
			this->Controls->Add(this->lblSpecularBlueChannel);
			this->Controls->Add(this->lblSpecularGreenChannel);
			this->Controls->Add(this->lblSpecularRedChannel);
			this->Controls->Add(this->lblSpecularStrength);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnResetMonkeyPosition);
			this->Controls->Add(this->barSpecularBlueChannel);
			this->Controls->Add(this->barSpecularGreenChannel);
			this->Controls->Add(this->barSpecularRedChannel);
			this->Controls->Add(this->barSpecularStrength);
			this->Controls->Add(this->btnResetLightPosition);
			this->Controls->Add(this->radioCubesToSphere);
			this->Controls->Add(this->radioColorPosition);
			this->Controls->Add(this->radioMoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularRedChannel))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularGreenChannel))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barSpecularBlueChannel))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void checkBoxRedChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		//RenderRedChannel = checkBoxRedChannel->Checked;
	}
	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		//RenderGreenChannel = checkBoxGreenChannel->Checked;
	}
	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		//RenderBlueChannel = checkBoxBlueChannel->Checked;
	}
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void barSpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularStrength = barSpecularStrength->Value;
		lblSpecularStrength->Text = barSpecularStrength->Value.ToString();
	}

	private: System::Void barSpecularRedChannel_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularRedChannel = barSpecularRedChannel->Value;
		lblSpecularRedChannel->Text = ((float)barSpecularRedChannel->Value / 100).ToString();
	}

	private: System::Void barSpecularGreenChannel_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularGreenChannel = barSpecularGreenChannel->Value;
		lblSpecularGreenChannel->Text = ((float)barSpecularGreenChannel->Value / 100).ToString();
	}

	private: System::Void barSpecularBlueChannel_Scroll(System::Object^ sender, System::EventArgs^ e) {
		specularBlueChannel = barSpecularBlueChannel->Value;
		lblSpecularBlueChannel->Text = ((float)barSpecularBlueChannel->Value / 100).ToString();
	}
private: System::Void radioMoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	radioMoveLightValue = radioMoveLight->Checked;
	radioColorPositionValue = false;
	radioCubesToSphereValue = false;
}
private: System::Void radioColorPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	radioColorPositionValue = radioColorPosition->Checked;
	radioMoveLightValue = false;
	radioCubesToSphereValue = false;
}
private: System::Void radioCubesToSphere_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	radioCubesToSphereValue = radioCubesToSphere->Checked;
	radioMoveLightValue = false;
	radioColorPositionValue = false;
}
private: System::Void btnResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {
	resetLightPos = true;
}
private: System::Void btnResetMonkeyPosition_Click(System::Object^ sender, System::EventArgs^ e) {
	resetMonkeyPos = true;
}
};
}
