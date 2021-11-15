#include<stdio.h>
#include<stdlib.h>

typedef struct grafo{
  int v;//vértices
  int **adj;//matriz de adjacências
  int *visitado;//vetor de vértices visitados
}Grafo;

//aloca o grafo inicializando sem arestas
//e com a matriz de adjacências zerada.
Grafo* cria_grafo(int vertices){
  Grafo *grafo=malloc(sizeof(Grafo));
  grafo->v=vertices;
  grafo->adj=malloc(vertices * sizeof(int*));
  grafo->visitado=malloc(vertices * sizeof(int));
  for(int i=0;i<vertices;i++){
    grafo->visitado[i]=0;
    grafo->adj[i]=malloc(vertices * sizeof(int));
    for(int j=0;j<vertices;j++){
      grafo->adj[i][j]=0;
    }
  }
  return grafo;
}

void cria_aresta(Grafo *grafo, int inicio,int fim){
  grafo->adj[inicio][fim]=1;
}

//algoritmo dfs
int dfs(Grafo *grafo, int verticeInicial, int encontrar, int encontrado){
  grafo->visitado[verticeInicial]=1;
  printf("Visitado %d\n", verticeInicial+1);

  if(encontrar==verticeInicial){
    printf("%d encontrado.\n",verticeInicial+1);
    encontrado=1;
    return encontrado;
  }

  for(int i=0;i<grafo->v;i++){
    if(grafo->adj[verticeInicial][i]==1 && !grafo->visitado[i]){
      if(dfs(grafo,i,encontrar,encontrado)==1){
        encontrado=1;
        break;
      }
    }
  }
  return encontrado;
}

//utiliza o algoritmo DFS, e, caso o vertice a ser procurado não seja encontrado,
//escolhe outro vértice que ainda não tenha sido visitado como inicial da busca.
int busca(Grafo *grafo,int verticeInicial,int encontrar,int encontrado){
  int novoInicioEncontrado;
  printf("Inicio: %d\n",verticeInicial+1);
  while(dfs(grafo,verticeInicial,encontrar,encontrado)==0){
    novoInicioEncontrado=0;
    for(int i=0;i<grafo->v;i++){
      if(grafo->visitado[i]==0){
        novoInicioEncontrado=1;
        verticeInicial=i;
        break;
      }
    }
    if(!novoInicioEncontrado)
      return 0;
    printf("Novo inicio: %d\n",verticeInicial+1);
  }
}

//pede ao usuário que preencha a matriz de adjacencias.
int preencheMatriz(Grafo *grafo){
  int i,j,inicio=-1;
  printf("Preencha a matriz de adjacencias: \n");
  for(i=0;i<grafo->v;i++){
    for(j=0;j<grafo->v;j++){
      while(1){
        printf("Posicao %d %d: ",i+1,j+1);
        scanf("%d",&grafo->adj[i][j]);
        if(grafo->adj[i][j]==0 || grafo->adj[i][j]==1)
          break;
        printf("Valor invalido. É um grafo não-ponderado. Apenas 0 e 1.\n");
      }
      if(grafo->adj[i][j]==1 && inicio==-1)
        inicio=i;
    }
  }
  if(inicio==-1)
    return 0;
  else
    return inicio;
}

int main(){
  int op=0,aux,inicio;
  //cria o grafo sem arestas
  Grafo *G=cria_grafo(5);
  //preenche a matriz de adjacencias
  inicio=preencheMatriz(G);
  while(op!=2){
    printf("Digite 1 para buscar, 2 para sair: ");
    scanf("%d",&op);
    if(op==1){
      printf("Digite o vertice que deseja buscar: ");
      scanf("%d",&aux);
      //realizando a busca por profundidade
      if(busca(G,inicio,aux-1,0)==0)
        printf("Vertice não encontrado.\n");
      //resetando o vetor visitado após a busca ter sido feita.
      for(int i=1;i<6;i++){
        G->visitado[i]=0;
      }
    }
  }

  return 0;
}