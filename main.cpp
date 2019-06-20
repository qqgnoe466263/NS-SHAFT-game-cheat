#include<iostream>
#include<windows.h>
#include<stdio.h>

using namespace std;

int main()
{
	HWND game = FindWindow(NULL, "NS-SHAFT");
	DWORD pid = 0;
	GetWindowThreadProcessId(game, &pid);
	
	HANDLE hgame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	DWORD base = 0x0018FDA0;
	DWORD blood_offset = 0x1170;
	DWORD x_axis_offset = 0x1158;
	DWORD y_axis_offset = 0x115C;
	DWORD buf = 0;
	ReadProcessMemory(hgame, (LPVOID)base, &buf, sizeof(DWORD), 0);
	DWORD blood_add = buf + blood_offset;
	DWORD y_add = buf + y_axis_offset;
	DWORD x_add = buf + x_axis_offset;
	
	int full = 12;
	int y = 0;
	int x = 0;
	POINT p;
	MSG msg;
	system("pause");
	while (1)
	{

		WriteProcessMemory(hgame, (LPVOID)blood_add, &full, sizeof(int), 0);

		Sleep(50);
		GetCursorPos(&p);
		y = p.y % 315;
		x = p.x % 320;

		cout << x << " " << y << endl;
		
		WriteProcessMemory(hgame, (LPVOID)y_add, &y, sizeof(int), 0);
		Sleep(10);
		WriteProcessMemory(hgame, (LPVOID)x_add, &x, sizeof(int), 0);

		Sleep(50);
	}
	system("pause");
	return 0;

}
