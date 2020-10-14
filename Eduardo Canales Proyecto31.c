#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

// Declaración de variables globales
// Nombre Jugador
char Name[] = "";
// Vectores para las cartas
char Values[12] = "A23456789JQK";
char *Suits[] = {"Picas", "Corazones", "Treboles", "Diamantes"};
// Ramdomizers
int RandValue;
int RandSuit;
// Barajas
int PlayerValDeck[10];
int PlayerSuitDeck[10];
int DealerValDeck[10];
int DealerSuitDeck[10];
int FullValueDeck[20];
int FullSuitDeck[20];
//Otras variables
int i = 0; // Contador para cartas repartidas
int x = 0; // Contador para comparar cartas
int y = 0; // Contador para mostrar cartas
int playerCards = 0; // Contador de cartas recibidas por el jugador
int DealerCards = 0; // Contador de cartas recibidas por el banquero
int playerContinue = 0; // Variable para consultar si el jugador desea continuar
int DealerContinue = 1; // variable para verificar si el banquero debe continuar
int PlayerScore = 0; // Puntaje del jugador
int DealerScore = 0; // Puntaje del Banquero
int AceValue; // Valor de As
int Points; //Puntos
int ValueComparer; // Comparador de valores
int SuitComparer; // Comparador de palo
int newGame = 0;
int loses = 0; // Número de partidas perdidas
int draws = 0; //Número de partidas empatadas
int wins = 0; //Número de partidas ganadas
// Declaración de métodos
void Deal();
void Point();
void Winner();

Deal(){
	if(i == 0){
		RandValue = rand() % 12;
		RandSuit = rand() % 4;
		FullValueDeck[i] = RandValue;
		FullSuitDeck[i] = RandSuit;
	}
	else{
		for(x = 0; x < i; x++){
			if((RandValue == FullValueDeck[x]) && (RandSuit == FullSuitDeck[x])){
				RandValue = rand() % 12;
				RandSuit = rand() % 4;
				x = 0;
			}
		}
		FullValueDeck[i] = RandValue;
		FullSuitDeck[i] = RandSuit;
	}
	Point();
	i++;
}

Point(){
	if(FullValueDeck[i] > 0 && FullValueDeck[i] < 9){
		Points = FullValueDeck[i] + 1;
	}
	else if(FullValueDeck[i] == 0 && playerContinue == 1){
		printf("Usted posee un As, desea que tenga valor de 1 (Ingrese 1) o de 11 (Ingrese otro numero): ");
		scanf("%d", &AceValue);
		if(AceValue == 1){
			Points = 1;
		}
		else{
			Points = 11;
		}
	}
	else if(FullValueDeck[i] == 0 && playerContinue == 0){
		Points = 11; 
	}
	else{
		Points = 10;
	}
	
}

Winner(){
	if(PlayerScore > 31){
		printf("\nEl banquero ha ganado.");
		loses += 1;
	}
	
	else if(DealerScore > 31){
		printf("\nEl jugador ha ganado.");
		wins += 1;
	}
	
	else if(PlayerScore > DealerScore){
		printf("\nEl jugador ha ganado.");
		wins += 1;
	}
	
	else if(PlayerScore < DealerScore){
		printf("\nEl banquero ha ganado.");
		loses += 1;
	}
	
	else{
		printf("\nEs un empate.");
		draws += 1;
	}
}

int main(){
	//Inicializamos el randomizador
    srand(time(0)); 
    
    //Solicitamos ingresar nombre al usuario
    printf("Ingrese su nombre para comenzar: ");
    scanf("%s", &Name);
    
    do{
    	// Inicializamos todas las variables
    	i = 0;
		x = 0;
		y = 0;
		playerCards = 0; 
		DealerCards = 0; 
		playerContinue = 0; 
		DealerContinue = 1; 
		PlayerScore = 0; 
		DealerScore = 0; 
		AceValue; 
		Points; 
		ValueComparer;
		SuitComparer;
		newGame = 0;
    	
		// Limpiamos la consola
	    system("cls");
	    
	    // Saludamos al jugador
	    printf("Bienvenido %s, estás a punto de iniciar una partida de 31: \n");
	    
	    // Repartimos las cartas al jugador
	    for(i = 0; i < 3; i){
	    	playerContinue = 1;
	    	Deal();
	    	playerCards += 1;
	    	PlayerScore += Points;
		}
		for(y = 0; y < playerCards; y++){
	    	ValueComparer = FullValueDeck[y];
	    	SuitComparer = FullSuitDeck[y];
	    	printf("\nSu carta %d es: %c de %s", y, Values[ValueComparer], Suits[SuitComparer]);	
		}
		printf("\nSu puntaje actual es: %d\n", PlayerScore);
		if(PlayerScore < 31){
			printf("Ingrese 1 si desea continuar. Cualquier otro valor para finalizar: ");
			scanf("%d", &playerContinue);
		}
		else{
			playerContinue = 0;
		}
		while(playerContinue == 1 && PlayerScore <= 30){
	    	Deal();
	    	playerCards += 1;
	    	PlayerScore += Points;
	    	for(y = 0; y < playerCards; y++){
		    	ValueComparer = FullValueDeck[y];
		    	SuitComparer = FullSuitDeck[y];
		    	printf("\nSu carta %d es: %c de %s", y, Values[ValueComparer], Suits[SuitComparer]);	
			}
			printf("\nSu puntaje actual es: %d\n", PlayerScore);
			if(PlayerScore > 30){
				playerContinue = 0;
				break;
			}
			printf("Ingrese 1 si desea continuar. Cualquier otro valor para finalizar\n");
			scanf("%d", &playerContinue);
		}
		playerContinue = 0;	
		
		
		//Repartimos al Banquero
		for(i = playerCards; i < (playerCards + 3); i){
			Deal();
			DealerCards += 1;
	    	DealerScore += Points;
		}
		
		
		while(DealerScore < 26 && PlayerScore < 31){
	    	Deal();
	    	DealerCards += 1;
			DealerScore += Points;	
		}
		
		printf("%d %d %d %s %d %d", playerCards, DealerCards, i, Name, PlayerScore, DealerScore);
	    
	    for(y = 0; y < playerCards; y++){
	    	ValueComparer = FullValueDeck[y];
	    	SuitComparer = FullSuitDeck[y];
	    	printf("\nSu carta %d es: %c de %s", (y + 1), Values[ValueComparer], Suits[SuitComparer]);	
		}
		printf("\nSu puntaje actual es: %d\n", PlayerScore);
		for(y = 0; y < DealerCards; y++){
	    	ValueComparer = FullValueDeck[y + playerCards];
	    	SuitComparer = FullSuitDeck[y + playerCards];
	    	printf("\nLa carta %d del banquero es: %c de %s", (y + 1), Values[ValueComparer], Suits[SuitComparer]);
		}
		printf("\nEl puntaje actual del banquero es: %d\n", DealerScore);	
		
		// Para generar al ganador nos dirigimos a la función Winner
		Winner();
		printf("\nSi desea iniciar una nueva partida ingrese 1, ingrese cualquier otro valor para finalizar: ");
		scanf("%d", &newGame);
	}while(newGame == 1);
	printf("\nEl número de partidas ganadas es: %d", wins);
	printf("\nEl número de partidas empatadas es: %d", draws);
	printf("\nEl número de partidas perdidas es: %d", loses);
	return 0;
}

