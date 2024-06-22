#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void setTextColor (int color) {
	HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int main()
{
	#define GREEN 10
	#define ORANGE 6
	#define RESET 7

	//set minimum and maximum values of the answer
	int min = 1000, max = 999999;

	// set the clock to nanoseconds
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);

	//gen random number
	int ans;
	int input; 
	srand(time.tv_nsec);
	ans = (rand() % (max - min + 1)) + min;

	//check number of digits
	int nofdigits = 0;
	int temp = ans;
	while (temp > 0)
	{
		temp /= 10;
		nofdigits++;
	}
    int inpdigits = 0;
    
	//allocate memory for the answer array
	int *digits = (int *)malloc(nofdigits * sizeof(int));
	
	//allocate memory for the marker array
	int *marked = (int *)malloc(nofdigits * sizeof(int));
	
	//allocate memory for the input array
	int *trydigits = (int *)malloc(nofdigits * sizeof(int));

	//set the array to memory
	temp = ans;
	for (int i = nofdigits - 1; i >= 0; i--)
	{
		digits[i] = temp % 10;
		temp /= 10;
	}

	printf("Adivine el numero secreto\n\nNumero de digitos = %d\n\nLeyenda: \nverde = posicion y valor correctos \namarillo = valor correcto, posicion erronea \nblanco = valor incorrecto\n", nofdigits);
	//debug print
	/*
	printf("%d\n", ans);
	for (int i = 0; i < nofdigits; i++)
	{
		printf("%d ", digits[i]);
	}
	*/
	printf("\nIntroduzca respuesta \n");
	
	printf("                   ");

inputans:
    input = 0;
    inpdigits = 0;
	scanf("%d", &input);

	//check number of digits
	
	int temp2 = input;
	while (temp2 > 0)
	{
		temp2 /= 10;
		inpdigits++;
	}
	if (inpdigits != nofdigits)
	{
		printf("cantidad de digitos incorrecta \n");
		goto inputans;
	}

	

	//set the array to memory
	temp2 = input;
	for (int j = inpdigits - 1; j >= 0; j--)
	{
		trydigits[j] = temp2 % 10;
		temp2 /= 10;
	}
   
	// set a marker for comparisons
	


	for (int i = 0; i < nofdigits; i++)
	{
		marked[i] = 0;
	}
	//compare with ans

	for (int i = 0; i < nofdigits; i++)
	{
		if (trydigits[i] == digits[i])
		{
			marked[i] = 2;
		}
	}

	for (int i = 0; i < nofdigits; i++)
	{
		for (int j = 0; j < inpdigits; j++)
		{
			if (trydigits[j] == digits[i] && marked[j] == 0 && marked[i] != 2)
			{
				marked[j] = 1;
				j = 0;
				break;
			}
		}
	}
	
	for (int i = 0; i < nofdigits; i++) {
		if (marked[i] == 2) {
			setTextColor(GREEN);
			printf("%d", trydigits[i]); //green
			setTextColor(RESET);
			}
		 if (marked[i] == 1) {
			setTextColor(ORANGE);
			printf("%d", trydigits[i]); //orange
			setTextColor(RESET);
			}
		 if (marked[i] == 0) {
				printf("%d", trydigits[i]); //no color
				}
	}
	printf("             ");
	
	goto inputans;
	
free(marked);
free(trydigits);
free(digits);
return 0;
}
