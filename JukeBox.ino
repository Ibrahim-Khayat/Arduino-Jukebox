
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
// Pins
const int l_pin = 8;
const int r_pin = 9;
const int buzzerPin = 10;

// Number of columns on LCD


// LCD object

int song=0;

// Define a custom LCD character (5x7) that looks
// like a person.
byte person[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B01010,
  B01010,
};


// Button states
int l_prev = HIGH;
int r_prev = HIGH;


void setup()
{
    Serial.begin(9600);
  
  // Set pullups on buttons
  pinMode(l_pin, INPUT_PULLUP);
  pinMode(r_pin, INPUT_PULLUP);
  
  // Initialize and clear LCD 
  lcd.init();
  lcd.backlight();
  lcd.print("Jukebox");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.print("Jukebox");
  delay(500);
  lcd.clear();
  delay(1000);
  lcd.print("Select a track");
  lcd.setCursor(0,1);
  lcd.print("Press the Right btn");
  // Register custom character
  lcd.createChar(0, person);
}

void loop()
{
  
  // Look for left button press and move character to the left
  int l_state = digitalRead(l_pin);
  if ( (l_prev == HIGH) && (l_state == LOW) ) {
    if (song == 2){
        Serial.println("play 2");
      int songLength = 16;
    char notes[] = "acdddefffgedccd "; // a space represents a rest
    int beats[] = {1,1,2,2,1,1,2,2,1,1,2,2,1,1,1,2};
    int tempo = 150;
    int i, duration;

  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }
    }else if (song == 1){
     Serial.println("play 1");
      const int songLength = 24;
  char notes[] = "xzxxzxzxnxzvvmvvmvmvzxmv "; // a space represents a rest
  int beats[] = {1,1,3,1,1,3,1,1,2,2,2,3,1,1,3,1,1,3,1,1,2,2,2,3};
  int tempo = 160;
       
  int i, duration;

  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

    }
    
    
  }
   
  
  
  // Look for Right button press and move character to the left
  int r_state = digitalRead(r_pin);
  if ( (r_prev == HIGH) && (r_state == LOW) ) {
     lcd.clear();
    if ( song == 2){
      lcd.print("1st Track");
      song=1;
      
    } else if (song == 1 || song == 0 ){
      lcd.print("2nd Track");
      song=2;
    }
    
    
  }
  
  // Remember previous button states
  l_prev = l_state;
  r_prev = r_state;
  
  delay(20);
}


int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 13;  // number of notes we're storing

  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C',
                  'z', 'x', 'v', 'n', 'm'};
  // z=Csharp, x=d5, v=b4, n=e5, m=a4
  int frequencies[] = {262, 294, 330, 349, 392, 220, 494, 523,
                       554, 587, 493, 659, 440};

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
