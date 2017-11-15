// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "cstdlib"
#include "stdio.h"
using namespace std;





	

	int** createMatr(int N){
		
	int base, index;
	
		__asm{
			mov eax, N;
			shl eax, 2;
			push eax;
			call dword ptr malloc;
			mov ecx, [esp]
			shr ecx, 2;
			mov base, eax;

		MATR_CREATE:
			mov index, ecx;
			call dword ptr malloc;
			mov ecx, N;
            
		CYCLE_ZERO:
			mov dword ptr[eax][ecx * 4 - 4], 0;
			loop CYCLE_ZERO;

            mov ecx, index;
			mov ebx, base;
			mov[ebx][ecx * 4 - 4], eax;

			loop MATR_CREATE;

			mov eax, ebx;
			add esp, 4;


		
  
		}
	
	}


void deleteMatr(int** matr, int N){
	__asm{
		
		mov ecx, N;

	CYCLE:
		mov ebx, matr;
		push ecx;
		mov eax, [ebx][ecx * 4 - 4];
		push eax;
		call dword ptr free;
		add esp, 4;
		pop ecx;
		loop CYCLE;

		mov ebx, matr;
		push ebx;
		call dword ptr free;
		add esp, 4;
		
	}

}

int getElem(int**matr,unsigned int N, unsigned int i,unsigned int j){
	char ERRORMESS[] = "index is out of range";
	__asm{
		mov ebx, matr;
		mov ecx, j;
		mov eax, i;
		cmp ecx, N;
		jae ERR;
		cmp eax, N;
		jae ERR;

		mov edx, [ebx][ecx * 4];
		mov ecx, i;		
		mov eax, [edx][ecx * 4];
		jmp FIN;

	ERR:
        lea eax, ERRORMESS;
		push eax;
		call dword ptr printf;
		add esp, 4;
	FIN:
	}

}



void setElem(int**matr, unsigned int N, unsigned int i, unsigned int j,int x){
	char ERRORMESS[] = "index is out of range";
	__asm{
		mov ebx, matr;
		mov ecx, j;
		mov eax, i;
		cmp ecx, N;
		jae ERR;
		cmp eax, N;
		jae ERR;

		mov edx, [ebx][ecx * 4];
		mov ecx, i;
		mov esi, x;
		mov[edx][ecx * 4], esi;
		jmp FIN;

	ERR:
		lea eax, ERRORMESS;
		push eax;
		call dword ptr printf;
		add esp, 4;
	FIN:
	}

}

void  printMatr(int** matr, int N){

	char fmt1[] = "%d ";
	char fmt2[] = "\n";
	__asm{

		mov ebx, matr;				
		mov ecx, N;		
		xor esi, esi;					//esi - номер текущей строчки

		CYCLE_I :
		    cmp esi, N;
		    je END;
			mov edx, [ebx][esi * 4];		//в edx - указатель на текущую строчку
			xor edi, edi;			//edi - номер текущего столбца
			push ebx;
			push esi;
		CYCLE_J :
			cmp edi, N;
			je NEXT;
			push edi;
			push edx;
			mov eax, [edx][edi * 4];
			push eax;
			lea edx, fmt1;
			push edx;
			call dword ptr printf;
			add esp, 8;
			pop edx;
			pop edi;
			inc edi;
			jmp CYCLE_J;
		NEXT :
			lea edi, fmt2;
			push edi;
			call dword ptr printf;
			add esp, 4;
			pop esi;
			pop eax;
			inc esi;
			jmp CYCLE_I;


		END :
	}
}

int counterStr(int** matr, int N){

	
		
	
	int res = 0, sum = 0;  
		__asm{
			  
			mov eax, matr; 
			mov edi, N;  
			mov N, edi;
			xor esi, esi;

			CYCLE_I :
			    cmp esi, N
				je END
				mov sum,0
				mov edx, [eax][esi * 4];
			    xor edi, edi;
				push eax
				 
			CYCLE_J :
				    cmp edi, N;
					je NEXT;
					mov eax, [edx][edi * 4];
					add sum, eax;
					inc edi;
					jmp CYCLE_J;
			
			NEXT :
					mov eax, sum;
					rcr eax, 1;
					jnc EVEN_NUM;
				    mov ebx, res
				    add ebx, 1
				    mov res, ebx
			EVEN_NUM :
			        pop eax
				    inc esi
				    jmp CYCLE_I


			END :



		}
		return res;

}

int main(){
	unsigned int N;
	int **matr = 0;
	int c = 0;
	unsigned int i;
	unsigned int j;
	int x;
	bool fMatrExist = false;
	unsigned int res;

	while (c !=7){

	

	cout << "1 - Create matr(zero matr)" << endl;
	cout << "2 - Delete matr" << endl;
	cout << "3 - Get elem [i,j]" << endl;
	cout << "4 - Set elem [i,j] on x" << endl;
	cout << "5 - Print matr" << endl;
	cout << "6 - Count lin " << endl;
	cout << "7 - Exit" << endl;
	cin >> c;
	
	switch (c)
	{
	case 1:
	{
			  cout << "Write dim matr" << endl;
			  cin >> N;
			  matr = createMatr(N);
			  fMatrExist = true;
			  break;
	}

	case 2:
	{
			  if (fMatrExist == true){
				  deleteMatr(matr, N);

			  }
			  else
			  {
				  cout << "Matr dosn't exist!" << endl;
				 
			  }
			  break;
	}

	case 3:
	{


			  if (fMatrExist == true){
				  cout << "Write i,j through a SPACE" << endl;
				  cin >> i >> j;
				  x = getElem(matr, N, i, j);

			  }
			  else
			  {
				  cout << "Matr dosn't exist!" << endl;
				 
			  }
			  break;
	}

	case 4:
	{
			  if (fMatrExist == true){
				  cout << "Write i,j through a SPACE" << endl;
				  cin >> i >> j;
				  cout << "Write elem x" << endl;
				  cin >> x;
				  setElem(matr, N, i, j, x);

			  }
			  else
			  {
				  cout << "Matr dosn't exist!" << endl;
				 
			  }
			  break;
	}
	case 5:
	{
			  if (fMatrExist == true){
				  printMatr(matr, N);

			  }
			  else
			  {
				  cout << "Matr dosn't exist!" << endl;
				 
			  }
			  break;
	}
	case 6:
	{
			  if (fMatrExist == true){
				  res = counterStr(matr, N);
				  cout << res << endl;


			  }
			  else
			  {
				  cout << "Matr dosn't exist!" << endl;
				  
			  }
			  break;
	}
	case 7:
	{

			  return 0;
	}

	default:
	{
			   cout << "Error" << endl;
			   break;
	}



	}
}
}