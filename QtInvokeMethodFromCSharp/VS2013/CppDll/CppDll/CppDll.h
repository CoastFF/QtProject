// CppDll.h

#pragma once
using namespace System::Reflection;
using namespace System;


__declspec(dllexport) int api_add(int a, int b)
{
	CSharpDll::CSharpClass obj;
	return obj.add(a, b);
}
__declspec(dllexport) void api_substract(int a, int b, int* c)
{
	CSharpDll::CSharpClass obj;
	obj.substract(a, b, *c);	
}
__declspec(dllexport) void api_showBox(const char* content)
{
	CSharpDll::CSharpClass obj;
	String^ str = gcnew String(content);
	obj.showBox(str);
}
