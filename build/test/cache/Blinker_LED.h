









typedef volatile uint8_t * Port_t;



typedef struct {

  Port_t port;

  uint8_t pin;

} Blinker_LED_t;



void Blinker_LED_Toggle(Blinker_LED_t * led);
