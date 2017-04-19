/*  Source Code for Arduino 2
 * This Arduino will be...
 * Reciving an encrypted message
 * Reciving an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */

String[] userList = new String[10];
int idCounter = 0;
boolean authorization = false;

//will take in a user ID and will allow access to the device
boolean authenticateUser(String u){
  for(String s: userList){
    if(s == u){
      idCounter++;
    }
  }

  if(idCounter == 10)
  {
    Serial.println("User Authentication: Access Granted");
    authorization = true;
  }

  return authorization;
}

void recieveStringData(){
  
}


void updateStringData(){
  
}



void sendStringData(){
  
}


void setup() {

  Serial.begin(9600);
}

void loop() {
 

}
