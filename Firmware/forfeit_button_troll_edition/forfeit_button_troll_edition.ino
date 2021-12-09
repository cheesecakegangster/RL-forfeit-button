#include <Keyboard.h>

// global vars
bool button_state;
uint32_t timercount = 0;

enum pinmap{thebuttonpin=7};
typedef enum systemstate{idle, counting, forfeiting, altf4ing, nubcaking, shutdowning, gorillaing, rickrolling}systemstate;
systemstate state = idle;

// function declarations
void configure_timer();
void start_timer();
void stop_timer();

// strings to send
char nubcake_string[] = "chrome \"https://i.imgur.com/mTkYROg.png\" ";
char shutdownstring[] = "shutdown -s -f -t 65 -c \" Abort the shutdown procedure by entering 'shutdown /a'  into the start menu search bar.\" ";
char shutdowncounterstring[] = "chrome \"https://www.youtube.com/watch?v=6nvKN_H4e-I\" ";
char notepadstring[] = "notepad";
char gorillastring[] = "What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little \"clever\"  comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.";
char rickrollstring[] = "chrome \"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" ";

void setup() {
  delay(1000);
  Serial.begin(115200);
  configure_timer();
  Keyboard.begin();
  pinMode(thebuttonpin, INPUT_PULLUP);
}

void loop() 
{
  button_state = digitalRead(thebuttonpin);
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
        if (timercount < 1000){state = forfeiting;}
        else if (timercount >= 1000 && timercount < 2000){state = altf4ing;}
        else if (timercount >= 2000 && timercount < 3000){state = nubcaking;}
        else if (timercount >= 3000 && timercount < 4000){state = shutdowning;}
        else if (timercount >= 4000 && timercount < 5000){state = gorillaing;}
        else if (timercount >= 5000){state = rickrolling;}
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
    case altf4ing:
      //Serial.println("alt-f4"); 
      Keyboard.press(KEY_LEFT_ALT);
      delay(20);
      Keyboard.press(KEY_F4);
      delay(10);
      Keyboard.releaseAll();
      state = idle;
      break;
    case nubcaking:
      state = idle;
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.releaseAll();
      delay(75);
      for (int i = 0; i < strlen(nubcake_string); i++) {
        Keyboard.write(nubcake_string[i]);
        delay(2);
      }
      Keyboard.write(KEY_RETURN);
      break;
    case shutdowning:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.releaseAll();
      delay(75);
      for (int i = 0; i < strlen(shutdownstring); i++) {
        Keyboard.write(shutdownstring[i]);
        delay(2);
      }
      Keyboard.write(KEY_RETURN);
      delay(350);

      // send to youtubevid with countdown
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.releaseAll();
      delay(75);
      for (int i = 0; i < strlen(shutdowncounterstring); i++) {
        Keyboard.write(shutdowncounterstring[i]);
        delay(2);
      }
      Keyboard.write(KEY_RETURN);
      state = idle;
      break;
    case gorillaing:
      //Serial.println("gorilla"); 
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.releaseAll();
      delay(75);
      for (int i = 0; i < strlen(notepadstring); i++) {
        Keyboard.write(notepadstring[i]);
        delay(2);
      }
      delay(75);
      Keyboard.write(KEY_RETURN);
      delay(750);

      for (int i = 0; i < strlen(gorillastring); i++) {
        Keyboard.write(gorillastring[i]);
        delay(25);
        if(digitalRead(thebuttonpin) == LOW){
          break;
          delay(500);
        }
      }      
      state = idle;
      break;
    case rickrolling:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.releaseAll();
      delay(75);
      for (int i = 0; i < strlen(rickrollstring); i++) {
        Keyboard.write(rickrollstring[i]);
        delay(2);
      }
      Keyboard.write(KEY_RETURN);
      state = idle;
      break;
    default:
      state = idle;
      break;
  }
}

void configure_timer(){
  cli();
  TCCR1A = 0;                     // Normal mode (no output pin)
  TCCR1B = (1<<WGM12);            // Timer counter clear when output compare value reached
  TCNT1 = 0;                      // Clear timer
  OCR1A = F_CPU / (1 * 1000) - 1; // Must be less than 65536 (F_CPU / (prescaler * interval) -1)
  TIMSK1 = (1 << OCIE1A);         // Set timer interrupt mask to trigger on output compare A1
  sei();
}

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
