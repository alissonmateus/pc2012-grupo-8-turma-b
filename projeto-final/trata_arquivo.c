#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAMANHO_ADICIONAL 100000
#define T_STR_MENOR 5
#define T_STR_MAIOR 30

void alocarVetorString(char ***,long int *, int);
void realocaVetorString(char ***,long int *,int);


int insereOrdenado(char **vetor, char *palavra, int tamanho)
{
	int i=0,j;
	while(i<tamanho && strcmp(vetor[i],palavra)<0)
		++i;
	
	/*palavra ja foi inserida*/
	if(strcmp(vetor[i],palavra)==0)
		return 0;
	else
	{
		for(j=tamanho;j>=i;--j)
			strcpy(vetor[j+1],vetor[j]);
		strcpy(vetor[i],palavra);
		return 1;
	}
}

int main(int argc, char **argv)
{
	FILE *p_texto;
	long int p_texto_tam=0, t_vet_menor=0, t_vet_maior=0, i_menor=0, i_maior=0;
	char *s_texto, **vetor_menor, **vetor_maior, *palavra_atual;
	register long int i=0;
	
	/*Verifica se o argumento foi passado*/
	if(argc < 2)
	{
		fprintf(stderr,"Erro: Arquivo texto deve ser passado no primeiro argumento do programa.\n");
		return EXIT_FAILURE;
	}

	/*Abrir o arquivo*/
	p_texto = fopen(argv[1],"r");
	if(p_texto == NULL)
	{
		fprintf(stderr,"Erro: Erro ao abrir o arquivo especificado.\n");
		return EXIT_FAILURE;
	}

	/*Copiar o arquivo todo para uma string*/
	fseek(p_texto,0,SEEK_END);
	p_texto_tam = ftell(p_texto); //recupera o nro do byte final do arquivo
	fseek(p_texto,0,SEEK_SET);
	s_texto = (char *) malloc(p_texto_tam*sizeof(char) + 1*sizeof(char));

	fgets(s_texto,p_texto_tam,p_texto); //copia o texto do arquivo para a string -> [TESTADO] copia o texto na íntegra

	fclose(p_texto); /*Fecha o arquivo que não será mais utilizado*/

	alocarVetorString(&vetor_menor,&t_vet_menor,T_STR_MENOR); //aloca vetor menor
	alocarVetorString(&vetor_maior,&t_vet_maior,T_STR_MAIOR); // aloca vetor maior

	/*Separa as palavras no vetor maior ou menor*/
	palavra_atual = strtok(s_texto," ,-");
	while(palavra_atual != NULL)
	{

		if(strlen(palavra_atual) <= T_STR_MENOR) //inserir no vetor menor
		{
			if(i_menor+1 == t_vet_menor) //verificar se é já foram utilizadas todas as posiçoes do vetor
				realocaVetorString(&vetor_menor,&t_vet_menor,T_STR_MENOR);

			//INSERIR ORDENADO AQUI
			//strcpy(vetor_menor[i_menor++],palavra_atual);
			if(insereOrdenado(vetor_menor,palavra_atual,i_menor))
				i_menor++;
			
		}
		else //inserir no vetor maior
		{
			if(i_maior+1 == t_vet_maior) //verificar se é já foram utilizadas todas as posiçoes do vetor
				realocaVetorString(&vetor_maior,&t_vet_maior,T_STR_MAIOR);

			//INSERIR ORDENADO AQUI
			//strcpy(vetor_maior[i_maior++],palavra_atual);
			if(insereOrdenado(vetor_maior,palavra_atual,i_maior))
				i_maior++;
		}

		palavra_atual = strtok(NULL," ,-");
	}

	printf("Palavras menor: %ld - Palavras maior: %ld\n",i_menor,i_maior);

	return EXIT_SUCCESS;
}

/**
 * Alocar o vetor de strings.
 *
 * @param ***vetor: endereco do vetor de strings
 * @param *tamanho: o endereco do tamanho que deve ser igual a 0 do vetor de strings
 * @param tamanho_string: o tamanho das novas strings que serão alocadas
 */
void alocarVetorString(char ***vetor,long int *tamanho, int tamanho_string)
{
	register long int i=0;
	*tamanho += TAMANHO_ADICIONAL;
	*vetor = (char **) malloc((*tamanho)*sizeof(char *));
	for(i=0; i<*tamanho; i++)
		(*vetor)[i] = (char *) malloc((tamanho_string+1)*sizeof(char));
}

/**
 * Realocar o vetor de strings para um novo tamanho, caso o tamanho antigo não seja suficiente.
 *
 * @param ***vetor: endereco do vetor de strings
 * @param *tamanho: o endereco tamanho antigo do vetor de strings
 * @param tamanho_string: o tamanho das novas strings que serão alocadas
 */
void realocaVetorString(char ***vetor,long int *tamanho, int tamanho_string)
{
	register long int i=0;
	long int ultima_posicao;
	ultima_posicao = *tamanho;

	*tamanho += TAMANHO_ADICIONAL;

	*vetor = (char **) realloc (*vetor,(*tamanho)*sizeof(char *));

	for(i=ultima_posicao; i<*tamanho; i++)
		(*vetor)[i] = (char *) malloc((tamanho_string+1)*sizeof(char));
}
