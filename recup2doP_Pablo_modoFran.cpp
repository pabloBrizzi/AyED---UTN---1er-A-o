/* Durante la pandemia los alumnos fueron entregado trabajos prácticos 
y se iban cargando en una cola para su posterior procesamiento 
con los siguientes datos: dni-alumno, apellido_nombre, trabajos-entregados y calificación. 
La calificación se obtiene del siguiente criterio de valoración:
Se sabe que son 10 trabajos prácticos
Si el alumno ha cumplido el 80% estaría Aprobado
Si el alumno ha cumplido entre el 50% y 79,99% debería realizar un Repechaje
Otro caso estaría Desaprobado
En función de la calificación que obtuvieron los alumnos se genera una lista de control con los alumnos 
que tienen que ir a Repechaje y Aprobados, con la siguiente datos: 
dni-alumno, apellido_nombre , trabajos-entregados, estado.

Cuantos alumnos han accedido al Repechaje
Que porcentaje de alumnos han Aprobado*/

#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

// 

typedef struct dato{
	int dni;
	char apyn[50];
	int cantp;
	float calif;
}dato;

typedef struct nodoCola{
	struct dato d;
	struct nodoCola *sig;
}nodoCola;

typedef struct tipo_cola{
	nodoCola *inicio, *final;
}t_cola;

typedef struct listatp{
	struct dato datoAlum;
	struct listatp *sig;
}listatp;

// Declaro los subprogramas
void solicitoDatos(struct dato *d);
void crearCola(t_cola *cola);
void encolar(t_cola *cola, dato *d);
dato desencolar(t_cola *cola);
int estaVacia(t_cola cola);
listatp *listaVacia(listatp *cabeza);
void agregarAlista(listatp **cabeza, dato d);
float notaProm(int qtp);
int alumnosAprobados(listatp *cabeza);
int alumnosRepechaje(listatp *cabeza);
int cantTotaldeAlumnos(listatp *cabeza);

void clearBuffer() { //LIMPIA EL BUFFER ANTES DE LEER CARACTERES //GUSTAVO
	while(getchar() != '\n');
}

/*
dato Consultar(t_cola* cola){
	if(cola->inicio){
		return cola->inicio->d;
	}
}
//*/

void ImprimoLista(listatp *cabeza){ //PRUEBA DE IMPRESIÓN DE LISTA
	if(cabeza==0){
		printf("\nLista Vacia");
	}
	else{
		while(cabeza!=0){
			printf("\n%s",cabeza->datoAlum.apyn);
			printf("\n%f",cabeza->datoAlum.calif);
			cabeza=cabeza->sig;
		}
	}
}

int main(){
	listatp *lista;
	dato datoC, datoL, datoX/*VARIABLE PARA IMPRESION COLA*/;
	nodoCola *nodo;
	t_cola cola;
	crearCola(&cola);
	
	int continua = 1;
	
	lista = listaVacia(lista);
	
	//INICIO DE CARGA
	while(continua==1){
		
		solicitoDatos(&datoC);
		encolar(&cola, &datoC);
		
		printf("\n\nDesea ingresar otro Alumno (1-Si): ");
		scanf("%d",&continua);
	}
	
	while (!estaVacia(cola)){
		datoL=desencolar(&cola);
		agregarAlista(&lista, datoL);
	}
		
//	ImprimoLista(lista); //CONTROL IMPRESION DE LISTA ANTES DE INFORME FINAL
	printf("\n----------INFORME FINAL----------");
	printf("\nLa cantidad de alumnos que aprobaron es: %i", alumnosAprobados(lista));
	printf("\nLa cantidad de alumnos que van a repechaje son: %i", alumnosRepechaje(lista));
		
	return 0;
}


void solicitoDatos(struct dato *d){
	printf("\nIngrese el Dni del Alumno: ");
	scanf("%i", &d->dni);
	printf("\nIngrese el Apellido y Nombre del Alumno: ");
	scanf("%s",d->apyn);
	printf("\nIngrese la Cant. de TPs entregadospor el Alumno: ");
	scanf("%i",&d->cantp);
	d->calif = notaProm(d->cantp);
	printf("\nCalif: %.2f", d->calif);	
}

void crearCola(t_cola *cola){
	cola->inicio=NULL;
	cola->final=NULL;
}

listatp *listaVacia(listatp *cabeza){
	cabeza = NULL;
	return cabeza;
}

void encolar(t_cola *cola, dato *d){
	nodoCola *nuevo = (nodoCola*) malloc(sizeof(nodoCola));
	nuevo->d=*d;
	nuevo->sig=NULL;
	if(cola->inicio == NULL){
		cola->inicio=nuevo;
		cola->final=nuevo;
	}
	else{
		cola->final->sig=nuevo;
		cola->final=nuevo;
	}	
}


dato desencolar(t_cola *cola){ //problema al cargar la lista
	
	dato datoL;
	nodoCola *aux1;
	aux1=cola->inicio;
	cola->inicio = aux1->sig;
	datoL = aux1->d;
	free(aux1);
	return datoL;
}


int estaVacia(t_cola cola) {
	if (cola.inicio==NULL) { 
    		return 1; // TRUE
  	} else {
    		return 0; // FALSE
  	}
}

void agregarAlista(listatp **cabeza, dato d){
	listatp *nuevo = (listatp *)malloc(sizeof(listatp));
	nuevo->datoAlum=d;
	nuevo->sig=*cabeza;
	*cabeza=nuevo;
	
}

int alumnosAprobados(listatp *cabeza){
		if (cabeza!=NULL && ((cabeza->datoAlum.calif>79.99))){
			return alumnosAprobados(cabeza->sig) + 1;
		}
		else{
			return 0;
		}
	}
int cantTotaldeAlumnos(listatp *cabeza){
	if (cabeza!= NULL){
		return cantTotaldeAlumnos(cabeza->sig) + 1;
	}
	else{
		return 0;
	}
}

int alumnosRepechaje(listatp *cabeza){
		if (cabeza!=NULL && ((cabeza->datoAlum.calif<=79.99) && (cabeza->datoAlum.calif>=50))){
			return alumnosRepechaje(cabeza->sig) + 1;
		}
		else{
			return 0;
		}
	}

float notaProm(int qtp){
	float prom;
	prom = (((float)qtp)/10) * 100;
	return prom;
}
