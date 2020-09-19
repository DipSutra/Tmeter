#include<reg51.h>//REG51.H Header file for generic 80C51 and 80C31 microcontroller
#include<stdio.h>
#define LCDPort P1 // LDCPort (PIN 7 to PIN 14) of LCD is Connected to P1(PIN 1 to PIN 8) of 8051
sbit RS=P0^0; // RS pin of LCD (PIN 4) is Connected to P0.0 (PIN 39) of 8051
sbit RW=P0^1; // RW pin of LCD (PIN 5) is Connected to P0.1 (PIN 38) of 8051
sbit EN=P0^2; // EN pin of LCD (PIN 6) is Connected to P0.2 (PIN 37) of 8051
sbit SENSOR=P3^2;
sbit LED=P2^0;
void delay(int t) // This function will generate t ms delay
{
int i;
while(t>0) // Loop until t become ZERO
{
i=1275; // Set the Starting value of i with 1275
while(i>0) i--; // Decrease the Value of i by -1 , until i become ZERO
t--; // Decrease the value of t by -1
26
}
}
void LCDCommand(char c) // This function will execute a Command
{
RS=0; // RS=0 means, we are sending Command to LCD
RW=0; // RW=0 means, we are using the LCD in Write Mode
LCDPort=c; // Copy the Value of c (Command) into LCDPort (P1 in Our Case)
EN=1; // SET EN pin HIGH ----------------+
delay(2); // Wait for 2 ms +-- Generat a High To Low Pulse
EN=0; // Reset the EN pin Back to LOW ----+
}
void LCDData(char c) // This function will send a Data to LCD
{
RS=1; // RS=1 means, we are sending Data to LCD
RW=0; // RW=0 means, we are using the LCD in Write Mode
LCDPort=c; // Copy the Value of c (Data) into LCDPort (P1 in Our Case)
EN=1; // SET EN pin HIGH ----------------+
delay(2); // Wait for 2 ms +-- Generat a High To Low Pulse
EN=0; // Reset the EN pin Back to LOW ----+
}
void LCDInit() // This function will Initilized the LCD
{
LCDCommand(0x38); // 0x38 - 8 Bit Mode
LCDCommand(0x06); // 0x06 - Display from Left to Right
LCDCommand(0x0c); // 0x0c- Display On, Cursor Hide
LCDCommand(0x01); // 0x01 - Clear LCD
}
/* String: An array of character terminated by NULL ('\o') is Called String
array index start from 0 (ZERO)
+---+---+---+--+
String | A | E | C |\o|
+---+---+---+--+
^
0
*/
void LCDPuts(char *s) // This function will Display a String on LCD
{
int i; // Declare local variable i to use as index of the Character of a String
for(i=0;s[i]!='\0';i++) // Scan each and every Character of the String One by on
{
LCDData(s[i]); // And display the Character on LCD with LCDDatra() function
}
}

void main() // The main() function start here
{
char buffer[10]; // Declare an array of Character
unsigned long int TimerCounter=0;
int Counter=0;
int RPM=0;
LCDInit(); // Initilizing the LCD
LCDPuts("Contact Less");
LCDCommand(0xc0); // Set Cursor at the starting of Second Line
LCDPuts("Techometer");
delay(100); // Wait for 100 ms
LCDCommand(0x01); // Clear LCD
LCDPuts("AEC/EE/2018");
delay(100); // Wait for 100 ms
LCDCommand(0xc0);
LCDPuts("Kunal Nath ");
delay(100);
LCDCommand(0xc0);
LCDPuts("Dipankar ");
delay(100);
LCDCommand(0xc0);
LCDPuts("Rajdeep Das ");
delay(100);
LCDCommand(0xc0);
LCDPuts("Chirantan ");
delay(100);
LCDCommand(0x01); // Clear LCD
LCDPuts("RPM:");
while(1)
{
TimerCounter++;
if(SENSOR==0)
{
Counter++;
while(SENSOR==0);
}
if(TimerCounter> 65500)
{
TimerCounter=0 ;

RPM=Counter * 6; // As we have count for 15 sec, we have to Multiply by 4 to get RPM
Counter=0; // Reset the Counter to 0
if(RPM>0)
{
sprintf(buffer,"%4d",RPM); // Convert The Numeric Data into String
LCDCommand(0x85); // Move the Cursor to 5th Position of First Line
LCDPuts(buffer); // Display The RPM on LCD
}
}
}
}
