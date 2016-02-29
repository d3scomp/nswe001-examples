#include "main.h"

#include <cstdio>

uint32_t mainCycles = 0;

LED::Properties greenLedProps {
	GPIOD, GPIO_Pin_12, RCC_AHB1Periph_GPIOD
};
LED::Properties redLedProps {
	GPIOD, GPIO_Pin_14, RCC_AHB1Periph_GPIOD
};
LED::Properties orangeLedProps {
	GPIOD, GPIO_Pin_13, RCC_AHB1Periph_GPIOD
};
LED::Properties blueLedProps {
	GPIOD, GPIO_Pin_15, RCC_AHB1Periph_GPIOD
};
LED greenLed(greenLedProps);
LED redLed(redLedProps);
LED blueLed(blueLedProps);
LED orangeLed(orangeLedProps);

extern void sysTickHookMain() 
{
	static int counter = 0;

	if (counter >= 25) {
		orangeLed.off();
	} else {
		orangeLed.on();
	}

	counter++;

	if (counter >= 50) {
		counter = 0;
	}
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	// Configures how priorities are interpreted
	                                                // 4 bits for pre-emption priority, 0 bits for non-preemptive subpriority

	// Set SysTick to fire every 10ms
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0));
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

	greenLed.init();
	redLed.init();
	blueLed.init();
	orangeLed.init();


	NVIC_SystemLPConfig(NVIC_LP_SLEEPONEXIT, ENABLE); // This ..
	while (1) {
		__WFI(); // ... and this has to be commented out when debugging.
	}
}


