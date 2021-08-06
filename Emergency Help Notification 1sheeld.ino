#define CUSTOM_SETTINGS
#define INCLUDE_NOTIFICATION_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* A name for the button on pin 12. */
int buttonPin = 12;
/* A name for the LED on pin 13. */
int ledPin = 13;

void setup()
{
  /* Start communication. */
  OneSheeld.begin();
  /* Set the button pin as input. */
  pinMode(buttonPin,INPUT);
  /* Set the LED pin as output. */
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  /* Always check the button state. */
  if(digitalRead(buttonPin) == HIGH)
  {
    /* Turn on the LED. */
    digitalWrite(ledPin,HIGH);
    /* Send a notification to your phone. */
    Notification.notifyPhone("I need emergency help");
    /* Wait for 300 ms.   */
 OneSheeld.delay(300);  
  }
  else
  {
    /* Turn off the LED. */
    digitalWrite(ledPin,LOW);
  }
}
