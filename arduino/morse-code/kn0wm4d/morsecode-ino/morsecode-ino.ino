/* Attributions:

   The vast majority of code below was taken from Xavi Álvarez (kn0wm4d)'s morsecode-ino sketch for Arduino.
   https://github.com/kn0wm4d/morsecode-ino
*/

#include <LiquidCrystal_I2C.h>

/* @XaviAlvarez
   Este sketch es un traductor de texto (introducido via serial) a código morse.
     1) Convierte los carácteres ASCII del puerto serie a código morse (que se interpreta por la iluminación de un led)
     2) Interpreta las pulsaciones y hace el proceso inverso (lo convierte a carácteres ASCII)
*/

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int PUNT = 1;
const int RAYA = 2;
const int PAUSA = 0;
const int DURACIO_PUNT = 200;               // Duració d'un PUNT.
const int DURACIO_RAYA = 600;               // Duració d'una raya.
const int SALT = 200;                // SALT entre senyals.
const int SALT_LLETRA = 600;         // SALT entre 2 lletres
const int SALT_PARAULA = 1400;       // SALT entre 2 paraules.
const int LED = 10;
const int BOTO = 8;

boolean Polsador = false;        // Indica si s'ha polsat el botó
long duracioAnterior = 0;                  // Ultim timestamp
byte senyalEntrada[5];                     // Buffer de senyals d'entrada (per descodificar)
int senyalEntradaIndex = 0;                // Index de l'array de senyals d'entrada

void resetSenyalEntrada() {                // Reseteja el buffer de senyals
  senyalEntrada[0] = 0;
  senyalEntrada[1] = 0;
  senyalEntrada[2] = 0;
  senyalEntrada[3] = 0;
  senyalEntrada[4] = 0;
  senyalEntradaIndex = 0;
}
// return true si la senyal d'entrada es valida
boolean comprovaSenyalEntrada(byte s0, byte s1, byte s2, byte s3, byte s4) {
  return ((senyalEntrada[0] == s0) &&
          (senyalEntrada[1] == s1) &&
          (senyalEntrada[2] == s2) &&
          (senyalEntrada[3] == s3) &&
          (senyalEntrada[4] == s4));
}

// Procediment que converteix senyal d'entrada a lletra
char senyalEntradaALletra() {
  if (comprovaSenyalEntrada(PUNT, RAYA, PAUSA, PAUSA, PAUSA))  {
    return 'A';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, PUNT, PUNT, PAUSA))    {
    return 'B';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, RAYA, PUNT, PAUSA))   {
    return 'C';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, PUNT, PAUSA, PAUSA))   {
    return 'D';
  }
  if (comprovaSenyalEntrada(PUNT, PAUSA, PAUSA, PAUSA, PAUSA))  {
    return 'E';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, RAYA, PUNT, PAUSA))    {
    return 'F';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, PUNT, PAUSA, PAUSA))  {
    return 'G';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, PUNT, PAUSA))     {
    return 'H';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PAUSA, PAUSA, PAUSA))   {
    return 'I';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, RAYA, RAYA, PAUSA))  {
    return 'I';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, RAYA, PAUSA, PAUSA))  {
    return 'K';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, PUNT, PUNT, PAUSA))    {
    return 'L';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, PAUSA, PAUSA, PAUSA)) {
    return 'M';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, PAUSA, PAUSA, PAUSA))  {
    return 'N';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, RAYA, PAUSA, PAUSA)) {
    return 'O';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, RAYA, PUNT, PAUSA))   {
    return 'P';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, PUNT, RAYA, PAUSA))  {
    return 'Q';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, PUNT, PAUSA, PAUSA))   {
    return 'R';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, PAUSA, PAUSA))    {
    return 'S';
  }
  if (comprovaSenyalEntrada(RAYA, PAUSA, PAUSA, PAUSA, PAUSA)) {
    return 'T';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, RAYA, PAUSA, PAUSA))   {
    return 'U';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, RAYA, PAUSA))    {
    return 'V';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, RAYA, PAUSA, PAUSA))  {
    return 'W';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, PUNT, RAYA, PAUSA))   {
    return 'X';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, RAYA, RAYA, PAUSA))  {
    return 'Y';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, PUNT, PUNT, PAUSA))   {
    return 'Z';
  }
  if (comprovaSenyalEntrada(PUNT, RAYA, RAYA, RAYA, RAYA))  {
    return '1';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, RAYA, RAYA, RAYA))   {
    return '2';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, RAYA, RAYA))    {
    return '3';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, PUNT, RAYA))     {
    return '4';
  }
  if (comprovaSenyalEntrada(PUNT, PUNT, PUNT, PUNT, PUNT))      {
    return '5';
  }
  if (comprovaSenyalEntrada(RAYA, PUNT, PUNT, PUNT, PUNT))     {
    return '6';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, PUNT, PUNT, PUNT))    {
    return '7';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, RAYA, PUNT, PUNT))   {
    return '8';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, RAYA, RAYA, PUNT))  {
    return '9';
  }
  if (comprovaSenyalEntrada(RAYA, RAYA, RAYA, RAYA, RAYA)) {
    return '0';
  }
  return '?';
}

// Metode per encendre el LED amb una determinada duracio
void encendreLlum(long duracio) {
  digitalWrite(LED, HIGH);
  delay(duracio);
  digitalWrite(LED, LOW);
}

// Procediment per escullir si volem mostrar RAYA o PUNT al LED.
boolean senyalLlum(byte tipus) {
  switch (tipus) {
    case PUNT:
      encendreLlum(DURACIO_PUNT);
      return true;
    case RAYA:
      encendreLlum(DURACIO_RAYA);
      return true;
    default:
      return false;
  }
}

// Encen el LED en funcio de les senyals convertides a morse.
void convertidorSenyalALletra(byte s0, byte s1, byte s2, byte s3, byte s4) {
  if (senyalLlum(s0)) {
    delay(SALT);
    if (senyalLlum(s1)) {
      delay(SALT);
      if (senyalLlum(s2)) {
        delay(SALT);
        if (senyalLlum(s3)) {
          delay(SALT);
          senyalLlum(s4);
        }
      }
    }
  }
  delay(SALT_LLETRA);
}

// Metode per mostrar les lletres via LED
void mostrarLletra(byte lletra) {
  if (97 <= lletra && lletra <= 122) { // a-z
    lletra -= 32;
  }
  switch (lletra) {
    case 'A': convertidorSenyalALletra(PUNT, RAYA, PAUSA, PAUSA, PAUSA); break;
    case 'B': convertidorSenyalALletra(RAYA, PUNT, PUNT, PUNT, PAUSA); break;
    case 'C': convertidorSenyalALletra(RAYA, PUNT, RAYA, PUNT, PAUSA); break;
    case 'D': convertidorSenyalALletra(RAYA, PUNT, PUNT, PAUSA, PAUSA); break;
    case 'E': convertidorSenyalALletra(PUNT, PAUSA, PAUSA, PAUSA, PAUSA); break;
    case 'F': convertidorSenyalALletra(PUNT, PUNT, RAYA, PUNT, PAUSA); break;
    case 'G': convertidorSenyalALletra(RAYA, RAYA, PUNT, PAUSA, PAUSA); break;
    case 'H': convertidorSenyalALletra(PUNT, PUNT, PUNT, PUNT, PAUSA); break;
    case 'I': convertidorSenyalALletra(PUNT, PUNT, PAUSA, PAUSA, PAUSA); break;
    case 'J': convertidorSenyalALletra(PUNT, RAYA, RAYA, RAYA, PAUSA); break;
    case 'K': convertidorSenyalALletra(RAYA, PUNT, RAYA, PAUSA, PAUSA); break;
    case 'L': convertidorSenyalALletra(PUNT, RAYA, PUNT, PUNT, PAUSA); break;
    case 'M': convertidorSenyalALletra(RAYA, RAYA, PAUSA, PAUSA, PAUSA); break;
    case 'N': convertidorSenyalALletra(RAYA, PUNT, PAUSA, PAUSA, PAUSA); break;
    case 'O': convertidorSenyalALletra(RAYA, RAYA, RAYA, PAUSA, PAUSA); break;
    case 'P': convertidorSenyalALletra(PUNT, RAYA, RAYA, PUNT, PAUSA); break;
    case 'Q': convertidorSenyalALletra(RAYA, RAYA, PUNT, RAYA, PAUSA); break;
    case 'R': convertidorSenyalALletra(PUNT, RAYA, PUNT, PAUSA, PAUSA); break;
    case 'S': convertidorSenyalALletra(PUNT, PUNT, PUNT, PAUSA, PAUSA); break;
    case 'T': convertidorSenyalALletra(RAYA, PAUSA, PAUSA, PAUSA, PAUSA); break;
    case 'U': convertidorSenyalALletra(PUNT, PUNT, RAYA, PAUSA, PAUSA); break;
    case 'V': convertidorSenyalALletra(PUNT, PUNT, PUNT, RAYA, PAUSA); break;
    case 'W': convertidorSenyalALletra(PUNT, RAYA, RAYA, PAUSA, PAUSA); break;
    case 'X': convertidorSenyalALletra(RAYA, PUNT, PUNT, RAYA, PAUSA); break;
    case 'Y': convertidorSenyalALletra(RAYA, PUNT, RAYA, RAYA, PAUSA); break;
    case 'Z': convertidorSenyalALletra(RAYA, RAYA, PUNT, PUNT, PAUSA); break;
    case '1': convertidorSenyalALletra(PUNT, RAYA, RAYA, RAYA, RAYA); break;
    case '2': convertidorSenyalALletra(PUNT, PUNT, RAYA, RAYA, RAYA); break;
    case '3': convertidorSenyalALletra(PUNT, PUNT, PUNT, RAYA, RAYA); break;
    case '4': convertidorSenyalALletra(PUNT, PUNT, PUNT, PUNT, RAYA); break;
    case '5': convertidorSenyalALletra(PUNT, PUNT, PUNT, PUNT, PUNT); break;
    case '6': convertidorSenyalALletra(RAYA, PUNT, PUNT, PUNT, PUNT); break;
    case '7': convertidorSenyalALletra(RAYA, RAYA, PUNT, PUNT, PUNT); break;
    case '8': convertidorSenyalALletra(RAYA, RAYA, RAYA, PUNT, PUNT); break;
    case '9': convertidorSenyalALletra(RAYA, RAYA, RAYA, RAYA, PUNT); break;
    case '0': convertidorSenyalALletra(RAYA, RAYA, RAYA, RAYA, RAYA); break;
    case ' ': delay(SALT_PARAULA); break;
    default:
      Serial.print("No es pot convertir [");
      Serial.print((char) lletra);
      Serial.print("]");
      encendreLlum(50);
      delay(50);
      encendreLlum(50);
      delay(50);
      encendreLlum(50);
  }
}

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.home();
  pinMode(LED, OUTPUT);                  // LED
  pinMode(BOTO, INPUT);                // Polsador
  digitalWrite(LED, LOW);                // Apaga LED
  Serial.begin(9600);                    // Inicia connexió serie
  resetSenyalEntrada();
}

void loop() {
  long duracioActual  = millis(); // Obté temps actual
  long duracioTotal = duracioActual - duracioAnterior;
  if (digitalRead(BOTO) == HIGH) { // if Pulsador = ON
    if (!Polsador) { //  Si el pulsador no s'ha premut amb antelacio
      Polsador = true; // Recorda la pulsació anterior
      digitalWrite(LED, HIGH); // encen LED
      duracioAnterior = duracioActual; // obté la duració total entre pulsacions
      if (duracioTotal > SALT_LLETRA) { // si es major al salt entre lletres (600ms) es un salt entre paraules
        Serial.print(' ');
        lcd.print(' ');
      }
    }
  } else { // if Pulsador = OFF
    if (Polsador) { // acabem de premer el pulsador
      if (duracioTotal < DURACIO_PUNT) { // si es menor a la duracio del punt (200ms) es un punt
        senyalEntrada[senyalEntradaIndex] = PUNT; // PUNT
      } else { // si es major, es una raya
        senyalEntrada[senyalEntradaIndex] = RAYA; // RAYA
      }
      senyalEntradaIndex++; // index següent
      digitalWrite(LED, LOW); // apaguem LED
      Polsador = false;
      duracioAnterior = duracioActual;
    } else {
      if (senyalEntradaIndex > 0) { // si hi ha dades en el buffer de senyals
        if (duracioTotal > SALT || senyalEntradaIndex >= 4) { // si tenim una lletra
          Serial.print(senyalEntradaALletra()); // envia lletra via serial
          lcd.print(senyalEntradaALletra());
          resetSenyalEntrada();
        }
      }
    }
  }
  if (Serial.available() > 0) {
    mostrarLletra(Serial.read()); // envia el següent byte via LED
  }
}
