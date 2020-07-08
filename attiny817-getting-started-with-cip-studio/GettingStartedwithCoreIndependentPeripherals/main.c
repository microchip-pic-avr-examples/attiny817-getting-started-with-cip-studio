/*
    Application initiates a single ADC conversion when Button0
    (SW0 on tiny817 Xplained Pro) is pressed.
    To avoid starting more than one conversion due to "bounce" on the
    button signal, the signal is "debounced" using the CCL filter combined
    with PIT output from the RTC as the filter clock.
    The signals from the button and the PIT are routed to LUT1 in the CCL
    via the	Event System, and the output from LUT1 is routed to the ADC
    via the Event System as well.

    The 8 least significant bits of the ADC result register are then stored
    and transmitted via the USART. The transmitted data can be inspected in a
    serial terminal like the one included in the Data Visualizer in
    Atmel Studio.

    The ADC result register will contain the raw value from the temperature
    sensor on the device.

    To initiate ADC conversions directly from the button signal without
    CCL debouncing, comment in #define NO_DEBOUNCE below.
    Bounce on the button signal will in most then initiate more than one
    ADC conversion on each button press.
*/

#include <atmel_start.h>

//#define NO_DEBOUNCE

volatile uint8_t ADC_result = 0;
volatile uint8_t send_flag  = 0;

/* ADC result ready interrupt routine */
ISR(ADC0_RESRDY_vect)
{
	/* Store the ADC result and notify the main loop to send the result */
	ADC_result = ADC0.RESL;
	send_flag  = 1;

	/* The interrupt flag has to be cleared manually */
	ADC0.INTFLAGS = ADC_RESRDY_bm;
}

/* Initialize application settings */
void init_application()
{
	/* Enable the ADC result ready interrupt */
	ADC0.INTCTRL |= ADC_RESRDY_bm;
	/* Enable the ADC */
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Initialize application settings */
	init_application();

#ifdef NO_DEBOUNCE
	/* Disable the CCL to deactivate debouncing.
	Use Button0 directly to initiate an ADC sample instead. */
	CCL.CTRLA = (CCL.CTRLA & ~CCL_ENABLE_bm);
#endif

	while (1) {

		/* ADC result has been stored and is ready to be sent */
		if (send_flag) {
			USART0.TXDATAL = ADC_result;
			send_flag      = 0;
		}

#ifdef NO_DEBOUNCE
		/* Use Button0 output directly */
		if (Button0_get_level() == false) {
			ADC0.COMMAND = ADC_STCONV_bm; // Start ADC conversion
			while (Button0_get_level() == false) {
			} // Wait for button release
		}
#endif
	}
}
