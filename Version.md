This is a separate file for version history of the Talking Uterus Project. 

v0.1: 
-Program Officially titled 'Talking Uterus Project' (previously a serial test program using case structures)
- Added Serial.write to playback version number
- Fixed possible issue with only checking the serial line only once a cycle. If it hangs (delays too long), it will be removed and tested with the old version.
- Full pin number initialization added
- Dummy pin numbers added until current/voltage is taken into account.

v0.2: 
-Break lines added in each case structure if-statement check to speed up process of each case so it doesn't spend time checking each conditional if the result hasn't changed.
-First draft of full steps used.

v0.3: A second version of the original program has modified:
- Some redundancy with checking for same step within step has been removed.
- Serial line with steps is in the process of being modified.
- The line that turns off the light at the end of a step has been added as well to the beginning of the next step to make sure nothing is left on accidently between steps due to transmission/logic issues.

v0.4:
- Delay is split up in half due to execution speed of the Loop() function after successful test of hardware boards.
-This version has been simplified a bit with the off execution of a light happening at the very beginning of the next cycle.
