#include "stdafx.h"
#include <conio.h> 
#include <stdio.h> 
#include <iostream> 
#include <cstdlib> 
#include <math.h> 

double binom(double x, const double *eps){
	double k = 1.0 / 3.0;
	__asm{
		mov ecx, eps;

		finit
		fld x;
		fld k;
		fldz;
		fld1;
		fld x;

	WHILE:
		fld st(0);
		fabs;
		fcom qword ptr[ecx];
		fstsw ax;
		sahf;
		fstp st(0);
		jc END;

		fld st(3);
		fld st(3);
		fsub st(1), st(0);
		fld1;
		faddp st(1), st(0);
		fdiv st(1), st(0);
		fxch st(4);
		fstp st(0);
		fmulp st(1), st(0);
		
		fadd st(1), st(0);
		fld st(4);
		fmulp st(1), st(0);
		jmp WHILE;
	END:
		fstp st(0);
	}
}


int main(){
	char* programm = "Programm calculate (1+x)^(1/3)\n";
	char* enterX = "Enter x\n";
	char* enterAcc = "Enter accuracy\n";
	char* frmRes = "(1+(%lf))^(1/3) = %lf\n";
	char* absoluteError = "Absolute error  = %lf\n";
	char *scDoub = "%lf";
	char *errorMes = "x out domain";
	double x = 0;
	double acc = 0.001;
	double res = 0;
	__asm{
	mov		eax, programm		//сообщение о начале работы
		push	eax
		call	printf_s;
	add		esp, 4

		mov		eax, enterX			//Сообщение о вводе x
		push	eax
		call	printf_s;
	add esp, 4

		mov		eax, scDoub			//Считываем x
		lea		ebx, x
		push	ebx
		push	eax
		call	scanf_s;
	add		esp, 8

		//проверка на принадлежнаие к [-1,1]
		finit;
	fld qword ptr x;
	fabs;
	fld1;
	fcomp st(1);
	fstsw ax;
	sahf;
	jb ERROR_M;
		 
		


	mov		eax, enterAcc		//Сообщение о вводе точности
		push	eax
		call	printf_s
		add		esp, 4

		mov		eax, scDoub			//Считываем точность
		lea		ebx, acc
		push	ebx
		push	eax
		call	scanf_s
		add		esp, 8






		lea	eax, acc			//Вычисляем функцию
		push	eax;
		sub esp, 8;
		finit;
		fld qword ptr x;
		fstp qword ptr[esp];
		
		call	binom;
		add		esp, 12
		fst		qword ptr res

		sub		esp, 8				//Выводим результат
		fst		qword ptr[esp]		//Положили res 
		fstp	st(0)
		sub		esp, 8
		fld		x
		fst		qword ptr[esp]		//Положили x 
		fstp	st(0)
		mov		eax, frmRes
		push	eax
		call	printf_s
		add		esp, 20
		jmp FIN;

ERROR_M:
	mov	eax, errorMes;
	push	eax
	call	printf_s;
	add		esp, 4
	FIN:
	}
	double solv = pow((1 + x), (1.0/3.0));

	printf(absoluteError, abs(solv - res));
	system("pause");
}