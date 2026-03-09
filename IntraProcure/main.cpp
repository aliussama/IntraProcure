#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace IntraProcure;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew LoginForm());
	return 0;
}