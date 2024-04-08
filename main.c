/*
Autore: Samuconfaa
Nome: Acchiappa la Talpa
Descrizione: Simula il gioco da luna park dove devi colpire i "topi" che sbucano fuori dai buchi. 
Versione: 1-BETA
*/


//dichiarazione dei pin

int pinBottoni[] = {2,3,4,5};
int pinLed[] = {6,7,8,9};
int pinBuzzer = 10;
int durataGioco = 30000;
int restart = 4000;             //tempo da aspettare prima di ricominciare la partita

bool gameRunning = false;
int score = 0;
unsigned long startTime = 0;

void setup(){
    
    //inizializzazione pin pulsanti
    for (int i = 0; i < 4; i++) {
        pinMode(pinBottoni[i], INPUT_PULLUP);           //pull_up serve a fare da resistenza interna per i pulsanti
    }

    //inizializzazione pin led
    for (int i = 0; i < 4; i++) {
        pinMode(pinLed[i], OUTPUT);
    }

    //inizializzazione pin buzzer
    pinMode(pinBuzzer, OUTPUT);

    //funzione per avviare il gioco
    startGame();
}

void loop(){
    if(gameRunning){

        unsigned long tempoTrascorso = millis() - startTime; //calcola il tempo trascorso dall'avio del gioco

        //generazione numero casuale per i led
        int rnd = random(0, 4);

        //accensione pin corrispondende al numero random
        digitalWrite(pinLed[rnd], HIGH);

        //aspetta un po
        delay(random(500,2000));
        
        for (int i = 0; i < 4; i++) {
            if (digitalRead(pinBottoni[i]) == HIGH && i == rnd) {
                score++; // aumenta il punteggio
                serial.print("+1");
                tone(pinBuzzer, 1000, 100); // suona il buzzer per indicare un colpo
            }
        }

        //spegne il led 
        digitalWrite(pinLed[rnd], LOW);


        if (tempoTrascorso >= durataGioco) {
            endGame();
        }
    }
}

void startGame() {
  gameRunning = true;
  score = 0;
  startTime = millis(); //memorizza il tempo di inizio del gioco
  Serial.begin(9600);
  Serial.println("Acchiappa la Talpa è iniziato!"); // stampa un messaggio iniziale
}

void endGame() {
  gameRunning = false;
  Serial.println("Tempo scaduto! Punteggio: " + String(score)); // stampa il punteggio finale
  
  // spegni tutti i LED
  for (int i = 0; i < 4; i++) {
    digitalWrite(pinLed[i], LOW);
  }
  
  // suona il buzzer per indicare la fine del gioco
  tone(pinBuzzer, 200, 1000);
  
  // aspetta un po' prima di iniziare una nuova partita
  delay(restart);
  
  // inizia una nuova partita
  startGame();
}