#include "stdafx.h"
#include "Form1.h"
#include <ctime>
#include <cstdlib>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew kalkulacka::Form1());
	return 0;
}