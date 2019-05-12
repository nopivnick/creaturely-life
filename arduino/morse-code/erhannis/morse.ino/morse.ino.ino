/* Attributions:

   The vast majority of code below was taken from Erhannis's patched version of Matthias Esterl's morse.ino sketch for Arduino.
   https://gist.github.com/Erhannis/17de678c9b6ac4d75ffa585156f513b8
*/

//Define the LED Pin
#define PIN_OUT        9
//Define unit length in ms
#define UNIT_LENGTH    100

//Build a struct with the morse code mapping
static const struct {
  const char letter, *code;
} MorseMap[] =
{
  { 'A', ".-" },
  { 'B', "-..." },
  { 'C', "-.-." },
  { 'D', "-.." },
  { 'E', "." },
  { 'F', "..-." },
  { 'G', "--." },
  { 'H', "...." },
  { 'I', ".." },
  { 'J', ".---" },
  { 'K', "-.-" },
  { 'L', ".-.." },
  { 'M', "--" },
  { 'N', "-." },
  { 'O', "---" },
  { 'P', ".--." },
  { 'Q', "--.-" },
  { 'R', ".-." },
  { 'S', "..." },
  { 'T', "-" },
  { 'U', "..-" },
  { 'V', "...-" },
  { 'W', ".--" },
  { 'X', "-..-" },
  { 'Y', "-.--" },
  { 'Z', "--.." },
  { ' ', "     " }, //Gap between word, seven units

  { '1', ".----" },
  { '2', "..---" },
  { '3', "...--" },
  { '4', "....-" },
  { '5', "....." },
  { '6', "-...." },
  { '7', "--..." },
  { '8', "---.." },
  { '9', "----." },
  { '0', "-----" },

  { '.', ".-.-.-" },
  { ',', "--..--" },
  { '?', "..--.." },
  { '!', "-.-.--" },
  { ':', "---..." },
  { ';', "-.-.-." },
  { '(', "-.--." },
  { ')', "-.--.-" },
  { '"', ".-..-." },
  { '@', ".--.-." },
  { '&', ".-..." },
};

void doMorse(int pin, const char *string) {
  size_t i, j;

  for ( i = 0; string[i]; ++i )
  {
    for ( j = 0; j < sizeof MorseMap / sizeof * MorseMap; ++j )
    {
      if ( toupper(string[i]) == MorseMap[j].letter )
      {
        emitMorse(pin, MorseMap[j].code);
        break;
      }
    }
    emitMorse(pin, "  "); //Add tailing space to separate the chars
  }
}

void emitMorse(int pin, const char *morseString) {
  for (int i = 0; morseString[i]; i++)
  {
    switch ( morseString[i] )
    {
      case '.': //dit
        digitalWrite( pin, HIGH );
        delay( UNIT_LENGTH );
        digitalWrite( pin, LOW );
        delay( UNIT_LENGTH );

        break;

      case '-': //dah
        digitalWrite( pin, HIGH );
        delay( UNIT_LENGTH * 3 );
        digitalWrite( pin, LOW );
        delay( UNIT_LENGTH );

        break;

      case ' ': //gap
        delay( UNIT_LENGTH );
    }
  }
}

void setup()
{
  pinMode( PIN_OUT, OUTPUT );
  digitalWrite( PIN_OUT, LOW );
}

void loop()
{
  doMorse(PIN_OUT, "SOS ");
}
