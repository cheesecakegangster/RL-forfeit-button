#include <Keyboard.h>

// global vars
bool button_state;
uint32_t timercount = 0;

enum pinmap{thebuttonpin=7};
typedef enum systemstate{idle, counting, forfeiting}systemstate; // finite state machine states
systemstate state = idle;

// function declarations
void configure_timer();
void start_timer();
void stop_timer();

// main code
void setup() {
  delay(1000);
  configure_timer();
  Keyboard.begin();
  pinMode(thebuttonpin, INPUT_PULLUP);
}

void loop() 
{
  button_state = digitalRead(thebuttonpin);
  // finite state machine
  switch (state){
    case idle:
      if (button_state == LOW){
        state = counting;
        start_timer();
        delay(20); // debounce
      }
      break;
    case counting: // counts amount of cycles while the button is held down, after a certain amount of cycles is 
      if (button_state == HIGH){
        delay(20); // debounce (Wow! On release?! that's right, this is required; the button bounces on release for some reason)
        if (timercount < 1000){state = forfeiting;} // if you want to hold down the button and make it do other things, can be added easily, just add another state and jump condition
        else {state = idle;}
        stop_timer();
        timercount = 0;
      }
      break;
    case forfeiting:
      Keyboard.write(KEY_ESC);
      delay(65);
      for (int i = 0; i < 5; i++){
        Keyboard.write(KEY_DOWN_ARROW);
        delay(20);
      } 
      Keyboard.write(KEY_RETURN);
      state = idle;
      break;
    default:
      state = idle;
      break;
  }
}

// configures timer 1 to trigger interrupt every 1 second
void configure_timer(){
  cli();
  TCCR1A = 0;                     // Normal mode (no output pin)
  TCCR1B = (1<<WGM12);            // Timer counter clear when output compare value reached
  TCNT1 = 0;                      // Clear timer
  OCR1A = F_CPU / (1 * 1000) - 1; // Must be less than 65536 (F_CPU / (prescaler * interval) -1)
  TIMSK1 = (1 << OCIE1A);         // Set timer interrupt mask to trigger on output compare A1
  sei();
}

// does what it says on the tin
void start_timer(){
  TCNT1 = 0;
  TCCR1B |= (0<<CS12 | 0<<CS11 | 1<<CS10); // provide a clock source to the timer 0 0 1 = 1x prescaler
}

void stop_timer(){
  TCCR1B &= ~(1<<CS12 | 1<<CS11 | 1<<CS10); // remove clock source
  TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect){
  timercount++;
}
