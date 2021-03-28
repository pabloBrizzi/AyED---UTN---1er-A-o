/*------------PROGRAMA PRIMER PARCIAL: PABLO BRIZZI-----------*/

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>


/*--------------------DATOS ENUNCIADO-----------------------

   15 Diferentes Tipos de Barbijos
   N° de piezas diferentes e/barbijos. de entre 20 piezas.
   Cada barbijo solo cuenta con 1 pieza distinta.
   
   --------------------SOLICITUDES-------------------------
1.   En primer lugar se procederá a la lectura de la información que 
     indican cuáles son las piezas de cada barbijo. 
     El usuario introducirá la información relativos a los 15 tipos diferentes, 
     indicando primero el número de piezas que tiene.

2.  A continuación, se deberá tener en cuenta que la producción del mes termina 
    cuando se trabaja un ciclo de 20 días donde en cada día se leer la cantidad 
    de barbijos que se confeccionaran.

3. Para realizar los pedidos correspon	dientes, se deben contar el número de 
   piezas que se necesitan cada mes y escribirlos en la pantalla.

4. El programa deberá determinar sobre el total de piezas que conforman el 
   barbijo que porcentaje corresponde a cada pieza sobre el total utilizado en el mes.
   
*/

//---------------------DEFINO LAS CONSTANTES-----------------------

#define tipoB 2 //PASAR A 15 --- Tipo de barbijos
#define tipoP 3 //PASAR A 20 ---- Tipo de piezas
#define cicloProd 2 //PASAR A 20 ---- Cant de días del ciclo de Prod

//-------------------DECLARO LOS PROCEDIMIENTOS---------------------

void inicializar(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP], int tb, int tp); //Procedimiento de inicializacion de matrices y Vectores
void piezXbarb(int m[tipoB][tipoP], int tb, int tp); //proc. donde identifico el tipo de pieza por barbijo asignando un 1 en el casillero de la matriz correspondiente al tipo de barbijo y tipo de pieza
void lectProdDiaria(int vecB[tipoB],int tb, int dia);//proc. que lee la producción diaria de barbijos y los guarda en el vector produccion
void contarPieza(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP],int tb,int tp); // proc. que calcula la cantidad de piezas mensuales necesarias conforme la identificación en la matriz de "piezaXbarbijo" y la cantidad de barbijos a producir por tipo cargada
void informePiezas(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP],int tb,int tp); // Impresión del % de pieza por barbijo sobre el total de piezas del mes
float promTotalP(int vecB[tipoB],int vecP[tipoP], int b, int p); //Funcion que calcula el % de la participacion de cada pieza por barbijo del total de piezas a utilizar en el mes
int main(){
	int piezaXbarbijo[tipoB][tipoP];
	int prodMensual[tipoB], cantPiezas[tipoP];
	int i, nuevoMes;
	nuevoMes=1;
	while(nuevoMes==1){
		inicializar(piezaXbarbijo,prodMensual,cantPiezas,tipoB,tipoP);
		piezXbarb(piezaXbarbijo,tipoB,tipoP);
		for(i=0;i<cicloProd;i++){
			lectProdDiaria(prodMensual,tipoB,i);
		}
		contarPieza(piezaXbarbijo,prodMensual,cantPiezas,tipoB,tipoP);
		informePiezas(piezaXbarbijo,prodMensual,cantPiezas,tipoB,tipoP);
		
		printf("\n");	
		printf("\nDesea Cargar otro mes? (1-Si): ");
		scanf("%d",&nuevoMes);
	}
	system("cls");
	
	
	return 0;
}

void inicializar(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP], int tb, int tp){
	int i,j;
	for(i=0;i<tb;i++){
		vecB[i]=0;
		for(j=0;j<tp;j++){
			vecP[j]=0;
			m[i][j]=0;
		}
	}
}

void piezXbarb(int m[tipoB][tipoP], int tb, int tp){
	int i,j,cantP, codTP;
	for (i=0;i<tb;i++){
		printf("\nIngrese la cantidad de piezas del Barbijo %i: ",(i+1));
		scanf("%d",&cantP);
		for(j=0;j<cantP;j++){
			printf("\nIngrese el cod de la pieza %i del barbijo %i: ",(j+1),(i+1));
			scanf("%d",&codTP);
			m[i][(codTP-1)] = 1;
		}
	}
	
}
void lectProdDiaria(int vecB[tipoB],int tb, int dia){
	int i, cantProd;
	printf("\n--- PRODUCCION DIA %i ------",(dia+1));
	for (i=0;i<tb;i++){
		printf("\nIngrese la cantidad a producir del Barbijo %i: ",(i+1));
		scanf("%d",&vecB[i]);
	}
}
void contarPieza(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP],int tb, int tp){
	int i,j;
	for (i=0;i<tb;i++){
		for (j=0;j<tp;j++){
			if(m[i][j]==1){
				vecP[j]+=vecB[i];
			}
		}	
	}
	printf("\n");
	printf("\n-------TOTALES POR PIEZA--------");
	for(i=0;i<tp;i++){
		printf("\n");
		printf("\nTotal necesario pieza %i: %i",(i+1),vecP[i]);
	}
}
void informePiezas(int m[tipoB][tipoP],int vecB[tipoB],int vecP[tipoP],int tb,int tp){
	int i,j;
	printf("\n");
	printf("\n-----INFORME PROMEDIOS------");
	for(i=0;i<tb;i++){
		for(j=0;j<tp;j++){
			if(m[i][j]==1){
				printf("\n");
				printf("\n BARBIJO %i",(i+1));
				printf("\n Pieza %i: %.2f %%",(j+1),promTotalP(vecB,vecP,i,j));
			}
		}
	}
	
}
float promTotalP(int vecB[tipoB],int vecP[tipoP], int b, int p){
	float prom;
	prom = (float)vecB[b]/(float)vecP[p] * 100;
	return prom;
}
