
byte TP = 0b10101010; //jeder 2. Port bekommt das umgekehrte Signal

void setup()
{
 DDRC = 0b11111111; //Alle Analogports als Ausgang definieren
 
  // Timer 1 initialisieren
  noInterrupts();           // Interrupts deaktivieren
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 200;              // Compare Match Register setzen (16MHz / 200 = 80kHz Rechteck -> 40kHz Vollwelle )
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10);    // Prescaler auf 1 ==> kein prescalling
  TIMSK1 |= (1 << OCIE1A);  // Compare Timer Interrupt einschalten
  interrupts();             // Interrupts aktivieren
}

ISR(TIMER1_COMPA_vect)          
{
  PORTC = TP; // Den Wert TP an die Ausgange senden
  TP = ~TP;   // TP invertieren für den nächsten durchlauf
}

void loop(){
  // hier bleibt  nichts zu tun übrig:-(
}

