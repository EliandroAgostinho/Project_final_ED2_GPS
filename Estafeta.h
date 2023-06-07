

typedef struct grafo{

 int e_ponderado;
 int num_vertices;
 int grau_max;
 
 int **arestas;
 float **peso;
 int *grau; 	
	
	
}Estafeta;


Estafeta *cria_estafeta(int nu_vert, int gr_mx, int e_pond);

void libera_estafeta(Estafeta *esta);

int insere_rua(Estafeta *esta, int orig, int dest, int e_dig, float pes);

int remove_rua(Estafeta *esta,int orig,int dest, int e_dig);

int buscaMenorDistancia(float *dista, int *visitado, int NumVt);

void imprime_grafo(Estafeta *esta);

void caminho_curto(Estafeta *esta, int ini, int *ante, float *dista);

void caminho_curto_excess(Estafeta *esta, int ini, int *ante, float *dista, int *orig, int *dest);

void caminhos_possivies(Estafeta *esta, int orig, int dest);

void tempo_de_cobertura(Estafeta *esta,int kilm);

void melhor_percurso(Estafeta *esta, int orig, int *pai);


