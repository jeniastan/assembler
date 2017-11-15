// ConsoleApplication26.cpp: определяет точку входа для консольного приложения
// 

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	const int N=1000;
	int count;
	char inputStr[N];
	char outputStr[N];
	int arrCounter[256];
	char intFormatStr [] = "%d";
	char formatStr[] = "%s";

	__asm{
		lea ebx, arrCounter;
		mov ecx, 256;
	WHILE:
		mov dword ptr[ebx], 0;
		add ebx,4;
		loop WHILE;

		;считываем символы с клавиатуры
		mov aex, N;
push eax;
lea eax, inputStr;
push aex;
call gets_s;
add esp, 8;

lea eax, count;
push eax;
lea eax, intFormatStr;
push eax;
call scanf_s;
add esp, 8;

lea eax, inputStr;
lea ecx, arrCounter;
xor ebx, ebx;

MAIN_CYCLE:
mov bl, [eax];
cmp bl, 0;
je NEXT;
inc dword ptr [ecx] [ebx*4];
inc eax;
jmp MAIN_CYCLE;

NEXT:
mov eax, count;
xor ebx, ebx;
mov edi, ecx; указатель на arrCounter
mov ecx, 256;
lea edx, outputStr;
xor esi, esi;
COUNTER_CYCLE:
cmp [edi][ebx*4], eax;
jne NEXT_CHAR;
mov[edx][esi], bl;
inc esi;
NEXT_CHAR:

add ebx,1;

loop COUNTER_CYCLE;
mov [edx][esi], 0;


mov eax, edx;
push eax;
lea eax, formatStr;
push eax;
call dword ptr printf;
add esp, 8;


}
system ("pause");

}
