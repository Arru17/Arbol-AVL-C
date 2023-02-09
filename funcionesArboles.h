#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cliente Cliente;
typedef struct mascota Mascota;
typedef struct listaMascotas ListaMascotas;
typedef struct nodoArbol NodoArbol;
typedef struct arbol Arbol;


FILE* abrirArchivo();
FILE* prepararArchivo();
Cliente* crearCliente(char* nombreCliente, char* apellidoP,char* apellidoM, char* numeroTelefon);
Mascota* crearMascota(char* nombreMas, char* especieMas, int edadMas, int numeroAtencionesMas, char* vacunasMas, char* fechaControl);
NodoArbol* crearNodoArbol(Cliente* cliente);
Arbol* crearArbol();
ListaMascotas* crearListaMascota();
NodoArbol* buscar(NodoArbol* raiz, Cliente* cliente);
NodoArbol* buscarRegistro(NodoArbol* raiz, char* nombreCliente, char* apellidoPat, char* apellidoMat);
Mascota* revisarListaMascotas(ListaMascotas* mascotas, char* nombreMascota);
int revisarMenor(char* nombreCliente, char* apellidoPat, char* apellidoMat, Cliente* cliente);
int compararStrings(char* insertar, char* claveNodo);
int verificarMenor(Cliente* cliente1, Cliente* cliente2);
void rotarIzq(Arbol* a, NodoArbol* z);
void rotarDer(Arbol* a, NodoArbol* z);
int altura(NodoArbol* z);
int diferenciaAlturas(NodoArbol* z);
void balancear(Arbol* a, NodoArbol* z);
void insertarArbol(Arbol* arbol, NodoArbol* z);
NodoArbol* extraerMinimo(NodoArbol* x);
void transplantar(Arbol* a, NodoArbol* u, NodoArbol* v);
void borrarDato(Arbol* a, NodoArbol* z);
void insertarEnListaMascota(ListaMascotas* lista, Mascota* mascota);
void vaciarListaMascotas(ListaMascotas* lista);
void recorrerIn(NodoArbol* x);
void recorrerPre(NodoArbol* x);
void recorrerPost(NodoArbol* x);
void imprimirLista(ListaMascotas* lista);
int limpiarStdin();
int compararFechas(char* ingresada, char* fecha);
void buscarFecha(NodoArbol* x, char* fecha, FILE* archivo);
void revisarFechasMascotas(char* fecha, Cliente* cliente, FILE* archivo);
void escribirArchivo(Cliente* cliente, Mascota* mascota, FILE* archivo);
void eliminarMascota(ListaMascotas* lista, Mascota* mascota);
void vaciarArbol(NodoArbol* raiz);

typedef struct cliente{
	char nombre[31];
	char apellidoP[31];
	char apellidoM[31];
	char fono[21];
	ListaMascotas* listaMascotas;
}Cliente;

typedef struct mascota{
	char nombreM[21];
	char especie[21];
	int edad;
	int numAtenciones;
	char vacunas[3];
	char fechaProxControl[21];
	Mascota* siguiente;
}Mascota;

typedef struct listaMascotas{
	Mascota* primera;
	Mascota* ultima;
	int largo;
}ListaMascotas;

typedef struct nodoArbol{
	NodoArbol* padre;
	NodoArbol* hijoI;
	NodoArbol* hijoD;
	Cliente* cliente;
}NodoArbol;

typedef struct arbol{
	NodoArbol* raiz;
}Arbol;


//Funcion que abre un archivo en formato .txt para su lectura
//Entrada:      Salida: FILE*
FILE* abrirArchivo(){
	FILE* archivo;
	char nombreArchivo[14]="Bultos.in.txt";
	archivo= fopen(nombreArchivo,"r");
	return archivo;
}
//Funcion que crea o vacia un archivo en formato .txt para su posterior escritura.
//Entrada:      Salida: archivo.
FILE* prepararArchivo(){
	FILE* archiv;
	char text[15]="Bultos.out.txt"; 
	archiv=fopen(text, "w");
	return archiv;
}

//Funcion que crea un cliente con todos sus datos correspondientes
//Entradas: char*, char*, char*, char*, char*, Mascota*  Salida: Cliente*
Cliente* crearCliente(char* nombreCliente, char* apellidoP,char* apellidoM, char* numeroTelefon){
	Cliente* cliente;
	cliente= (Cliente*)malloc(sizeof(Cliente));
	if(cliente==NULL){
		printf("No se pudo asignar memoria al cliente\n");
	}
	strcpy(cliente->nombre,nombreCliente);
	strcpy(cliente->apellidoP,apellidoP);
	strcpy(cliente->apellidoM, apellidoM);
	strcpy(cliente->fono, numeroTelefon);
	cliente->listaMascotas = crearListaMascota();
	return cliente;
}
//Funcion que crea una mascota con todos sus datos correspondientes
//Entradas: char*, char*, int, int, char*   Salida: Mascota*
Mascota* crearMascota(char* nombreMas, char* especieMas, int edadMas, int numeroAtencionesMas, char* vacunasMas, char* fechaControl){
	Mascota* mascota;
	mascota = (Mascota*)malloc(sizeof(Mascota));
	if(mascota==NULL){
		printf("No se pudo asignar memoria a la mascota.\n");
	}else{
	strcpy(mascota->nombreM,nombreMas);
	strcpy(mascota->especie, especieMas);
	mascota->edad=edadMas;
	mascota->numAtenciones=numeroAtencionesMas;
	strcpy(mascota->vacunas,vacunasMas);
	strcpy(mascota->fechaProxControl, fechaControl);
	mascota->siguiente=NULL;
	}
	return mascota;
}

NodoArbol* crearNodoArbol(Cliente* cliente){
	NodoArbol* nodo;
	nodo= (NodoArbol*)malloc(sizeof(NodoArbol));
	if(nodo==NULL){
		printf("No se pudo asignar memoria para el nodo\n");
	}
	nodo->padre=NULL;
	nodo->hijoI=NULL;
	nodo->hijoD=NULL;
	nodo->cliente=cliente;
	return nodo;
}

Arbol* crearArbol(){
	Arbol* arbol;
	arbol=(Arbol*)malloc(sizeof(Arbol));
	if (arbol==NULL){
		printf("No se pudo asignar memoria al arbol\n");
	}
	arbol->raiz= NULL;
	return arbol;
}

ListaMascotas* crearListaMascota(){
	ListaMascotas* lista;
	lista=(ListaMascotas*)malloc(sizeof(ListaMascotas));
	if(lista==NULL){
		printf("No se pudo asignar memoria a la lista.\n");
		return NULL;
	}
	lista->primera=NULL;
	lista->ultima=NULL;
	lista->largo=0;
	return lista;
}

NodoArbol* buscar(NodoArbol* raiz, Cliente* cliente){
	while((raiz!= NULL) && (verificarMenor(cliente, raiz->cliente)!=2)){
		if(verificarMenor(cliente, raiz->cliente)==0){
			raiz= raiz->hijoI;
		}
		else{
			raiz= raiz->hijoD;
		}
	}
	return raiz;
}

NodoArbol* buscarRegistro(NodoArbol* raiz, char* nombreCliente, char* apellidoPat, char* apellidoMat){
	while((raiz!= NULL) && (revisarMenor(nombreCliente, apellidoPat, apellidoMat, raiz->cliente)!=2)){
		if(revisarMenor(nombreCliente, apellidoPat, apellidoMat, raiz->cliente)==0){
			raiz= raiz->hijoI;
		}
		else{
			raiz= raiz->hijoD;
		}
	}
	return raiz;
}

Mascota* revisarListaMascotas(ListaMascotas* mascotas, char* nombreMascota){
	Mascota* auxiliar;
	Mascota* retorno;
	auxiliar= mascotas->primera;
	while(auxiliar != NULL){
		if(strcmp(nombreMascota, auxiliar->nombreM)==0){
			retorno = auxiliar;
		}else{
			
		}
		auxiliar= auxiliar->siguiente;
	}
	return retorno;
}

int revisarMenor(char* nombreCliente, char* apellidoPat, char* apellidoMat, Cliente* cliente){
	if((strcmp(nombreCliente, cliente->nombre)==0) && (strcmp(apellidoPat, cliente->apellidoP)==0) && (strcmp(apellidoMat, cliente->apellidoM)==0)){
		return 2; // caso especial
	}
	else if((strcmp(nombreCliente, cliente->nombre)==0) && (strcmp(apellidoPat, cliente->apellidoP)==0)){
		if (compararStrings(apellidoMat, cliente->apellidoM)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(apellidoMat, cliente->apellidoM)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if((strcmp(nombreCliente, cliente->nombre)==0) && (strcmp(apellidoMat, cliente->apellidoM)==0)){
		if (compararStrings(apellidoPat, cliente->apellidoP)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(apellidoPat, cliente->apellidoP)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if((strcmp(apellidoPat, cliente->apellidoP)==0 ) && (strcmp(apellidoMat, cliente->apellidoM)==0)){
		if (compararStrings(nombreCliente, cliente->nombre)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(nombreCliente, cliente->nombre)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else if (strcmp(nombreCliente, cliente->nombre)!=0){
		if (compararStrings(nombreCliente, cliente->nombre)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(nombreCliente, cliente->nombre)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else if(strcmp(apellidoPat, cliente->apellidoP)!=0){
		if (compararStrings(apellidoPat, cliente->apellidoP)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(apellidoPat, cliente->apellidoP)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if(strcmp(apellidoMat, cliente->apellidoM)!=0){
		if (compararStrings(apellidoMat, cliente->apellidoM)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(apellidoMat, cliente->apellidoM)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else{
		printf("Ha ocurrido un error sin sentido \n");
	}
	
}

int compararStrings(char* insertar, char* claveNodo){
	int x;
	int resolucion;
	for(x=0; x<31;x++){
		if(((int)insertar[x]==0) || ((int)insertar[x] == 13)){
			resolucion=0;
			x=31;
		}
		else if(((int)claveNodo[x]==0) || ((int)claveNodo[x] == 13)){
			resolucion=1;
			x=31;
		}
		else if(insertar[x]<claveNodo[x]){
			resolucion=0;
			x=31;
		}
		else if(insertar[x]>claveNodo[x]){
			resolucion=1;
			x=31;
		}
		else{
			
		}
	}
	return resolucion;
}

int verificarMenor(Cliente* cliente1, Cliente* cliente2){
	if((strcmp(cliente1->nombre, cliente2->nombre)==0) && (strcmp(cliente1->apellidoP, cliente2->apellidoP)==0) && (strcmp(cliente1->apellidoM, cliente2->apellidoM)==0)){
		return 2; // caso especial
	}
	else if((strcmp(cliente1->nombre, cliente2->nombre)==0) && (strcmp(cliente1->apellidoP, cliente2->apellidoP)==0)){
		if (compararStrings(cliente1->apellidoM, cliente2->apellidoM)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->apellidoM, cliente2->apellidoM)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if((strcmp(cliente1->nombre, cliente2->nombre)==0) && (strcmp(cliente1->apellidoM, cliente2->apellidoM)==0)){
		if (compararStrings(cliente1->apellidoP, cliente2->apellidoP)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->apellidoP, cliente2->apellidoP)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if((strcmp(cliente1->apellidoP, cliente2->apellidoP)==0 ) && (strcmp(cliente1->apellidoM, cliente2->apellidoM)==0)){
		if (compararStrings(cliente1->nombre, cliente2->nombre)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->nombre, cliente2->nombre)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else if (strcmp(cliente1->nombre, cliente2->nombre)!=0){
		if (compararStrings(cliente1->nombre, cliente2->nombre)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->nombre, cliente2->nombre)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else if(strcmp(cliente1->apellidoP, cliente2->apellidoP)!=0){
		if (compararStrings(cliente1->apellidoP, cliente2->apellidoP)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->apellidoP, cliente2->apellidoP)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}
	else if(strcmp(cliente1->apellidoM, cliente2->apellidoM)!=0){
		if (compararStrings(cliente1->apellidoM, cliente2->apellidoM)==0){
			return 0; //0 -> izquierda 
		}
		else if (compararStrings(cliente1->apellidoM, cliente2->apellidoM)==1){
			return 1; //1 -> derecha
		}
		else{
			printf("Ha ocurrido un error desconocido \n");
		}
	}else{
		printf("Ha ocurrido un error sin sentido \n");
	}
}

void rotarIzq(Arbol* a, NodoArbol* z){
	NodoArbol* raiz;
	raiz= z->hijoD;
	if(z->padre ==NULL){
		a->raiz= raiz;
	}
	else{
		if (verificarMenor(z->cliente, z->padre->hijoI->cliente)== 2){
			z->padre->hijoI = raiz;
		}
		else{
			z->padre->hijoD= raiz;
		}
	}
	z->hijoD=raiz->hijoI;
	raiz->hijoI= z;
	raiz->padre= z->padre;
	raiz->hijoI->padre=raiz;
	if(raiz->hijoD!= NULL){
		raiz->hijoD->padre= raiz;
	}
}

void rotarDer(Arbol* a, NodoArbol* z){
	NodoArbol* raiz;
	raiz= z->hijoI;
	if(z->padre ==NULL){
		a->raiz=raiz;
	}
	else{
		if(verificarMenor(z->cliente, z->padre->hijoI->cliente)== 2){
			z->padre->hijoI=raiz;
		}
		else{
			z->padre->hijoD=raiz;
		}
	}
	z->hijoI= raiz->hijoD;
	raiz->hijoD= z;
	raiz->padre= z->padre;
	raiz->hijoD->padre= raiz;
	if(raiz->hijoI !=NULL){
		raiz->hijoI->padre= raiz;
	}
}

int altura(NodoArbol* z){
	int HI;
	int HD;
	if((z->hijoD ==NULL) && (z->hijoI ==NULL))
		return 0;
	if(z->hijoD == NULL)
		HD=0;
	else
		HD=altura(z->hijoD);
	if(z->hijoI ==NULL)
		HI=0;
	else
		HI= altura(z->hijoI);
	if(HI > HD)
		return HI+ 1;
	else 
		return HD +1;
}

int diferenciaAlturas(NodoArbol* z){
	int HI;
	int HD;
	if((z->hijoD !=NULL) || (z->hijoI !=NULL)){
		if((z->hijoD != NULL) && (z->hijoI != NULL)){
			HI= altura(z->hijoI);
			HD= altura(z->hijoD);
			return HI - HD;
		}
		if(z->hijoD == NULL){
			return 1+altura(z->hijoI);
		}
		if(z->hijoI ==NULL){
			return 0 - (1 + altura(z->hijoD)); 
		}
		return 0;
	}
	else{
		return 0;
	}
}

void balancear(Arbol* a, NodoArbol* z){
	int diferencia1;
	int diferencia2;
	diferencia1= diferenciaAlturas(z);
	if(diferencia1 >1){
		diferencia2= diferenciaAlturas(z->hijoI);
		if(diferencia2 <0){
			rotarIzq(a,z->hijoI);
		}
		rotarDer(a,z);
	}
	if(diferencia1 <-1){
		diferencia2= diferenciaAlturas(z->hijoD);
		if(diferencia2 >0){
			rotarDer(a,z->hijoD);
		}
		rotarIzq(a,z);
	}
}

void insertarArbol(Arbol* a, NodoArbol* z){
	NodoArbol* y;
	NodoArbol* x;
	if(a->raiz ==NULL){
		a->raiz= z;
		return;
	}
	else{
		x= a->raiz;
		while(x!= NULL){
			y=x;
			if(verificarMenor(z->cliente, x->cliente)==0){
				x=x->hijoI;
			}
			else{
				x= x->hijoD;
			}
		}
		if(verificarMenor(z->cliente, y->cliente)==0){
			y->hijoI= z;
		}
		else{
			y->hijoD= z;
		}
		z->padre=y;
		while(y!=NULL){
			balancear(a,y);
			y=y->padre;
		}
	}
	
}

NodoArbol* extraerMinimo(NodoArbol* x){
	while(x->hijoI != NULL){
		x= x->hijoI;
	}
	return x;
}

void transplantar(Arbol* a, NodoArbol* u, NodoArbol* v){
	if(u->padre == NULL){
		a->raiz = v;
	}
	else if(verificarMenor(u->cliente, u->padre->hijoI->cliente)==2){
		u->padre->hijoI=v;
	}
	else{
		u->padre->hijoD=v;
	}
	if(v != NULL){
		v->padre= u->padre;
	}
}

void borrarDato(Arbol* a, NodoArbol* z){
	if(z->hijoI ==NULL){
		transplantar(a,z,z->hijoD);
	}
	else if(z->hijoD ==NULL){
		transplantar(a,z,z->hijoI);
	}
	else{
		NodoArbol* y;
		y= extraerMinimo(z->hijoD);
		if(verificarMenor(z->cliente, y->padre->cliente)!=2){
			transplantar(a,y,y->hijoD);
			y->hijoD= z->hijoD;
			y->hijoD->padre=y;
		}
		transplantar(a,z,y);
		y->hijoI= z->hijoI;
		y->hijoI->padre=y;
	}
}

void insertarEnListaMascota(ListaMascotas* lista, Mascota* mascota){
	if(lista->primera==NULL){
		lista->primera=mascota;
		lista->ultima=mascota;
		lista->ultima->siguiente=NULL;
		lista->largo=(lista->largo +1);
	}else{
		lista->ultima->siguiente=mascota;
		lista->ultima=mascota;
		mascota->siguiente=NULL;
		lista->largo=(lista->largo +1);
		}
}
//Funcion que libera la memoria de una lista.
//Entrada: Lista     Salida:
void vaciarListaMascotas(ListaMascotas* lista){
	Mascota* auxiliar;
	auxiliar=lista->primera;
	while(auxiliar!=NULL){
	    Mascota* aux2=auxiliar; 
		auxiliar=auxiliar->siguiente;
		free(aux2);
	}
	free(lista);
}

void recorrerIn(NodoArbol* x){
	if(x != NULL){
		recorrerIn(x->hijoI);
		printf("key: %s ", x->cliente->nombre);
		//printf("%s ", x->cliente->fono);
		imprimirLista( x->cliente->listaMascotas);
		recorrerIn(x->hijoD);
	}
}

void recorrerPre(NodoArbol* x){
	if(x != NULL){
		printf("key: %s ", x->cliente->nombre);
		//printf("%s ", x->cliente->fono);
		imprimirLista( x->cliente->listaMascotas);
		recorrerPre(x->hijoI);
		recorrerPre(x->hijoD);
	}
}

void recorrerPost(NodoArbol* x){
	if(x!= NULL){
		recorrerPost(x->hijoI);
		recorrerPost(x->hijoD);
		printf("key: %s ", x->cliente->nombre);
		//printf("%s ", x->cliente->fono);
		imprimirLista( x->cliente->listaMascotas);
	}
}

void imprimirLista(ListaMascotas* lista){
	Mascota* auxiliar;
	//printf("MASCOTAS : ");
	auxiliar=lista->primera;
	while(auxiliar!=NULL){
	    printf("%s  ", auxiliar->nombreM);
		//printf("%d  ", auxiliar->edad);
		//printf("%s  ", auxiliar->fechaProxControl);
		auxiliar=auxiliar->siguiente;
	}
	//printf("\n");
}

//Funcion que se encarga de correr el cursor de lectura.
//Entrada:              Salida: 1 
int limpiarStdin(){
    while (getchar()!='\n');
    return 1;
}

int compararFechas(char* ingresada, char* fecha){
	int x;
	int comprobador=1;
	for(x=3; x<10; x++){
		if(x !=5){
			if(ingresada[x-3]!=fecha[x]){
			  	comprobador=0;
			  	x=13;	
			}
		}
	}
	if (comprobador==1){
		return 1; //1 -> son iguales
	}else{
		return 0; //0 -> son distintas
	}
}

void buscarFecha(NodoArbol* x, char* fecha, FILE* archivo){
	if(x != NULL){
		//printf("key: %s ", x->cliente->nombre);
		//imprimirLista( x->cliente->listaMascotas);
		revisarFechasMascotas(fecha, x->cliente, archivo);
		buscarFecha(x->hijoI, fecha, archivo);
		buscarFecha(x->hijoD, fecha, archivo);
	}
}

void revisarFechasMascotas(char* fecha, Cliente* cliente, FILE* archivo){
	Mascota* auxiliar;
	auxiliar= cliente->listaMascotas->primera;
	while(auxiliar != NULL){
		if(compararFechas(fecha,auxiliar->fechaProxControl)==1){
			escribirArchivo(cliente, auxiliar, archivo);
			//printf("%s", auxiliar->nombreM);
		}else{
			
		}
		auxiliar= auxiliar->siguiente;
	}
}

void escribirArchivo(Cliente* cliente, Mascota* mascota, FILE* archivo){
	fprintf(archivo, "%s ", cliente->nombre);
	fprintf(archivo, "%s ", cliente->apellidoP);
	fprintf(archivo, "%s ", cliente->apellidoM);
	fprintf(archivo, "%s ", mascota->nombreM);
	fprintf(archivo, "%s ", mascota->especie);
	fprintf(archivo, "%d ", mascota->edad);
	fprintf(archivo, "%s ", cliente->fono);
	fprintf(archivo, "%d ", mascota->numAtenciones);
	fprintf(archivo, "%s ", mascota->vacunas);
	fprintf(archivo, "%s ", mascota->fechaProxControl);
	fprintf(archivo, "\r\n");
}

void eliminarMascota(ListaMascotas* lista, Mascota* mascota){
	Mascota* auxiliar;
	Mascota* aux2;
	Mascota* aux3;
	auxiliar= lista->primera;
	int contador =0;
	while(auxiliar != NULL){
		contador= (contador+1);
		if(strcmp(auxiliar->nombreM, mascota->nombreM)==0){
			if(contador==1){
				lista->primera= auxiliar->siguiente;
				if(auxiliar->siguiente->siguiente==NULL){
					lista->ultima= auxiliar->siguiente;
				}
				aux2=auxiliar;
				auxiliar= auxiliar->siguiente;
				free(aux2);
			}else{
				aux2->siguiente= auxiliar->siguiente;
				aux3=auxiliar;
				auxiliar=auxiliar->siguiente;
				free(aux3);
			}
		}
		else if(contador == (lista->largo - 1)){
			lista->ultima= auxiliar;
			aux2= auxiliar->siguiente;
			auxiliar->siguiente= NULL;
			auxiliar=auxiliar->siguiente;
			free(aux2);
		}	
		else{
			aux2= auxiliar;
			auxiliar= auxiliar->siguiente;
		}
	}
}

void vaciarArbol(NodoArbol* raiz){
	if(raiz!= NULL){
		vaciarArbol(raiz->hijoI);
		vaciarArbol(raiz->hijoD);
		vaciarListaMascotas(raiz->cliente->listaMascotas);
		free(raiz->cliente);
		free(raiz);
	}
}