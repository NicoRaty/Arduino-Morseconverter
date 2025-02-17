//This code is a translator for inputs from buttons in morse code to letters in the alphabet
float pressLength_milliSeconds = 0; //press duration of the button
int optionOne_milliSeconds = 10; // short press of the button
int optionTwo_milliSeconds = 200; // long press of the button       
int char_time = 5000; // amount of time that the user has to input morse code corresponding to one letter
int buttonPin = 2; 
int ledPin_green = 13;
int ledPin_red = 12;
int buzzerpin = 6;
boolean buttonState;
unsigned long StartTime; // creates variable for start time
String Code = ""; // creates an empty string for the input morse code to go to
const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; 
const String morseCodes[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

char Code_Char(String str){ // method to convert the morse code to a letter
  int size = sizeof(morseCodes)/sizeof(morseCodes[0]); //get size of array
    for (int i = 0; i < size; i++) {  //iterates through the array
      if (morseCodes[i] == str) { //finds the corresponding letter
        return letters[i]; //returns the letter
      }
    }
    return ' '; //if it doesnt find it, it will return a space
}


void setup(){
  pinMode(buttonPin, INPUT_PULLUP); // sets the initial state of the button to HIGH   
  pinMode(ledPin_green, OUTPUT); // declares the green light as output
  pinMode(ledPin_red, OUTPUT); // declares the red light as output
  Serial.begin(9600); // starts serial communication
  Serial.println("Hello welcome to our morsecode converter!"); //intro message
  Serial.println("You have 5 seconds to enter your input"); //intro message
  Serial.println("Short press of the button results in \".\" and long press (at least a second) results in \"-\""); //intro message
  Serial.println("Have fun :)"); //intro message
  StartTime = millis(); //sets our starting time as the current milliseconds                                 
} 


void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    delay(10);
    noTone(buzzerpin);
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {
      tone(buzzerpin, 600);
      delay(10);
      return;
    }

  }
  while (digitalRead(buttonPin) == LOW ){ //when reading state of LOW button is pressed
    delay(10); //delays the execution of code for  100 milliseconds
    pressLength_milliSeconds = pressLength_milliSeconds + 10;//while button is pressed we are adding up on our time counter
  }
  if (pressLength_milliSeconds >= optionTwo_milliSeconds){ //checks if the button has been pressed for at least a second
    digitalWrite(ledPin_red, HIGH); //turns on the red light
    Code += "-"; // adds the - to our code string
    Serial.println("Added: - ");
    digitalWrite(ledPin_red, LOW); //turns off the light
  }

  else if(pressLength_milliSeconds >= optionOne_milliSeconds){//checks if the button has been pressed for less than a second
    digitalWrite(ledPin_green, HIGH); //turns on the green light
    Code += ".";// adds the . to our code string
    Serial.println("Added: . ");
    digitalWrite(ledPin_green, LOW);//turns off the light
  }
  
  
  if(millis()-StartTime >= 5000){ //if the duration of 15 seconds has passed
    StartTime=millis(); // start time will be set to the current time
    if(Code!=""){ // if our code string isnt empty (the user entered some kind of text)
    Serial.println("You entered: " + Code); //prints out what input we recorded
    char res = Code_Char(Code); // creates a variable that holds the translated letter
    if(res == ' '){ // if said variable is empty or is just a space, meaning the input has no translation
      Serial.println("Invalid input. Try again :)");// prints out this text
    }else{ // otherwise it prints out the translation
      Serial.print("Translated: ");
      Serial.println(res);
      Serial.println("Good job :)");
    }
    Code=""; // resets our string every 15 seconds so that the user may enter a new code
    }
  }
  pressLength_milliSeconds = 0; // resets our timer
} 