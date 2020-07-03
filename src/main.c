/* Contador de palavras

/* Data de submissao: 03/07
 * Nome: Lucas Leite Tavares  
 * RA: 156377
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_P 4];

unsigned long int Valor_Entrada[1000];
unsigned char Palavra_entrada = ' ';

/* Para verificar se é primo ou nao baseamos em:
http://www.bosontreinamentos.com.br/programacao-em-linguagem-c/programa-para-determinar-se-um-numero-e-primo-em-c/
para criar a função de vrificação a abixo
[RETIRADA DO LAB 4]
*/
unsigned long int VerificarPrimo(int aux){

	int n,a,b;
	int Primo = 1;
	
	n = aux;

		if(n <= 1){
		Primo = 0	;
		}
		else if (n == 2){
		Primo = 1;
		}
		else{
			for(a = 2; a <= n/2;a++){
				b = aux%a;
				if(b == 0){ 
				Primo = 0;
				break;
			}
		}
	}
	return Primo;

}

/* Programa que usa o tydef com 4 procesos independentes, resolvendo paralelamente se cada valor é primo*/
int main() {
		// Definição das variaveis auxiliars e do estrutura
	pid_t P [4];
	int i = 0,tam = 0;
	
	//visibilidade e proteção dados em aula
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;

	/* Criamos uma area na memoria para os processos */
	int *a;
	a = (int*) mmap(NULL, sizeof(int)*100, protection, visibility, 0, 0);
	if ((long int)a==-1)
	(*a)=0;


	// Leitura da entrada como Valor e palavra:
	
	while(Palavra_entrada != '\n') {
		scanf("%ld%c", &Valor_Entrada[tam], &Palavra_entrada);
		tam++;
	}	
	
	// usamos esse laço pra chamar a função ja escrita de verificar primos, e no final printamos os primos.
	// Foi usado https://pt.stackoverflow.com/questions/289579/entendo-uma-execu%C3%A7%C3%A3o-paralela-usando-fork-como-funciona-o-fork
	// Como uma base para escrever o prog final com o Fork
	for( i = 0; i < tam; i++) {
		P[i % 4] = fork();
		if ( P[i % 4] == 0 ) {
			*a += VerificarPrimo(Valor_Entrada[i]);
		  	exit(0);
    	}
    	if(i % 4 == 3 && i != 0){
    		for (int j = 0; j < 4; j++)
    			waitpid(P[j], NULL, 0);
    	} else if(i == tam - 1) {
    		for(int j = 0; j < tam % 4; j++) {
    			waitpid(P[j], NULL, 0);
    		}
    	}
	};
	printf("%d\n", *a);
	return 0;
}