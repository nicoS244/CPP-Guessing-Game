#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
//IMPORTANTE: Linea 386, sirve para ver la respuesta correcta
struct nodo
{
	char premio[50]; //Almacena el nombre del hito
	struct nodo *sig; //Apuntador al nodo siguiente
	struct nodo *ant; //Apuntador al nodo anterior
};

int i;
int iPC=0; //Este valor sirve para que el premio que se añada a la lista cambie según el valor de esta variable
int itpj;
int puntosJ=0;//Almacena los puntos que va adquiriendo el jugador
int puntosAna=0; //Variable utilizada en la función analizarPuntos
int n_nodosPC=0; //Número de nodos en la lista del juego.
int n_nodosJug=0; //Número de nodos en la lista del jugador.
int n_juegos=0;
int x;

struct nodo *inicioJ=NULL; //Nodos de posición de la lista del jugador.
struct nodo *finalJ=NULL;

struct nodo *inicioPC=NULL; //Nodos de la posición de la lista del jugador.
struct nodo *finalPC=NULL;

/*Lista de los hitos a conseguir, el número a lado de ellos indica los puntos necesarios para obtenerlos*/
char ht1pc[]="Acero (100 puntos)"; //100
char ht2pc[]="Bronce III (200 puntos)"; //200
char ht3pc[]="Bronce II (300 puntos)"; //300
char ht4pc[]="Bronce I (400 puntos)"; //400
char ht5pc[]="Plata III (500 puntos)"; //500
char ht6pc[]="Plata II (600 puntos)"; //600
char ht7pc[]="Plata I (700 puntos)"; //700
char ht8pc[]="Oro III (800 puntos)"; //800 
char ht9pc[]="Oro II (900 puntos)"; //900
char ht10pc[]="Oro I (1000 puntos)"; //1000
char ht11pc[]="Diamante III (1500 puntos)"; //1500
char ht12pc[]="Diamante II (2000 puntos)"; //2000
char ht13pc[]="Diamante I (2500 puntos)"; //2500
char ht14pc[]="Maestro (5000 puntos)"; //5000
char ht15pc[]="Gran Maestro (10000 puntos)"; //10000

void juego(); //Inicializa el juego, genera el número aleatorio y manda a llamar a la función adivinar.
void salir(); //Sale del juego, manda a llamar a la función analizarPuntos e imprimirHitos.
void puntos(); //Imprime los puntos actuales del jugador.
void parpadeo(); //Realiza un parpadeo alternando entre blanco y negro
void parpadeoCorrecto(); //Realiza un parpadeo alternando entre verde y negro si la respuesta del jugador es correcta.
void parpadeoIncorrecto(); //Realiza un parpadeo alternando entre rojo y negro si la respuesta del jugador es incorrecta.
void pista(int); //Evalua el numero generado por la computadoray genera una pista segun el rango en el que este se encuentre.
void suspensivos(); //Imprime 5 puntos, 1 por segundo, simulando puntos suspensivos o una pantalla de carga.
void adivinar(int); //En esta funcion, el usuario ingresa su respuesta, tiene  hasta 3 intentos para responder correctamente, en cada intento se ofrecen pistas y los puntos a ganar disminuyen segun el intento que sea.
void addPC(); //Llena la lista de hitos del juego, se usan iteraciones para mandar a llamar a la función.
void imprimirHitosPC(); //Imprime la lista de hitos del juego.
void analizarPuntos(); //Analiza los puntos del jugador para determinar el limite de un ciclo for que añadira los premios del jugador en la funcion addJ.
void addJ(); //Se añaden los hitos que consigue el jugador según su puntuación.
void imprimirHitosJ(); //Se imprimen los hitos del jugador.

int main()
{
	int op;
	int ita;
	srand(time(NULL));
	for(ita=0;ita<15;ita++)//Se añaden los hitos a la lista de la computadora, para mostrarlos al usuario posteriormente
	{
		addPC();
	}
	printf("\tADIVINA EL NUMERO\n");
	printf("\tOPCIONES\n");
	printf("1. Jugar\n");
	printf("2. Salir\n");
	printf(">> ");
	scanf("%d",&op);
	if(op==1)
	{
		parpadeo();
		printf("\t\tEMPECEMOS\n\n\n");
		Sleep(1000);
		system("pause");
		parpadeo();
		imprimirHitosPC();
		Sleep(5000);
		system("pause");
		juego();
	}
	if(op==2)
	{
		salir();
	}
}

void analizarPuntos() //Se analiza la cantidad de puntos del jugador y se asigna un valor a la variable puntosAna según lo que se determine.
{
	if(puntosJ<100)
	{
		puntosAna=0;
	}
	if(puntosJ>=100 && puntosJ<200)
	{
		puntosAna=1;
	}
	if(puntosJ>=200 && puntosJ<300)
	{
		puntosAna=2;
	}
	if(puntosJ>=300 && puntosJ<400)
	{
		puntosAna=3;
	}
	if(puntosJ>=400 && puntosJ<500)
	{
		puntosAna=4;
	}
	if(puntosJ>=500 && puntosJ<600)
	{
		puntosAna=5;
	}
	if(puntosJ>=600 && puntosJ<700)
	{
		puntosAna=6;
	}
	if(puntosJ>=700 && puntosJ<800)
	{
		puntosAna=7;
	}
	if(puntosJ>=800 && puntosJ<900)
	{
		puntosAna=8;
	}
	if(puntosJ>=900 && puntosJ<1000)
	{
		puntosAna=9;
	}
	if(puntosJ>=1000 && puntosJ<1500)
	{
		puntosAna=10;
	}
	if(puntosJ>=1500 && puntosJ<2000)
	{
		puntosAna=11;
	}
	if(puntosJ>=2000 && puntosJ<2500)
	{
		puntosAna=12;
	}
	if(puntosJ>=2500 && puntosJ<5000)
	{
		puntosAna=13;
	}
	if(puntosJ>=5000 && puntosJ<10000)
	{
		puntosAna=14;
	}
	if(puntosJ>=10000)
	{
		puntosAna=15;
	}
}

void addJ()
{
	struct nodo *nuevoJ=(struct nodo*)malloc(sizeof(struct nodo));
	if(itpj==1)
	{
		strcpy(nuevoJ->premio,ht1pc);	//Se copia el valor de una cadena a nuevoJ->premio.
	}
	if(itpj==2)
	{
		strcpy(nuevoJ->premio,ht2pc);	
	}
	if(itpj==3)
	{
		strcpy(nuevoJ->premio,ht3pc);	
	}
	if(itpj==4)
	{
		strcpy(nuevoJ->premio,ht4pc);	
	}
	if(itpj==5)
	{
		strcpy(nuevoJ->premio,ht5pc);	
	}
	if(itpj==6)
	{
		strcpy(nuevoJ->premio,ht6pc);	
	}
	if(itpj==7)
	{
		strcpy(nuevoJ->premio,ht7pc);	
	}
	if(itpj==8)
	{
		strcpy(nuevoJ->premio,ht8pc);	
	}
	if(itpj==9)
	{
		strcpy(nuevoJ->premio,ht9pc);
	}
	if(itpj==10)
	{
		strcpy(nuevoJ->premio,ht10pc);
	}
	if(itpj==11)
	{
		strcpy(nuevoJ->premio,ht11pc);	
	}
	if(itpj==12)
	{
		strcpy(nuevoJ->premio,ht12pc);	
	}
	if(itpj==13)
	{
		strcpy(nuevoJ->premio,ht13pc);	
	}
	if(itpj==14)
	{
		strcpy(nuevoJ->premio,ht14pc);	
	}
	if(itpj==15)
	{
		strcpy(nuevoJ->premio,ht15pc);	
	}
	nuevoJ->sig=inicioJ;
	n_nodosJug++;
	if(inicioJ==NULL)
	{
		inicioJ=nuevoJ;
		finalJ=nuevoJ;
		nuevoJ->sig=inicioJ;
		nuevoJ->ant=finalJ;
	}
	else
	{
		nuevoJ->sig=inicioJ;
		nuevoJ->ant=finalJ;
		finalJ->sig=nuevoJ;
		finalJ=nuevoJ;
		inicioJ->ant=finalJ;
	}
}

void imprimirHitosJ() //Se imprimen los hitos/premios que obtuvo el jugador.
{
	struct nodo *actualJ;
	int posJ=1;
	actualJ=inicioJ;
	while(posJ<=n_nodosJug)
	{
		printf("%s\n",actualJ->premio);
		actualJ=actualJ->sig;
		posJ++;
	}
}

void addPC() 
{
	struct nodo *nuevoPC=(struct nodo*)malloc(sizeof(struct nodo));
	if(iPC==0)
	{
		strcpy(nuevoPC->premio,ht1pc);	
	}
	if(iPC==1)
	{
		strcpy(nuevoPC->premio,ht2pc);	
	}
	if(iPC==2)
	{
		strcpy(nuevoPC->premio,ht3pc);	
	}
	if(iPC==3)
	{
		strcpy(nuevoPC->premio,ht4pc);	
	}
	if(iPC==4)
	{
		strcpy(nuevoPC->premio,ht5pc);	
	}
	if(iPC==5)
	{
		strcpy(nuevoPC->premio,ht6pc);	
	}
	if(iPC==6)
	{
		strcpy(nuevoPC->premio,ht7pc);	
	}
	if(iPC==7)
	{
		strcpy(nuevoPC->premio,ht8pc);	
	}
	if(iPC==8)
	{
		strcpy(nuevoPC->premio,ht9pc);
	}
	if(iPC==9)
	{
		strcpy(nuevoPC->premio,ht10pc);
	}
	if(iPC==10)
	{
		strcpy(nuevoPC->premio,ht11pc);	
	}
	if(iPC==11)
	{
		strcpy(nuevoPC->premio,ht12pc);	
	}
	if(iPC==12)
	{
		strcpy(nuevoPC->premio,ht13pc);	
	}
	if(iPC==13)
	{
		strcpy(nuevoPC->premio,ht14pc);	
	}
	if(iPC==14)
	{
		strcpy(nuevoPC->premio,ht15pc);	
	}
	nuevoPC->sig=inicioPC;
	iPC++;
	n_nodosPC++;
	if(inicioPC==NULL)
	{
		inicioPC=nuevoPC;
		finalPC=nuevoPC;
		nuevoPC->sig=inicioPC;
		nuevoPC->ant=finalPC;
	}
	else
	{
		nuevoPC->sig=inicioPC;
		nuevoPC->ant=finalPC;
		finalPC->sig=nuevoPC;
		finalPC=nuevoPC;
		inicioPC->ant=finalPC;
	}
}

void imprimirHitosPC()
{
	struct nodo *actualPC;
	int posPC=1;
	actualPC=inicioPC;
	printf("----HITOS----\n");
	while(posPC<=n_nodosPC)
	{
		printf("%s\n",actualPC->premio);
		actualPC=actualPC->sig;
		posPC++;
	}
}

void puntos()
{
	printf("Puntos: %d\n",puntosJ);
}

void salir()
{
	system("cls");
	analizarPuntos();
	if(puntosAna>0)
	{
		for(itpj=1;itpj<=puntosAna;itpj++)
		{
			addJ();
		}
		printf("----HITOS ALCANZADOS----\n\n");
		imprimirHitosJ();
	}
	else
	{
		printf("No se alcanzo ningun hito.\n\n");
	}
	printf("FIN DEL JUEGO\n");
	suspensivos();
	printf("\n");
}

void adivinar(int numeroPC)
{
	system("cls");
	int numeroUsuario;
	printf("%cQu%c n%cmero estoy pensando?\n",168,130,163);
	//printf("%d\n",numeroPC); //PARA VER EL NUMERO
	printf(">> ");
	scanf("%d",&numeroUsuario);
	printf("Tu respuesta es\n");
	suspensivos();
	if(numeroUsuario==numeroPC)
	{
		parpadeoCorrecto();
		system("cls");
		printf("CORRECTA\n");
		puntosJ=puntosJ+100;
		printf("\n+ 100 puntos\n\n");
	}
	else
	{
		parpadeoIncorrecto();
		system("cls");
		printf("INCORRECTA\n");
		switch(x){
			case 1:
				if(numeroPC<=5){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 1 y el 5");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=3){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 1 y el 3");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 4 y el 5");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 6 y el 10");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=8){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 6 y el 8");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 9 y el 10");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 2:
				if(numeroPC<=15){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 11 y el 15");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=13){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 11 y el 13");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 14 y el 15");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 16 y el 20");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=18){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 16 y el 18");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 19 y el 20");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 3:
				if(numeroPC<=25){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 21 y el 25");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=23){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 21 y el 23");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 24 y el 25");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 26 y el 30");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=28){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 26 y el 28");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 29 y el 30");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 4:
				if(numeroPC<=35){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 31 y el 35");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=33){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 31 y el 33");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 34 y el 35");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 36 y el 40");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=38){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 36 y el 38");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 39 y el 40");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 5:
				if(numeroPC<=45){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 41 y el 45");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=43){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 41 y el 43");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 44 y el 45");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 46 y el 50");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=48){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 46 y el 48");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 49 y el 50");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 6:
				if(numeroPC<=55){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 51 y el 55");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=53){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 51 y el 53");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 54 y el 55");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 56 y el 60");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=58){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 56 y el 58");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 59 y el 60");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 7:
				if(numeroPC<=65){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 61 y el 65");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=63){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 61 y el 63");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 64 y el 65");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 66 y el 70");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=68){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 66 y el 68");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 69 y el 70");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 8:
				if(numeroPC<=75){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 71 y el 75");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=73){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 71 y el 73");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 74 y el 75");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 76 y el 80");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=78){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 76 y el 78");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 79 y el 80");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 9:
				if(numeroPC<=85){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 81 y el 85");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=83){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 81 y el 83");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 84 y el 85");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 86 y el 90");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=88){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 86 y el 88");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 89 y el 90");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			case 10:
				if(numeroPC<=95){
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 91 y el 95");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=93){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 91 y el 93");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 94 y el 95");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}	
				}else{
					printf("\nSegunda pista:");
					printf("\nEl numero esta entre el 96 y el 100");
					printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
					scanf("%d",&numeroUsuario);
					printf("Tu respuesta es\n");
					suspensivos();
					if(numeroUsuario==numeroPC){
						parpadeoCorrecto();
						system("cls");
						printf("CORRECTA\n");
						puntosJ=puntosJ+50;
						printf("\n+ 50 puntos\n");
					}else{
						parpadeoIncorrecto();
						system("cls");
						printf("INCORRECTA\n");
						if(numeroPC<=98){
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 96 y el 98");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}else{
							printf("\nTercera pista:");
							printf("\nEl numero esta entre el 99 y el 100");
							printf("\n%cQu%c n%cmero estoy pensando?\n",168,130,163);
							scanf("%d",&numeroUsuario);
							printf("Tu respuesta es\n");
							suspensivos();
							if(numeroUsuario==numeroPC){
								parpadeoCorrecto();
								system("cls");
								printf("CORRECTA\n");
								puntosJ=puntosJ+25;
								printf("\n+ 25 puntos\n");
							}else{
								parpadeoIncorrecto();
								system("cls");
								printf("INCORRECTA\n");
							}
						}		
					}
				}
				break;
				
			default:printf("\nError");
		}
	}
	system("pause");
	system("cls");
	system("COLOR 07");
	puntos();
	Sleep(1000);
	system("pause");
	system("cls");
	int op3;
	printf("%cQuieres jugar otra vez?\n");
	printf("1. Si\n");
	printf("2. No\n");
	Sleep(1000);
	printf(">> ");
	scanf("%d",&op3);
	if(op3==1)
	{
		juego();
	}
	if(op3==2)
	{
		salir();
	}
}

void pista(int numeroPC)
{
	printf("\n");
	if(numeroPC>=1 && numeroPC<11)
	{
		printf("El n%cmero que estoy pensando esta entre el 1 y el 10",163);
		x=1;
	}
	if(numeroPC>=11 && numeroPC<21)
	{
		printf("El n%cmero que estoy pensando esta entre el 11 y el 20",163);
		x=2;
	}
	if(numeroPC>=21 && numeroPC<31)
	{
		printf("El n%cmero que estoy pensando esta entre el 21 y el 30",163);
		x=3;
	}
	if(numeroPC>=31 && numeroPC<41)
	{
		printf("El n%cmero que estoy pensando esta entre el 31 y el 40",163);
		x=4;
	}
	if(numeroPC>=41 && numeroPC<51)
	{
		printf("El n%cmero que estoy pensando esta entre el 41 y el 50",163);
		x=5;
	}
	if(numeroPC>=51 && numeroPC<61)
	{
		printf("El n%cmero que estoy pensando esta entre el 51 y el 60",163);
		x=6;
	}
	if(numeroPC>=61 && numeroPC<71)
	{
		printf("El n%cmero que estoy pensando esta entre el 61 y el 70",163);
		x=7;
	}
	if(numeroPC>=71 && numeroPC<81)
	{
		printf("El n%cmero que estoy pensando esta entre el 71 y el 80",163);
		x=8;
	}
	if(numeroPC>=81 && numeroPC<91)
	{
		printf("El n%cmero que estoy pensando esta entre el 81 y el 90",163);
		x=9;
	}
	if(numeroPC>=91 && numeroPC<101)
	{
		printf("El n%cmero que estoy pensando esta entre el 91 y el 100",163);
		x=10;
	}
	printf("\n");
}

/*Los parpadeos funcionan de esta forma: system color permite asignar un color al fondo y a las letras del CMD, 
	el primer digito se refiere al fondo de la ventana, el segundo el de las letras (Usamos 0=Negro,7=Blanco,A=Verde Claro y 4=Rojo)
	La función Sleep sirve para hacer pausas dentro del programa, el valor entre parentesis es un valor en milisegundos, en este caso se 
	usan 250 milisegundos para hacer los cambios de color, creando asi el efecto parpadeante*/
void parpadeo()
{
	system("cls");
	system("COLOR 70");
	Sleep(250);
	system("COLOR 07");
	Sleep(250);
	system("COLOR 70");
	Sleep(250);
	system("COLOR 07");
	Sleep(250);
	system("COLOR 70");
	Sleep(250);
	system("COLOR 07");
	Sleep(250);
}

void parpadeoCorrecto()
{
	system("cls");
	system("COLOR A0");
	Sleep(250);
	system("COLOR 0A");
	Sleep(250);
	system("COLOR A0");
	Sleep(250);
	system("COLOR 0A");
	Sleep(250);
	system("COLOR A0");
	Sleep(250);
	system("COLOR 0A");
	Sleep(250);
}

void parpadeoIncorrecto()
{
	system("cls");
	system("COLOR 40");
	Sleep(250);
	system("COLOR 04");
	Sleep(250);
	system("COLOR 40");
	Sleep(250);
	system("COLOR 04");
	Sleep(250);
	system("COLOR 40");
	Sleep(250);
	system("COLOR 04");
	Sleep(250);
}

/*Los puntos suspensivos funcionan de esta forma, se hace una pausa de 1 segundo y se imprime un punto, se repite el ciclo y se hace la mismo, se espera un 1 segundo
y se imprime un punto y asi sucesivamente hasta terminar el ciclo for, con esto se logra un efecto similar al de una pantalla de carga o de puntos suspensivos.*/
void suspensivos()
{
	for(i=0;i<5;i++)
	{
		Sleep(1000);
		printf(". ");
	}
}

void juego()
{
	parpadeo();
	int numeroPC;
	puntos();
	printf("Tienes que adivinar el n%cmero que estoy pensando.\n",163);
	printf("Es un n%cmero entre el 1 y el 100.\n",163);
	Sleep(2000);
	printf("%cListo?\n",168);
	system("pause");
	system("cls");
	printf("Bien, dejame pensar\n");
	suspensivos();
	printf("\n");
	numeroPC=1+rand()%(100-1+1);
	Sleep(1000);
	printf("Bien, ya tengo un n%cmero.\n",163);
	Sleep(1000);
	system("cls");
	printf("Primer pista.\n");
	suspensivos();
	Sleep(1000);
	pista(numeroPC);
	system("pause");
	adivinar(numeroPC);	
}