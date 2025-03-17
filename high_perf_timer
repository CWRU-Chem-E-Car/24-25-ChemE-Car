void setup()
{
  pinMode(2, OUTPUT);
  TCCR1A = 0;
  TCCR1B = 0;          // input capture noise canceller disabled, capture on falling edge (may adjust this later), stop timer
  TIMSK1 = 0;          // timer 1 interrupts disabled
  ACSR = 0;             // input capture NOT from analog comparator
  Serial.begin(115200);
}

void loop()
{
  static int numDisplayed = 20;
  static bool posEdge = true;
  
  TCCR1B = (posEdge) ? (1 << ICES1) : 0;        // set up timer 1 to capture on whichever edge we want and stop timer
  TCNT1H = 0;
  TCNT1L = 0;          // clear timer 1
  unsigned long start = micros();  // get the time
  
  cli();
  TIFR1 = 1 << ICF1;            // clear input capture bit
  TCCR1B |= (1 << CS10);     // start timer, prescaler = 1
  PORTD |= (1 << 2);          // set output high
  sei();

  unsigned int capture = 0;
  do
  {
    if ((TIFR1 & (1 << ICF1)) != 0)
    {
      byte temp = ICR1L;
      capture = (ICR1H << 8) | temp;
    }
  } while (capture == 0 && micros() - start < 100);     // time out after 100us
  
  PORTD &= ~(1 << 2);     // set output low
  if (capture != 0)
  {
    if (numDisplayed == 20)
    {
      Serial.println();
      numDisplayed = 0;
    }
    else
    {
      Serial.write(' ');
    }
    Serial.print(capture);
    ++numDisplayed;
    delay(100);
  }
  else
  {
    delayMicroseconds(500);
  }
}
