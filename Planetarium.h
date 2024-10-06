#pragma once

namespace Planetarium {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            //
            // Add initialization code here
            //
            conn = gcnew SqlConnection("Data Source=your_server;Initial Catalog=your_db;Integrated Security=True;");
            LoadData();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // Form components
        DataGridView^ dataGridView1;
        Button^ btnAdd;
        Button^ btnUpdate;
        Button^ btnDelete;
        TextBox^ textBoxName;
        TextBox^ textBoxDistance;
        TextBox^ textBoxDiameter;
        TextBox^ textBoxType;
        TextBox^ textBoxYear;
        MenuStrip^ menuStrip1;
        ToolStripMenuItem^ aboutToolStripMenuItem;
        ToolStripMenuItem^ exitToolStripMenuItem;

        SqlConnection^ conn;
        int selectedID;

        // Method for loading data into DataGridView
        void LoadData() {
            String^ query = "SELECT * FROM Planets";
            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, conn);
            DataTable^ table = gcnew DataTable();
            adapter->Fill(table);
            dataGridView1->DataSource = table;
        }

        // Method for adding a new planet
        void AddPlanet() {
            String^ query = "INSERT INTO Planets (Name, DistanceFromEarth, Diameter, Type, DiscoveryYear) VALUES (@name, @distance, @diameter, @type, @year)";
            SqlCommand^ cmd = gcnew SqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@name", textBoxName->Text);
            cmd->Parameters->AddWithValue("@distance", Convert::ToDouble(textBoxDistance->Text));
            cmd->Parameters->AddWithValue("@diameter", Convert::ToDouble(textBoxDiameter->Text));
            cmd->Parameters->AddWithValue("@type", textBoxType->Text);
            cmd->Parameters->AddWithValue("@year", Convert::ToInt32(textBoxYear->Text));

            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
            LoadData();
        }

        // Method for updating a planet
        void UpdatePlanet(int id) {
            String^ query = "UPDATE Planets SET Name=@name, DistanceFromEarth=@distance, Diameter=@diameter, Type=@type, DiscoveryYear=@year WHERE ID=@id";
            SqlCommand^ cmd = gcnew SqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@name", textBoxName->Text);
            cmd->Parameters->AddWithValue("@distance", Convert::ToDouble(textBoxDistance->Text));
            cmd->Parameters->AddWithValue("@diameter", Convert::ToDouble(textBoxDiameter->Text));
            cmd->Parameters->AddWithValue("@type", textBoxType->Text);
            cmd->Parameters->AddWithValue("@year", Convert::ToInt32(textBoxYear->Text));
            cmd->Parameters->AddWithValue("@id", id);

            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
            LoadData();
        }

        // Method for deleting a planet
        void DeletePlanet(int id) {
            String^ query = "DELETE FROM Planets WHERE ID=@id";
            SqlCommand^ cmd = gcnew SqlCommand(query, conn);
            cmd->Parameters->AddWithValue("@id", id);

            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
            LoadData();
        }

    private:
        void InitializeComponent(void)
        {
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnUpdate = (gcnew System::Windows::Forms::Button());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->textBoxName = (gcnew System::Windows::Forms::TextBox());
            this->textBoxDistance = (gcnew System::Windows::Forms::TextBox());
            this->textBoxDiameter = (gcnew System::Windows::Forms::TextBox());
            this->textBoxType = (gcnew System::Windows::Forms::TextBox());
            this->textBoxYear = (gcnew System::Windows::Forms::TextBox());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            // 
            // dataGridView1
            // 
            this->dataGridView1->Location = System::Drawing::Point(12, 180);
            this->dataGridView1->Size = System::Drawing::Size(600, 200);
            // 
            // btnAdd
            // 
            this->btnAdd->Text = "Додати";
            this->btnAdd->Location = System::Drawing::Point(12, 140);
            this->btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
            // 
            // btnUpdate
            // 
            this->btnUpdate->Text = "Оновити";
            this->btnUpdate->Location = System::Drawing::Point(90, 140);
            this->btnUpdate->Click += gcnew System::EventHandler(this, &MainForm::btnUpdate_Click);
            // 
            // btnDelete
            // 
            this->btnDelete->Text = "Видалити";
            this->btnDelete->Location = System::Drawing::Point(170, 140);
            this->btnDelete->Click += gcnew System::EventHandler(this, &MainForm::btnDelete_Click);
            // 
            // textBoxName
            // 
            this->textBoxName->Location = System::Drawing::Point(12, 30);
            this->textBoxName->PlaceholderText = "Назва планети";
            // 
            // textBoxDistance
            // 
            this->textBoxDistance->Location = System::Drawing::Point(12, 60);
            this->textBoxDistance->PlaceholderText = "Відстань від Землі (св.роки)";
            // 
            // textBoxDiameter
            // 
            this->textBoxDiameter->Location = System::Drawing::Point(12, 90);
            this->textBoxDiameter->PlaceholderText = "Діаметр (км)";
            // 
            // textBoxType
            // 
            this->textBoxType->Location = System::Drawing::Point(200, 30);
            this->textBoxType->PlaceholderText = "Тип планети";
            // 
            // textBoxYear
            // 
            this->textBoxYear->Location = System::Drawing::Point(200, 60);
            this->textBoxYear->PlaceholderText = "Рік відкриття";
            // 
            // menuStrip1
            // 
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->aboutToolStripMenuItem, this->exitToolStripMenuItem });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Size = System::Drawing::Size(800, 24);
            // 
            // aboutToolStripMenuItem
            // 
            this->aboutToolStripMenuItem->Text = "Про програму";
            this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this->exitToolStripMenuItem->Text = "Вихід";
            this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this->ClientSize = System::Drawing::Size(624, 441);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->textBoxName);
            this->Controls->Add(this->textBoxDistance);
            this->Controls->Add(this->textBoxDiameter);
            this->Controls->Add(this->textBoxType);
            this->Controls->Add(this->textBoxYear);
            this->MainMenuStrip = this->menuStrip1;
            this->Controls->Add(this->menuStrip1);
            this->Text = "Інформаційна система Планетарій";
        }

        // Button click event handlers
        void btnAdd_Click(Object^ sender, EventArgs^ e) {
            AddPlanet();
        }

        void btnUpdate_Click(Object^ sender, EventArgs^ e) {
            if (dataGridView1->SelectedRows->Count > 0) {
                selectedID = Convert::ToInt32(dataGridView1->SelectedRows[0]->Cells[0]->Value);
                UpdatePlanet(selectedID);
            }
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (dataGridView1->SelectedRows->Count > 0) {
                selectedID = Convert::ToInt32(dataGridView1->SelectedRows[0]->Cells[0]->Value);
                DeletePlanet(selectedID);
            }
        }

        void aboutToolStripMenuItem_Click(Object^ sender, EventArgs^ e) {
            MessageBox::Show("Інформаційна система Планетарію\nАвтор: Ваше Ім'я", "Про програму");
        }

        void exitToolStripMenuItem_Click(Object^ sender, EventArgs^ e) {
            Application::Exit();
        }
    };
}
