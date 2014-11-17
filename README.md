# Camera interval triggerer

Quick and dirty arduino thing to trigger my camera remote at an interval.

The Nikon D40 firmware doesn't have interval functionality, so this is a hack
to provide that functionality through a cheap remote.

## Outputs

There are 2 LEDs and an "actuator" pin.

1. LED 1 pulses at the interval currently set (init to none)
2. LED 2 shows whether the pulses are being sent to the actuator (remote)
3. Actuator is connected to the remote

## Inputs

There are 2 push buttons (which pull to GND when pushed), their function:

1. Set interval (time between last two presses = new interval, rounded to 5ms)
2. Activate remote - sends the pulses to the actual remote, rather than just the indication LED

## Current status

I just mocked this up in an evening because SoMakeIt (makerspace I'm a member of) needs a timelapse of the new space we're doing up. If I find time / motivation, I'll make this a proper little project in the future.

### Stuff I want to do

- Clean up / document arduino code
- Design for a smaller uC rather than a way overly featured one like the atmega 328p
- Design circuit + board in eagle

## License

I'll add an actual license file later, but essentially "Do whatever you want".
