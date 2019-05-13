/* Barnacle Budd's Morse Code Decoder v. 0.1
   (c) 2011, Budd Churchward - WB7FHC
   
   Hook a button or telegraph key up to your Arduino
   and this program will copy your Morse Code and display
   the characters in your Monitor window.
   
   The program will automatically adjust to the speed of code that
   you are sending. The first few characters may come out wrong.
   
   The software tracks the speed of the sender's dahs to make
   its adjustments. The more dahs you send at the beginning
   the sooner it locks into solid copy.
   
   After a reset, the following text is very difficult to lock in on:
   'SHE IS HIS SISTER' because there are only two dahs in the whole
   phrase and they come near the end. However, if you reset and then
   send 'CALL ME WOODY' it will match your speed quite quickly.
*/



int myKey=14;    // We are borrowing Analog Pin 0 and using it as digital
int speaker=11;  // Speaker will be hooked between pin 11 and ground

int val=0;                   // A value for key up and down
int myTone=440;              // Frequency of our tone

boolean ditOrDah=true;       // We have a full dit or a full dah
int dit=100;                 // If we loop less than this with keydown it's a dit else a dah
int averageDah=150;          // Start with this value we will adjusted it each time he sends a dah


boolean characterDone=true;  // A full character has been sent
int myBounce=2;              // Handles normal keybounce but we needed to do more later
int downTime=0;              // We are going to count the cycles we loop while key is down

long FullWait=10000;     // This value will be set by the sender's speed - the gap between letters
long WaitWait=FullWait;  // WaitWait is for the gap between dits and dahs
long newWord=0;          // For the gap between words

int nearLineEnd=60;      // How far do you want to type across your monitor window?
int letterCount=0;       // To keep track of how many characters have been printed on the line

int myNum=0;  // We will turn the dits and dahs into a data stream and parse
              // a value that we will store here

// The place a letter appears here matches the value we parse out of the code
char mySet[] ="##TEMNAIOGKDWRUS##QZYCXBJP#L#FVH09#8###7#######61#######2###3#45";



void setup() {
  pinMode(myKey, INPUT);
  pinMode(speaker,OUTPUT);
  // initialize the serial communication:
  Serial.begin(9600);
}



 void loop() {
   val=digitalRead(myKey);  // Is it up or is it down?
   if (val) keyIsDown();    // Any value here means it is down.
   if (!val) keyIsUp();     // Should be 0 when it is up.
 }
 
 void keyIsDown() {
   tone(speaker,myTone);  // Turn on the sound
   WaitWait=FullWait;     // Reset our Key Up countdown
   downTime++;   //Count how long the key is down

  if (myNum==0) {       // myNum will equal zero at the beginning of a character
      myNum=1;          // This is our start bit  - it only does this once per letter
    }

  characterDone=false;  // we aren't finished with the character yet, there could be more
  ditOrDah=false;       // we don't know what it is yet - key is still down
  delay(myBounce);      // short delay to keep the real world in synch with Arduino
 }

 void keyIsUp() {
   noTone(speaker);     // Turn off the sound
  if (newWord>0) newWord--;     // Counting down to spot gap between words
  if (newWord==1) printSpace(); // Found the gap, print a space but only once next time it will be 0

  if (!ditOrDah) {              // We don't know if it was a dit or a dah yet, so ...
      shiftBits();              // let's go find out! And do our Magic with the bits
    }
    
  if (!characterDone) {
      WaitWait--;               // We are counting down 
      if (WaitWait==0) {        // Bingo, keyUp just timed out! A full letter has been sent
        WaitWait=FullWait;      // Reset our  keyUp counter
        printCharacter();       // Go figure out what character it was and print it
        
        characterDone=true;     // We got him, we're done here
        myNum=0;                // This sets us up for getting the next start bit
      }
      downTime=0;               // Reset our keyDown counter
   }
}

void printSpace() {
  letterCount++;                  // we're counting the number of characters on the line  
  if (letterCount>nearLineEnd) {  // when we get past our threshold we do this:
    Serial.println();             // jump down to a new line
    letterCount=0;                // reset our character counter
    return;                       // Go back to loop(), we're done here.
  }  
  Serial.print(' ');              // print a space on the monitor window
}

void printCharacter() {           
  FullWait=averageDah*100;        // the keyUp counter gets reset based on sender's speed
  newWord=FullWait*5;             // word gap counter is also adjusted by sender's speed
  letterCount++;                  // we're counting the number of characters on the line
  if (myNum>63) {  
    printPunctuation();           // The value we parsed is bigger than our character array
                                  // It is probably a punctuation mark so go figure it out.
                                  
    return;                       // Go back to the main loop(), we're done here.
  }

  Serial.print(mySet[myNum]);     // Print the letter that is in this spot in our character set
}



void printPunctuation() {
  byte pMark='#'; // Just in case nothing matches
  if (myNum==71) pMark=':';
  if (myNum==76) pMark=',';
  if (myNum==84) pMark='!';
  if (myNum==94) pMark='-';
  if (myNum==101) pMark='@';
  if (myNum==106) pMark='.';
  if (myNum==115) pMark='?';
  Serial.print(pMark);   // print the punctuation mark
}

void shiftBits() {
  ditOrDah=true;        // we will know which one in two lines
  if (downTime<dit/3) return;  // ignore my keybounce
  if (downTime<dit) {
    // We got a dit
    myNum = myNum << 1;  // shift bits left
    myNum++;             // add one because it is a dit
  }
  else {
    // We got a dah
    myNum = myNum << 1; // shift bits left
    
    // The next three lines handle the automatic speed adjustment:
    averageDah=(downTime+averageDah)/2;  // running average of dahs
    dit=averageDah/3;                    // normal dit would be this
    dit=dit*2;                           // double it to get the threshold between dits and dahs
  }
}
