	#include<conio.h>
	#include<stdlib.h>
	#include<stdio.h>
	
	
	/*El problema se basaba en una empresa de reparto, que realizaba la entrega de pedidos
	  entre distintas ciudades, o en la misma.
	  Constaba de crear una pila, a medida que los vehiculos llegaban al depósito General
	  y luego una vez finalizado el día una lista con los vehículos ordenados por idVehiculo.
	  Las esturcturas eran plantedas así como ID, lo que facilitaba el manejo de comparaciones y demás.
	  las consultas a resolver de manera recursiva al final eran:
	  	1) Obtener la cantidad de pedidos por vehículos.
		2) Obtener del total de entregas cuantas pertenecían a la misma ciudad.*/
		
	
	typedef struct pilaLlegada{
		int idGuia;
		int dniDestinatario;
		int idCiudadOrigen;
		int idCiudadDestino;
		int idVehiculo;
			struct pilaLlegada *sig;
	}pilaLlegada;
	
	typedef struct listaOrd{
		int idGuia;
		int dniDestinatario;
		int idCiudadOrigen;
		int idCiudadDestino;
		int idVehiculo;
			struct listaOrd *sig;
	}listaOrd;
	
	void iniciaPila(pilaLlegada **pila);
	listaOrd *listaVacia(listaOrd *cabeza);
	void cargaPila(pilaLlegada **pila,int idG, int dniDest, int idCO, int idCD, int idV);
	void desapiloPila(pilaLlegada **pila, listaOrd **cabeza);
	void insertarOrdenado(pilaLlegada *pila, listaOrd **cabeza);
	void obtengoDatos(int *idG, int *dniDest, int *idCO, int *idCD, int *idV);
	
	void paquetesPorVehic(listaOrd *cabeza);
	
	int cantEntregas(listaOrd *cabeza);
	int entregasMismaCiudad(listaOrd *cabeza);
	//void ImprimoLista(listaOrd *cabeza);
	
	int main(int argc, char *argv[]){
		int idG,dniDest,idCO,idCD,idV;
		int continuaDia=1;
		pilaLlegada *pilaIdV;
		listaOrd *cabezaIdVeh;
		iniciaPila(&pilaIdV);
		cabezaIdVeh = listaVacia(cabezaIdVeh);
		idG=0;
		dniDest=0;
		idCO=0;
		idCD=0;
		idV=0;
		while(continuaDia==1){
			obtengoDatos(&idG,&dniDest,&idCO,&idCD,&idV);
			cargaPila(&pilaIdV,idG,dniDest,idCO,idCD,idV);
			printf("\nDesea Continuar el Dia? (1)-SI: ");
			scanf("%i",&continuaDia);
		}
		desapiloPila(&pilaIdV,&cabezaIdVeh);
		//ImprimoLista(cabezaIdVeh);
		printf("\n----------------------------");
		printf("\n------INFORME DEL DIA-------");
		printf("\n----------------------------");
		printf("\nEl %% de entregas de la misma ciudad es: %.2f", (((float)entregasMismaCiudad(cabezaIdVeh)/(float)cantEntregas(cabezaIdVeh))*100));
		printf("\n");
		printf("\nLa cant. de entregas del mismo vehículo es: %i", entregasMismaCiudad(cabezaIdVeh));
		printf("\n");
		getch();
		return 0;
	}
	
	void iniciaPila(pilaLlegada **pila){
		*pila=NULL;
		
	}
	
	listaOrd *listaVacia(listaOrd *cabeza){
		cabeza = NULL;
		return cabeza;
	}
	
	void cargaPila(pilaLlegada **pila,int idG, int dniDest, int idCO, int idCD, int idV){
		
		pilaLlegada *nuevo=(pilaLlegada *)malloc(sizeof(pilaLlegada));
		
		nuevo->idGuia=idG;
		nuevo->dniDestinatario=dniDest;
		nuevo->idCiudadOrigen=idCO;
		nuevo->idCiudadDestino=idCD;
		nuevo->idVehiculo=idV;
		nuevo->sig=*pila;
		*pila=nuevo;
	}
	
	void desapiloPila(pilaLlegada **pila, listaOrd **cabeza){
		pilaLlegada *aux;
		
		while(*pila != NULL){
	        		aux=*pila;
	        		insertarOrdenado(aux, cabeza);
	            	*pila = aux->sig;
	            	free(aux); // libero el espacio
	        }
	
	}
	void insertarOrdenado(pilaLlegada *pila, listaOrd **cabeza){
		
		listaOrd *nuevo = (listaOrd *)malloc(sizeof(listaOrd));	
		struct listaOrd *ant;
		struct listaOrd *act;
		
			act = *cabeza;
			ant = NULL;
			
			nuevo->idGuia=pila->idGuia;
			nuevo->dniDestinatario=pila->dniDestinatario;
			nuevo->idCiudadOrigen=pila->idCiudadOrigen;
			nuevo->idCiudadDestino=pila->idCiudadDestino;
			nuevo->idVehiculo=pila->idVehiculo;
			nuevo->sig=NULL;
		
			while(act!=NULL && act->idVehiculo<nuevo->idVehiculo){   // ordeno por idVehiculo
				ant=act;
				act=act->sig;
			}
			if(ant!=NULL){		//Inserto en el cuerpo
				ant->sig=nuevo;
				nuevo->sig=act;
			}else{				//Inserto al inicio
				nuevo->sig=*cabeza;
				*cabeza=nuevo;
			}		
	}
	        		
	
	void obtengoDatos(int *idG, int *dniDest, int *idCO, int *idCD, int *idV){
		printf("\nIngrese el ID-Guia: ");
		scanf("%i", &*idG);
		printf("\nIngrese el DNI-Destinatario: ");
		scanf("%i", &*dniDest);
		printf("\nIngrese el ID-Ciudad Origen: ");
		scanf("%i", &*idCO);
		printf("\nIngrese el ID-Ciudad Destino: ");
		scanf("%i", &*idCD);
		printf("\nIngrese el ID-Vehículo: ");
		scanf("%i", &*idV);
	}
	
	
	int cantEntregas(listaOrd *cabeza){
		if (cabeza != NULL){
	  		return cantEntregas(cabeza->sig) + 1; 
		}
		else{
	
			return 0;
		}
	}
	
	int entregasMismaCiudad(listaOrd *cabeza){
		if (cabeza != NULL && (cabeza->idCiudadDestino==cabeza->idCiudadOrigen)){
			return entregasMismaCiudad(cabeza->sig) + 1;
		}
		else{
			return 0;
		}
	}

int cantPedxVehic(listaOrd *cabeza){
	if (cabeza != NULL && (cabeza->idVehiculo==cabeza->sig->idVehiculo)){
  		return cantPedxVehic(cabeza->sig) + 1; 
	}
	else{

		return 0;
	}
}

/*void ImprimoLista(listaOrd *cabeza){
	if(cabeza==0){
		printf("\nLista Vacia");
	}
	else{
		while(cabeza!=0){
			printf("\n%i",cabeza->idVehiculo);
			printf("\n%p",cabeza->sig);
			cabeza=cabeza->sig;
		}
	}
}*/
