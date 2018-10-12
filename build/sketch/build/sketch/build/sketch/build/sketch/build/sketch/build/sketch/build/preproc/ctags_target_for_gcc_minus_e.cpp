# 1 "/Users/brett/Documents/Projects/chinook/StateMachineWorkingCpp.ino"
# 1 "/Users/brett/Documents/Projects/chinook/StateMachineWorkingCpp.ino"
extern "C++"{
# 3 "/Users/brett/Documents/Projects/chinook/StateMachineWorkingCpp.ino" 2
}
# 5 "/Users/brett/Documents/Projects/chinook/StateMachineWorkingCpp.ino" 2
# 6 "/Users/brett/Documents/Projects/chinook/StateMachineWorkingCpp.ino" 2

state_t CurrentState;
instance_data_t CurrentData;
volatile uint8_t TimerTicks = 0;
volatile bool IsStateReady = 1;

int main(void) {
  uint8_t timerTicks;
  bool isStateReady;

  // Configure pin modes.
  Serial.begin(115200);

  __asm__ __volatile__ ("cli" ::: "memory");
  // Set timer interrupt for sampling rate.
  (*(volatile uint8_t *)(0xB0)) = 0;
  (*(volatile uint8_t *)(0xB1)) = 0;
  (*(volatile uint8_t *)(0xB2)) = 0;
  (*(volatile uint8_t *)(0xB3)) = 60; // for a 256 Hz timer.
  (*(volatile uint8_t *)(0xB0)) |= (1 << 1);
  (*(volatile uint8_t *)(0xB1)) |= ((1 << 0) | (1 << 1) | (1 << 2)); // 1/1024 pre-scaler.
  (*(volatile uint8_t *)(0x70)) |= (1 << 1);
  __asm__ __volatile__ ("sei" ::: "memory");
  // Set external interrupt to count fuel pump pulses.

  CurrentState = STATE_INITIAL;

  while (1) {
    __asm__ __volatile__ ("cli" ::: "memory");
    timerTicks = TimerTicks;
    isStateReady = IsStateReady;
    __asm__ __volatile__ ("sei" ::: "memory");
    if ((timerTicks==0) && isStateReady) {
      IsStateReady = false;
      CurrentState = run_state(CurrentState, &CurrentData);
    }
  }

  return 0;
}

// Interrupt service routines.

extern "C" void __vector_7 /* Timer/Counter2 Compare Match A */ (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_7 /* Timer/Counter2 Compare Match A */ (void)
{
  TimerTicks++;
  IsStateReady = true;
}

extern "C" void __vector_1 /* External Interrupt Request 0 */ (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_1 /* External Interrupt Request 0 */ (void) {
  CurrentData.heater->ISR_fuelPumpPulse();
  CurrentData.lastPulses[CurrentData.iState % 5]++;
}
