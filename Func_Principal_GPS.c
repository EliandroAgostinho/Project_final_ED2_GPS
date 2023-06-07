#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include "Estafeta.c"


int main(){

setlocale(LC_ALL,"Portuguese");

Estafeta *estfa;

int opc, num_v, grmax, esc;

	
    printf("\n\nInsira a quantidade de esquinas:\t ");	
    scanf("%i",&num_v);

    printf("\n\nInsira a quantidade de saídas p'ra cada esquina:\t ");
    scanf("%i",&grmax);

    estfa = cria_estafeta(num_v,grmax,1);    	

    
printf("\n\n");
system("pause");
system("cls");

int ins,origem,destino,dig,qtruas,i, remor, *origg, *destn, klm;


int ant[num_v];
float ds[num_v];

do{

   printf("\t\t>>>>Menu principal<<<<\n\n");
   printf("\n1-Inserir rua");
   printf("\n2-Remover rua");
   printf("\n3-Imprimir todos caminhos possíveis");
   printf("\n4-Mostrar o melhor caminho");
   printf("\n5-Mostrar o melhor caminho com excessões");
   printf("\n6-Tempo de cobertura e o percurso\n\n->>\t");	
   scanf("%i",&esc);
   
   
printf("\n\n");
system("pause");
system("cls");
   
   if (esc == 1){//Inserção de rua
   	
    printf("\n\nDigite a quantidade de ruas");	
    scanf("%i",&qtruas);
    
    	
   
      for(i=0;i<qtruas;i++){
      
         printf("\nDigite a origem:\t");
         scanf("%i",&origem);
         
         printf("\nDigite o destino:\t");
         scanf("%i",&destino);
         
         printf("1-Rua com duplo sentido\n0-Sentido único\n\n->>\t");
         scanf("%i",&dig);
         
         if(dig > 1 || dig < 0 ){
         	printf("\n\nErro");
         	exit(0);
         	
         }
         
         ins = insere_rua(estfa,origem,destino,dig,1);	
      	
      }	
   	
      	
   	
   }
   
   ////////////////////////////////////////////
   
       if (esc == 2){// Remover rua
       
       
       
         printf("\nDigite a origem:\t");
         scanf("%i",&origem);
         
         printf("\nDigite o destino:\t");
         scanf("%i",&destino);
         
         printf("1-Rua com duplo sentido\n0-Sentido único");
         scanf("%i",&dig);
         
       
       remor = remove_rua(estfa,origem,destino,dig);
       
   	
       }
       
       /////////////////////////
          if (esc == 3){// Caminhos possíveis
          
             
             printf("\nDigite a origem:\t");
             scanf("%i",&origem);
         
             printf("\nDigite o destino:\t");
             scanf("%i",&destino);
       
          
             caminhos_possivies(estfa,origem,destino);
   	
          }
   	
          /////////////////////////////
            if (esc == 4){// Melhor caminho
            	
            	printf("\nDigite a origem:\t");
                    scanf("%i",&origem);
         
            	
            	caminho_curto(estfa,origem,ant,ds);
            	
   	
            }	
   	
   	/////////////////////////////////
   	
	if (esc == 5){// Melhor caminho com excessões
	
	    printf("\nDigite a origem:\t");
                        scanf("%i",&origem);
         
                        printf("\nDigite o destino:\t");
                        scanf("%i",&destino);
       
	   printf("\n\nDigite as quantidades de ruas indesejadas");
	   scanf("%i",&qtruas);
	   
	   if( qtruas > num_v-2 ){
	   	
	   	printf("\n\nNão há caminho!");
	   	exit(0);
	   }
	   
	   for(i=0;i<qtruas;i++){
	   	
	   	printf("\n\nA origem da rua:\t");
	   	scanf("%i",&origg[i]);
	   	
	   	printf("\n\nO destino:\t");
	   	scanf("%i",&destn[i]);
	   	
	   }
	
	     caminho_curto_excess(estfa,origem,ant,ds, origg,destn);
	
   	
                    }
	
	  //////////////////////////////
	    if (esc == 6){//Tempo de cobertura e percurso
	    
	    
	        printf("\n\nQuantos kilometros tem o percurso:\t"); 
	        scanf("%i",&klm);
	        
	         tempo_de_cobertura(estfa,klm);
	         caminho_curto(estfa,estfa->arestas[0][0],ant,ds);
   	
                        }
	    
	//////////////////////////////////////
	
printf("\n\n0-Sair\n1-Voltar ao menu");
scanf("%i",&opc);

printf("\n\n");
system("pause");
system("cls");

	
}while(opc != 0);


printf("\n\n");
system("pause");
system("cls");




//caminho_curto(estfa,2,ant,ds);

//int rem = remove_rua(estfa,0,1,1);

//int origem[2]={4};
//int destt[2]={5};

//caminho_curto_excess(estfa,0,ant,ds,origem,destt);

//imprime_grafo(estfa);

//caminhos_possivies(estfa,1,4);

//melhor_percurso(estfa,2,ant);

//tempo_de_cobertura(estfa,int kilm);

libera_estafeta(estfa);
	
return 0;	
 }
