#include <stdio.h>
#include <stdlib.h>


typedef struct e {
	int ne; //dimensione lista di adiacenza di un nodo
	int * edge; //array che contiene la lista di adiacenza di un nodo
} edges; 


typedef struct _queue {
	int* values;
	int capacity;
	int head;
	int tail;

} queue;


void init (queue* q, int capacity) {
	q->values=malloc(sizeof(int)* capacity);
	q->capacity=capacity;
	q->head=-1;
	q->tail=-1; //primo elemento vuoto
}


//1 se vuota0 altrimenti
int isEmpty(queue* q) {
	if (q->head == -1 && q->tail == -1)
		return 1;

	return 0;
}


//inserisci elemento
void ENQUEUE(queue* q, int value) {
	q->head++;
	if (q->tail==-1) q->tail++;
	q->values[q->head]=value;
	
}


//rimuovi elemento
int DEQUEUE(queue* q) {
	int elem;
	if (q->head==q->tail) {
		elem=q->values[q->head];
		q->head=-1;
		q->tail=-1;
		return elem;
	}
	else {
	elem=q->values[q->tail];
	q->tail++;
	return elem;
	}
}


void printQueue(queue* q) {
	if (q->tail==-1 && q->head==-1) {
		printf("Coda Vuota \n");
		return;
	}

	if (q->tail == q->head) {
		printf("[%d] \n", q->values[q->tail]);
		return;
	}

	for (int i=q->tail;i<=q->head;i++)
		printf("[%d] ", q->values[i]);

	printf("\n");

}



//s e` la sorgente
int BFS (edges* G, int n, int* C,int *D, int s) {
	int i, u, dest;
	
	queue* Q = malloc(sizeof(queue)); 

	init(Q, n);	
	
	for (i=0;i<n;i++) {
		C[i]=0;
		D[i]=0;
	}
	//coloro di grigio il nodo sorgente
	C[s]=1;
	//metto in coda il nodo sorgente	
	ENQUEUE(Q, s);

	while(!isEmpty(Q)) {

		u=DEQUEUE(Q);
		for (i=0;i<G[u].ne;i++) {	
			dest=G[u].edge[i];

			if (C[dest]==0) {	

				if (C[u]==1)
				C[dest]=2;
				else C[dest]=1;
			
				D[dest]=D[u]+1;
				ENQUEUE(Q,dest);
			}//chiudoif
			else if ( (C[u]==2 && C[dest]==2 ) || ( C[u]==1 && C[dest]==1) ) {
				return 0;


			}
		}
	}//chiudowhile
	
	return 1;
}


void printC(int *C, int n) {
	for (int i=0;i<n;i++)
		printf ("%d", C[i]);
}

void printD(int *D, int n) {
	for (int i=0;i<n;i++)
		printf ("%d", D[i]);
}


int main() {

int n, i, valore, j;

scanf ("%d", &n);

edges* G= malloc (n * sizeof(struct e));

int *C= (int*) malloc (sizeof(int)*n);

int *D= (int*) malloc (sizeof(int)*n);

//creo lista di adiacenza
for (i=0;i<n;i++) {
	scanf ("%d", &G[i].ne);
	G[i].edge= malloc (G[i].ne * sizeof(int));

	for (j=0;j<G[i].ne;j++) {
		scanf ("%d", &valore);
		G[i].edge[j]=valore;
	}
}
//


int ris=BFS(G, n, C, D, 0);
printf("%d", ris);





return 0;
}
