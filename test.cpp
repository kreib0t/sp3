#include <iostream>
#include <random>
#include <ctime>

using namespace std;

extern "C" {
	
	const int N=10;
	int array[N];
	int maxelem, maxelem_position;
	int tempN = N;
};

int main()
{
	srand(time(0));	

	for(int i=0; i<N; i++) {
		array[i]=rand()%100;
		cout<<array[i]<<" ";
	}
	cout<<"\n";
	
	__asm__(R"(
		.intel_syntax noprefix
		;//{
		mov ecx, 0 ; // адрес элемдля проверки
		mov dl, 0 ; // счетчик
		mov ebx, 0 ; // мах
		loop:
		mov eax, array[ecx] ; // Массив	
		cmp eax, ebx ; // Сравнение
		jg max ; // меньше
		jmp next
		max:
		mov ebx, eax
		mov maxelem_position, dl
		next:
		add ecx, 4
		add dl, 1
		cmp dl, BYTE PTR tempN
		jl loop
		mov maxelem, ebx
		;//}
	)");

	cout<<"Position: "<<maxelem_position+1<<"\n";
	cout<<"Value: "<<maxelem<<"\n";

	return 0;
}
