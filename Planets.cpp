#include "Planetarium.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Data::SqlClient;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Pr8::Planetarium form;
	Application::Run(% form);

SqlConnection^ conn = gcnew SqlConnection("Data Source=your_server;Initial Catalog=your_db;Integrated Security=True;");