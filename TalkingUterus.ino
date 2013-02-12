#define null 0 //for some reason, null was not defined originally and would throw an error without this statement.

/*Talking Uterus Arduino Control Program
Written by Chris Hilgenberg for the Ruth Lilly Health Education Center
Current Version 0.4*/

/*Version Notes:

v0.1: -Program Officially titled 'Talking Uterus Project' (previously a serial test program using case structures)
- Added Serial.write to playback version number
- Fixed possible issue with only checking the serial line only once a cycle. If it hangs (delays too long), it will be removed and tested with the old version.
- Full pin number initialization added
- Dummy pin numbers added until current/voltage is taken into account.

v0.2: -Break lines added in each case structure if-statement check to speed up process of each case so it doesn't spend time checking each conditional if the result hasn't changed.
-First draft of full steps used.

v0.3: A second version of the original program has modified: 
- Some redundancy with checking for same step within step has been removed.
- Serial line with steps is in the process of being modified.
- The line that turns off the light at the end of a step has been added as well to the beginning of the next step to make sure nothing is left on accidently between steps due to transmission/logic issues.

v0.4: 
- Delay is split up in half due to execution speed of the Loop() function after successful test of hardware boards.
-This version has been simplified a bit with the off execution of a light happening at the very beginning of the next cycle.
*/



void setup()
{
  /*Initialize SerialPort*/
  Serial.begin(9600);
  
  /*Initialize I/O*/
  
  int OutputPinUpper;
  int OutputPinLower;
  
  for(OutputPinLower = 2; OutputPinLower <14; OutputPinLower++) //Digitial I/O Pins 2-13 (PVM) used
  {
    pinMode(OutputPinLower, OUTPUT);
    Serial.println(OutputPinLower);
  }
  for(OutputPinUpper = 22; OutputPinUpper <54; OutputPinUpper++) //Digital I/O Pins 22-53 used. 42 (Lower = 11, Upper 31) total pins declared.
  {
    pinMode(OutputPinUpper, OUTPUT);
    Serial.println(OutputPinUpper); //Checking to see if pins are initialized. Also, for some reason str + variable + str concactination doesn't work here as Arduino throws an error.
  }
  Serial.println("Initialization Completed"); 
  Serial.println("Talking Uterus Control Program");
  Serial.println("Version 0.4 11-28-12");
}


void loop()
{
  int steps;
  if(steps == null) // checks for null, possibly garbage
  {
    steps = 0; 
  }
  while (Serial.available()==0) {
    delay(10); // wait until there's something interesting to do
  }
  
  if (Serial.available() > 0)
  {
    int inRecieved = Serial.read(); //Read value off of serial buffer.
    steps = inRecieved - '0';  // convert ASCII character to integer.
    Serial.print("Serial got: ");
    Serial.print(steps, DEC);
    Serial.println("");
  }
  
  switch (steps) 
  {
    case 0:
    {
        Serial.println("Executing Start Step");
        //Waits in step for main sequence to start
        Serial.println("Waiting for First Command or Additional Commands");
        break; 
    } 
      //Used No Pins
      
    case 1: 
      {
        Serial.println("Executing Step 1");
        //First Light Turns on Around 20s in main sequence
        digitalWrite(2, HIGH); //These pins will change depending on final configuration of pins for sourcing current
       break;
      }
      
      //Used 1 Pin
      
    case 2:
      {
        Serial.println("Executing Step 2");
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        break; 
      }
      //Used 1 Pin
      
    case 3:
    {
        int FirstFlash;
        Serial.println("Executing Step 3 - First Flashing Step");
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        for(FirstFlash = 0; FirstFlash <11; FirstFlash++) //Creation of the non-documented flashing sequence. It appearts to flash back and forth for 5 seconds and it appears the flashes might be a half-second delay between them
        {
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          delay(250);           //Pin numbers bound to change as any flashing might need to be put on separate powered pins.
          digitalWrite(6, HIGH);
          digitalWrite(5, LOW); 
          delay(250);
        }
        digitalWrite(5, LOW); //Reset those pins so they stay off after the toggle.
        digitalWrite(6, LOW);
        digitalWrite(4, LOW);
        break;
    }
        //Used 4 Pins
    case 4:
    { 
        Serial.println("Executing Step 4");
        digitalWrite(7, HIGH);
        break;
    }  
         //Used 1 Pin
         
    case 5:
    {
        Serial.println("Executing Step 5");
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        break;
    }   
          //Used 1 Pin
          
     case 6:
     {
          Serial.println("Executing Step 6");
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          break;
     }    
          //Used 1 Pin
          
     case 7:
     {
         Serial.println("Executing Step 7");
         digitalWrite(9, LOW);
         digitalWrite(10, HIGH);
         break;
     }   
         //User 1 pin
    case 8:
    {
        Serial.println("Executing Step 8");
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        break;
    }
         //Used 1 Pin
         
    case 9:
    {
        Serial.println("Executing Step 9");
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        break;
    }

        //Used 1 Pin
         
     case 10: //This is the first major loop.
      {
          digitalWrite(12, LOW);
          int SecondFlash;
          int LightCount; 
          Serial.println("Executing Step 10 - Second Flash Sequence in Stepper Fashion"); 
          for(SecondFlash = 0; SecondFlash < 5; SecondFlash++) //First for statement is for Count number in original XML code for 4 repeats
          {
            LightCount = 22; //Resets count for each main loop
            while (LightCount < 30) //I believe at least 8 lights are tied to this sequence. I will have the steps run again before teardown/installation to confirm this.
            {
              digitalWrite(LightCount,HIGH);
              delay(350); //Seconds delay based on XML code of .7 seconds.
              digitalWrite(LightCount,LOW);
              delay(350);
              LightCount++;
            }
          }
          Serial.println("Finished Step 10 - Second Flash Sequence in Stepper Fashion"); 
          break;
      }
         //Used 9 Pins
         
      case 11:
      {
          Serial.println("Executing Step 11");
          digitalWrite(30, HIGH);
         break;
      }  
         //Used 1 Pin
         
     /*Up until now, the timing for the triggering of the next step would be determined by the Mac sending commands to the Arduino. To save
     time and room in this case structure, the next few cases have recreated the last two 'toggles' which only turn off and on lights with a .54 second delay
     in between them. */
      case 12:
       { 
          int CountStep;
          int LightCount1 = 31;
          Serial.println("Executing Step 12");
          for(CountStep = 0; CountStep <10; CountStep++)
          {
            digitalWrite(LightCount1, HIGH);
            delay(270);
            digitalWrite(LightCount1, LOW);
            delay(270);
            LightCount1++;
          }
         break;
       } 
         //Used 9 Pins
     case 13:
       {
          int CountStep;
          int LightCount2 = 40;
          Serial.println("Executing Step 13");
          for(CountStep = 0; CountStep < 6; CountStep++) //The Last Delay call with 5 lights switched on at 0.54s intervals
          {
            digitalWrite(LightCount2 , HIGH);
            delay(270);
            digitalWrite(LightCount2, LOW);
            delay(270);
            LightCount2++;
          }
          break;
        }
         
      case 14:
         { /*This step is a 'dummy' end step for the final part of the program. The very beginning and end turn on the big fluorescent bulbs to light up the whole display, but they are currently outside of the limitiations of the Arduino and running hardware to power alone.
         This is a spot where commuincation is needed with the left over circuit for turning on the bulbs.*/
         steps = 0;
         Serial.println("Executing Step 14");
         break;
         }
    default:
      break;
  }
}
