/*
The ICACHE_RAM_ATTR and ICACHE_FLASH_ATTR are linker attributes. Once you compile your sketch, you can say if the function 
should be stored in the RAM or FLASH (normally you do not set anything: no cache). 
 - ESP8266 is multitasking and 
 - the ESP32 has 2 cores. 
So you can execute your code as multithreading - since it use the RTOS. 
And now the problem: The entire flash is used for the program and storage. Reading and writing to the flash can be done only 
over 1 thread. If you try to access the flash simultaneously over 2 different threads, your ESP will probably crash.
This is because you can put your function in the RAM instead of the flash. So even if you are writing something in the EEPROM 
or flash, this function can be called without accessing the flash.
With ICACHE_RAM_ATTR you put the function on the RAM.
With ICACHE_FLASH_ATTR you put the function on the FLASH (to save RAM).
Interrupt functions should use the ICACHE_RAM_ATTR. Function that are called often, should not use any cache attribute.
Important: NEVER access your flash inside an interrupt! The interrupt can occur during a flash access, so if you try to access
the flash at the same time, you will get a crash (and sometimes this happens after 1-2 hours after you use your device).
Since you have only 32kb of IRAM (Instruction RAM), you should try to put only interrupt functions in the RAM, not all your 
functions, even if it is possible to do so.
Second question: NO, absolutely no! inline is another compiler flag, so that the compiler will try to put your entire function
inside the caller function => convert a function call to c++ code inside your main. This doesn't mean that the compiler will do 
it, just try it. You can't ask to put the function inside the RAM, if the function does not exist anymore once you compile your 
sketch.
*/

void ICACHE_RAM_ATTR handleInterrupt();
const int interruptPin = D1;            //GPIO 0 (Flash Button) 
const int LED=2;                        //On board blue LED 


void handleInterrupt() { 
    Serial.println("Interrupt Detected"); 
}


void setup() { 
  Serial.begin(115200); 
  pinMode(LED,OUTPUT); 
  pinMode(interruptPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, HIGH); 
} 

void loop() 
{ 
    digitalWrite(LED,HIGH); //LED off 
    delay(1000); 
    digitalWrite(LED,LOW); //LED on 
    delay(1000); 
} 

