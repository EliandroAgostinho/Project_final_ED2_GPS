#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include "Estafeta.h"
 
 
 
Estafeta *cria_estafeta(int nu_vert, int gr_mx, int e_pond){
 
 Estafeta *est = (Estafeta*) malloc(sizeof(struct grafo)); // Alocar espaço para o verticie
 
 if(est != NULL){ // Verificar memória
 
    int i; 
 
    est->num_vertices = nu_vert;

    est->grau_max = gr_mx;

    est->e_ponderado = (e_pond != 0)?1:0; // Se for ponderado =1 então as arestas "Ruas" terão peso 
    
    est->grau = (int*)calloc(nu_vert,sizeof(int)); // Saídas das ruas
    
    est->arestas = (int**)malloc(nu_vert*sizeof(int*)); // Ruas 1º* indica origem e o 2º* indica o destino 
    
    for(i=0; i < nu_vert; i++ )//Fazendo a alocaçao da matriz e vetores
    est->arestas[i] = (int*)malloc(gr_mx*sizeof(int));	
        
        if (est->e_ponderado ){
           est->peso = (float**)malloc(nu_vert*sizeof(float*));
           
           for(i=0; i<nu_vert ; i++)
           est->peso[i] = (float*)malloc(gr_mx*sizeof(float));
        	
        }
     	
 }
 	
 printf("\n\nEstafeta criado.");
 
 return est;	
 	
}



int insere_rua(Estafeta *esta, int orig, int dest, int e_dig, float pes){

    if(esta == NULL){//Verificar se existe verticie
    
    printf("\n\nErro: Não é possível inserir rua!");	
    return 0;	
    }
       
    
    if (orig < 0 || orig >= esta->num_vertices){// Verificar se origem existe
    
    printf("\n\nErro: A origem não existe!");
    return 0;	
    }
       
       
    if (dest < 0 || dest >= esta->num_vertices){// Verificar se destino existe
    
    printf("\n\nErro: O destino não existe! ");
    return 0;	
    } 
        
        
    esta->arestas[orig][esta->grau[orig]]= dest;
    
    if (esta->e_ponderado)
        esta->peso[orig][esta->grau[orig]] = pes;  
    esta->grau[orig]++;     
       
    if(e_dig == 0)// Se for rua com duplo sentido insere no sentido contrario destino-origem
    return insere_rua(esta,orig,dest,1,pes);      
          
     
     printf("\n\nRua inserida.");     
    return 1;	
	
	
}



int remove_rua(Estafeta *esta,int orig,int dest, int e_dig){
	
 if(esta == NULL){ // Verificar se existe verticie
 
 printf("\n\nErro: Não é possível remover a rua!");	
 return 0;	
 }
    
    
 if (orig < 0 || orig >= esta->num_vertices){// Verificar se existe origem
 
 printf("\n\nErro: A origem não existe!");
 return 0;	
 }
     
     
  if (dest < 0 || dest >= esta->num_vertices){ // Verificar se existe destino
  
  printf("\n\nErro: O destino não existe!");
  return 0;	
  }
     
  
  int i = 0;
  
  while(i < esta->grau[orig] && esta->arestas[orig][i] != dest)
       i++;
       
   if (i == esta->grau[orig]){
   	
   	printf("Elemento não encontrado!");
   	
   	return 0;
   }          
	
   esta->grau[orig]--;
   esta->arestas[orig][i] = esta->arestas[orig][esta->grau[orig]];

   if (esta->e_ponderado)
       esta->peso[orig][i] = esta->peso[orig][esta->grau[orig]];
	
   if (e_dig == 0)// Remover seja duplo sentido
       return remove_rua(esta,dest,orig,1);

printf("\n\nRua removida.");    	
return 1;	
}



int buscaMenorDistancia(float *dista, int *visitado, int NumVt){
	
  int i, menor=-1, primeiro=1;
  
  for(i = 0; i < NumVt; i++){
  
      if (dista[i] >= 0 && visitado[i] == 0 ){
      	
      	if (primeiro){
      		
      	     menor = i;
	     primeiro = 0;	
      		
	} else{
	
	       if(dista[menor] > dista[i])
	          menor = i;	
		
	   }
      	
      }	
  	
  	
  }	
	
	
return menor;	
}




void caminho_curto(Estafeta *esta, int ini, int *ante, float *dista){

int i, j, cont, NumVt, ind, *visitado, recBuscaDist;

cont = NumVt = esta->num_vertices;
 
float peso;



visitado = (int*)malloc(NumVt * sizeof(int));

    for(i = 0; i < NumVt; i++){
	
        ante[i] = -1;	
        dista[i] = -1;
        visitado[i] = 0;         	
	
     }

      dista[ini] = 0;
      
      while(cont > 0){
      
            recBuscaDist = buscaMenorDistancia(dista,visitado,NumVt); 	
      	
            if(recBuscaDist == -1)
               break;	
               
               
             visitado[recBuscaDist] = -1;
             cont--;    		
      }

     free(visitado);
     
     
     
     for(i = 0; i < esta->grau[recBuscaDist]; i++){
    
            ind = esta->arestas[recBuscaDist][i];
        
            if (dista[ind] < 0 ){
        
        	
                dista[ind] = dista[recBuscaDist]+1;
                //dista[ind] = dista[recBuscaDist]+esta->peso[recBuscaDist][i];

                ante[ind] = recBuscaDist;     
        	
            } 
        
                            else{
        	
                      	if (dista[ind] > dista[recBuscaDist]+1){
        	
        	   dista[ind] = dista[recBuscaDist]+1;
        	   //dista[ind] = dista[recBuscaDist]+esta->peso[recBuscaDist][i];

                       ante[ind] = recBuscaDist;
                       	        	
        		
	}
        	
                             }	
     	
     	
     }
     





	
for(i = 0; i < esta->num_vertices ; i++){
      	
	
      for(j = ini; j < esta->num_vertices ; j++){
    	
    	if(esta->arestas[i][j] == esta->arestas[i][esta->grau[i]]){
    	
	    printf("%i",j);
	    
                    peso = peso + esta->peso[i][esta->grau[i]]; 	    	
    		
	}
                    
                    //peso = peso + esta->peso[i][esta->grau[i]];
    	
    }

if(i>0)break;
	
}

printf("\tPeso: %0.f\n\n",peso);


	
}
	

 
 
     




void caminho_curto_excess(Estafeta *esta, int ini, int *ante, float *dista, int *orig, int *dest){


int i, cont, NumVt, ind, *visitado, recBuscaDist;

float peso;

cont = NumVt = esta->num_vertices;



visitado = (int*)malloc(NumVt * sizeof(int));

    for(i = 0; i < NumVt; i++){
	
        ante[i] = -1;	
        dista[i] = -1;
        visitado[i] = 0;         	
	
     }

      dista[ini] = 0;
      
      while(cont > 0){
      
            recBuscaDist = buscaMenorDistancia(dista,visitado,NumVt); 	
      	
            if(recBuscaDist == -1)
               break;	
               
               
             visitado[recBuscaDist] = -1;
             cont--;    		
      }

     free(visitado);
	
///////////////////////////////////////////////////

int j;

    if(esta == NULL){//Verificar se existe verticie
    
       printf("\n\nErro: Não existe verticie!");	
       exit(0); 	
    }
       
    
    

    for(i = 0; i < esta->grau[recBuscaDist]; i++){
    
          for(j = 0;j < esta->num_vertices ; j++ ){
    
             if (orig[j] < 0 || orig[j] >= esta->num_vertices){// Verificar se origem existe
    
                  printf("\n\nErro: A origem não existe!");
                  exit(0); 	
             }
       
       
                 if (dest[j] < 0 || dest[j] >= esta->num_vertices){// Verificar se destino existe
    
                      printf("\n\nErro: O destino não existe! ");
                 
                      exit(0);	
                 
                 }
          
                         if(orig[j] == dest[j] ){ // Verificar se existe uma rua
                    	
                                printf("\n\nErro: A origem não pode ser a mesma que destino");
	            exit(0);	
                    	
	      }	
         
        if (orig[j] != esta->arestas[esta->grau[recBuscaDist]][j] && dest[j] != esta->arestas[esta->grau[recBuscaDist]][j] ){ // Descartando as possibilidades de passar nas ruas indesejadas
        	
          	
        ind = esta->arestas[recBuscaDist][i];
        
        if (dista[ind] < 0 ){
        
        	
            dista[ind] = dista[recBuscaDist]+1;
            //dista[ind] = dista[recBuscaDist]+esta->peso[recBuscaDist][i];

            ante[ind] = recBuscaDist;     
        	
        }  else{
        	
        	if (dista[ind] > dista[recBuscaDist]+1){
        	
        	   dista[ind] = dista[recBuscaDist]+1;
        	   //dista[ind] = dista[recBuscaDist]+esta->peso[recBuscaDist][i];

                       ante[ind] = recBuscaDist;
                       	        	
        		
	}
        	
           }
          	
        	
        
        
        	
        } 
          	
          	
          }
        
    	
     	
     	
     }
     
      	

	
for(i = 0; i < esta->num_vertices ; i++){
      	
	
      for(j = ini; j < esta->num_vertices ; j++){
    	
    	if(esta->arestas[i][j] == esta->arestas[i][esta->grau[i]]){
    	
	    printf("%i",j);
	    
                    peso = peso + esta->peso[i][esta->grau[i]]; 	    	
    		
	}
                    
                    //peso = peso + esta->peso[i][esta->grau[i]];
    	
    }

if(i>0)break;
	
}

printf("\tPeso: %0.f\n\n",peso);



	
	
}



void caminhos_possivies(Estafeta *esta, int orig, int dest){

     if (esta == NULL){//Verificar se é nulo
     	
         printf("\n\nErro: Grafo não vazio!");	
         exit(0);        	
     } 

          if (orig < 0 || orig >= esta->num_vertices){// Verificar se origem existe
    
              printf("\n\nErro: A origem não existe!");
              exit(0);	
          }
       
       
                if (dest < 0 || dest >= esta->num_vertices){// Verificar se destino existe
    
                    printf("\n\nErro: O destino não existe! ");
                    exit(0);	
               
                } 


                    if (orig == dest ){// Verificar se é uma rua
                  	
                  	    printf("\n\nA origem e destino não podem ser no mesmo verticie!");
                  	
                  	   exit(0);
                    }
	
	
 int i,j;
 float pes;
                
                if(orig > dest){
                	
                	printf("\n\nA origem não pode ser maior que dsetino!");
                	exit(0);
                }
 	
 	
 	
	  if(orig < dest ){
	  	
	     for(i=orig;i<esta->num_vertices;i++){
	  
	          printf("%i",i);
	          	       	
	          for(j=0;j< esta->num_vertices;j++){
	          	
	                    	
	       	if(esta->arestas[i][j]){
	       		
	       	   printf("%i",j);
                                           
		   pes = pes + esta->peso[i][j];
		    		       	
		}
	          	
	          	
	          }  	       	
	          	
	       printf("\tPeso: %0.f\n\n",pes);   	
	  	
	     }	
	  	
	    
	       	  	
	  }
	
	
	
	
}







void tempo_de_cobertura(Estafeta *esta,int kilm){
	
     if(esta == NULL ){
     
        printf("\n\nErro: Grafo vazio!");	
     exit(0);	
     }


int km = 20, tmp_min = 30, resul;

int i,j;



	
for(i = 0; i < esta->num_vertices ; i++){
      	
	
      for(j = 0; j < esta->num_vertices ; j++){
    	
    	if(esta->arestas[i][j]){
    	
                      resul = resul+(kilm * tmp_min)/km;
	    
	    
                         	    	
    		
	}
                    
    	
    }

	
}	


printf("\n\nO tempo de cobertura é: %i",resul);	
	
}












void imprime_grafo(Estafeta *esta){
	
int i,j;
float peso;


	
for(i = 0; i < esta->num_vertices ; i++){
      	
	
      for(j = 0; j < esta->num_vertices ; j++){
    	
    	if(esta->arestas[i][j]){
    	
	    printf("%i",j);
	    
                        peso = peso + esta->peso[i][j]; 	    	
    		
	}
                    
    	
    }

printf("\tPeso: %0.f\n\n",peso);	
}	
	
	
}


void melhor_percurso(Estafeta *esta, int orig, int *pai){//Kruskal

int i, j, dest, primeiro, NV = esta->num_vertices;

double menorPeso;

/*

for(i=0;i<NV;i++)
    pai[i] =-1;// Sem pai

pai[orig] = orig;

  while(1){
  	
     primeiro = 1;
     //Percorrer todos verticies
     for(i=0;i<NV;i++){
     	
        //Vertcicies visistados	
        if(pai[i] != -1){
        	
        	// Percorre os vizinhos do verticies visitado
        	for(j=0;j<esta->grau[i];j++){
                
                      // Procurar menor peso
        		
	}
        	
        }	
     	
     	
     }	
  
   
     if(primeiro == 1)
        break;
   
     pai[dest] = orig; 	
  }


if (pai[esta->arestas[i][j]] == -1){
	
   if (primeiro){
      
       menorPeso = esta->peso[i][j];
       
       orig=i;
       dest = esta->arestas[i][j];
       primeiro = 0;
       	
   	
   	
   }
   
      else{
      	
            if(menorPeso > esta->peso[i][j]){
               menorPeso = esta->peso[i][j];
               orig =i;
               dest = esta->arestas[i][j];	
            	
            }
      	
      }
      	
}



   for(i=0;i<sizeof(pai);i++){
	
      printf("%i\t",pai[i]);
	
  }
*/	
}



void libera_estafeta(Estafeta *esta){
	
     if (esta != NULL){
     	
         int i;
         
         for (i=0; i < esta->num_vertices; i++)
              free(esta->arestas[i]);
         free(esta->arestas);
         
         if(esta->e_ponderado){
         	
         	for(i=0; i < esta->num_vertices; i++ )
         	   free(esta->peso[i]);
         	free(esta->peso);   	
         } 	
     
         free(esta->grau);
         free(esta);	
     	
     }	
	
	
	
}



