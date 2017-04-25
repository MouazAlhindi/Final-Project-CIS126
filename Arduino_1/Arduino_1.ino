/*  Source Code for Arduino 1
 * This Arduino will be...
 * Sending an encrypted message
 * Sending an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */

//Variables
int reciverPin;
int senderPin;
char encryptedMessage[140];
char decryptedMessage[140];


//SEND METHODS

//Method that initiates sending sequence
void sendReadySignal(){
  digitalWrite(senderPin, HIGH);
  delay(500);
  digitalWrite(senderPin, LOW);
}

//Method to send a letter serially
void sendLetter(char x){
  String let = String(encode(x), BIN);

  if(let.length() == 8){
    for(int i = 0; let.length(); i++){
      if(let.equals("0")){
        digitalWrite(senderPin, HIGH);
        delay(500);
      } else {
        digitalWrite(senderPin, LOW);
        delay(500);
      }
      
    }
  }
  
}

//Method that will send the given char list
//via serial communication
void sendStringData(char letters[]){
  sendReadySignal();
  for(char c: letters){
    sendLetter(c);
  }
}

//RECIEVE METHODS

//Method that listens for correct ready signal
void listenReadySignal(){

}

//Methoda that will revieve in a serial communication pattern
void recieveStringData(){
  
}


//Setup method
void setup() {

  pinMode(reciverPin, INPUT);
  pinMode(senderPin, OUTPUT);
  
  Serial.begin(9600);

}

//Loop Method
void loop() {

}
