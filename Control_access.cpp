#include "mbed.h" 
#include "Keypad.h" 
#include "SLCD.h" 
#include <cstdio> 
#include <cstring> 
#include "KVMap.h" 
#include "flash_api.h" 
#include "FlashIAP.h" 
#include "Ticker.h" 
Keypad mykey(PTD3, PTA2, PTA1, PTC8, PTA5, PTA4, PTA12); 
FlashIAP fd; 
// Blinking rate in milliseconds 
#define BLINKING_RATE 500ms //define keypad input 
    char input[9]; 
    int i = 0;   
    //define the initial password（customer’s 
    
    char password[9] = " "; 
    char key[9] = " "; //define the admin‘s password 
    char admin[9] = "77777777"; 
    //Defines how to compare the entered password with the set password 
    bool match = true; 
    char cr = mykey.ReadKey(); 
    SLCD mydisp; 

//Change password function 
void ChangePassword(char* oldPassword, char* newPassword) 
{   
    strcpy(oldPassword, newPassword); 
} 
//Get Password Function 
char GetPassword(char m[9]) 
{ 
    m[0] = 0; 
    for (int i=1; i<9; i++) m[i] = ' '; 
    
    while (m[0]<9) { 
        if (mykey.KeyReady())
        { 
            cr = mykey.ReadKey(); 
            //* indicates invalid or reentered 
            if (cr == '*') return 0; 
            //# indicates comfirmed 
            if (cr == '#') 
                { 
                    if (m[0] == 0) return 0; 
                    else return 1; 
                } //The LCD always displays the last four digits input 
                m[0]++; 
                m[m[0]] = cr; 
                if (m[0]<=4) mydisp.printf("%c%c%c%c", m[1], m[2], m[3], m[4]); 
                else mydisp.printf("%c%c%c%c", m[m[0]-3], m[m[0]-2], m[m[0]-1], m[m[0]]); 
                } 
            } return 1; 
        }
                 
//Compare Password Function 
char ComparePassword(char m[9], char n[9], bool M)
{ 
    //Compare the entered numbers with the password bit by bit 
    if (m[0] == 9) 
    {
         m[0] = 0; 
    } 
        for (int j = 1; j < 9; j++) 
        { 
            if (m[j] != n[j-1]) 
            { 
                //If inconsistent, exit the loop immediately 
                M = false; 
                break; 
            } 
        } 
    return M; 
} 

//Display Function to make LCD information flash 
char displayMessage(SLCD& lcd, const char* message) 
{ 
    cr = 0; 
    
    while(cr <= 0) 
    { 
        lcd.printf("%s", message); 
        wait_us(500000); 
        lcd.printf(" "); 
        wait_us(500000); 
        lcd.printf("%s", message); 
        wait_us(500000); 
        lcd.printf(" "); 
        if (mykey.KeyReady()) 
        { 
            cr = mykey.ReadKey(); 
            if (cr > 0) return 0; 
        } 
    } 
    return 1; 
    } 
//Function is used to save the password of the flash memory 
void saveFlash(char* password, char* admin) 
{ 
    //Boot flash 
    fd.init(); 
    //Find address of last sector of flash 
    int Lastsector = fd.get_flash_size()+fd.get_flash_start()-1024;

    //Define and read page into buffer 
    char buffer [256]; 
    fd.read(buffer, Lastsector, 256); 
    //Assign the password into buffer 
    for(int i = 0; i < 9;i++) 
    { 
        //Save both the customer and admin passwords 
        buffer[i] = password[i]; 
        buffer[i+9] = admin[i]; 
    } 
        buffer[17] = '9'; 
    //Clear the sectors of the flash drive 
    fd.erase(Lastsector, 0x400); 
    //A sector encoded into a flash memory in the first page 
    fd.program(buffer, Lastsector, 256); 
    
    return; 
} 
//Function is used to read the password of flash memory 
void loadflash(char * password1, char* admin) 
{ 
    //Boot flash 
    fd.init(); 
    //Find address of last sector of flash 
    int Lastsector = fd.get_flash_size()+fd.get_flash_start()-1024; 
    
    //Define and read page into 
    buffer char buffer[256]; 
    fd.read(buffer, Lastsector,256); 
    //Assign the buffer into password 
    if(buffer[17] != '9') return; 
    else 
    for(int i = 0; i < 9;i++) 
    { 
    //Load both the customer and admin passwords 
    password1[i] = buffer[i]; admin[i] = buffer[i+9]; 
    } 
    return; 
} 
int main() 
{ 
    // Initialise the digital pin LED1 as an output 
    DigitalOut led(LED1); 
    SLCD mydisp;

    //Main program practice intelligent door lock complete logic 
    while (true) 
    { 
        led = !led; 
        if (mykey.KeyReady()) 
        { 
            displayMessage(mydisp, "ENTR"); 
            GetPassword(input); //Get new password 
            loadflash(password,admin); 
            if (ComparePassword(input, password, match)) 
            { 
                //If the customer enters the correct password, the LCD displays PASS // mydisp.printf("PASS"); displayMessage(mydisp, "PASS"); } else if (ComparePassword(input, admin, match)) { //If the admin enters the correct password,the LCD displays ADMI 
                
                //mydisp.printf("ADMI"); 
                displayMessage(mydisp, "ADMI"); 
                //Give administrators permission to change passwords 
                //The LCD display means can change password 
                displayMessage(mydisp,"CHAN"); 
                //GetPassword(input); 
                if (password[0] == key[0]) 
                { 
                    GetPassword(input); 
                    if(ComparePassword(input, admin, match) || ComparePassword(input, password,match) || input[8] == ' ' ) 
                    { 
                    //If the password is less than nine characters or the password same with the admin's password , //or the password same with the old customer's password the LCD displays an error 
                    displayMessage(mydisp,"EROR"); 
                    } 
                    else 
                    { 
                        ChangePassword(password, input+1); 
                        //Save the new password 
                        saveFlash(password,admin); 
                        //LCD displays change succeed 
                        displayMessage(mydisp,"SUCC"); 
                        }

                        } 
                        else 
                        { 
                            displayMessage(mydisp,"1OR2"); 
                            GetPassword(input); 
                            switch (input[1]) 
                            { 
                                //Input "1" to change the customer password 
                                //LOWR indicates the lower level on the LCD 
                                case '1':displayMessage(mydisp,"LOWR"); 
                                GetPassword(input); 
                                if(ComparePassword(input, admin, match) || ComparePassword(input, password,match) || input[8] == ' ' ) 
                                { 
                                    //If the password is less than nine characters or the password same with the admin's password , 
                                    //or the password same with the old customer's password the LCD displays an error 
                                    displayMessage(mydisp,"EROR"); 
                                    } 
                                    else 
                                    { 
                                        ChangePassword(password, input+1); 
                                        //Save the new password saveFlash(password,admin); 
                                        //LCD displays change succeed displayMessage(mydisp,"SUCC"); 
                                        } 
                                        break; 
                                        //Input "2" to change the customer password //HIGH indicates the higher level on the LCD 
                                        case '2':displayMessage(mydisp,"HIGH"); 
                                        GetPassword(input); 
                                        if(ComparePassword(input, admin, match) || ComparePassword(input, password,match) || input[8] == ' ' ) 
                                        { 
                                            //If the password is less than nine characters or the password same with the admin's password , 
                                            //or the password same with the old customer's password the LCD displays an error 
                                            displayMessage(mydisp,"EROR"); 
                                            } 
                                            else 
                                            { 
                                                ChangePassword(admin, input+1); 
                                                //Save the new password 
                                                saveFlash(password,admin);
                                                //LCD displays change succeed 
                                                displayMessage(mydisp,"SUCC"); 
                                                } 
                                                break; 
                                                //If input other numbers, the LCD will display "ERRO" by default. 
                                                default: displayMessage(mydisp,"EROR"); break; 
                             } 
                            } 
            } 
        else 
            { 
                //If you enter an incorrect password, the LCD displays FAIL //mydisp.printf("FAIL"); 
                displayMessage(mydisp, "FAIL"); 
            } 
        } 
    } 
}
