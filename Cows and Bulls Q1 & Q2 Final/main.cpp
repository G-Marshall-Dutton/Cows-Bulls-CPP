//
//  main.cpp
//  Cows and Bulls Q1 & Q2 Final
//
//  Created by George Marshall-Dutton on 14/01/2017.
//  Copyright © 2017 George Marshall-Dutton. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;

//----------------------------------------FUNCTIONS-----------------------------







char myRand(int a, int b) //creates a random number between a and b (0 and 1) and changes it to type char
{
    int d;
    char c;
    d = a + rand() % (b - a + 1);
    if (d == 0)
    {
        c = '0';
    }
    else
    {
        c = '1';
    }
    return c;
}


int countOnes(string a) // counts how many 1's there are in string a
{
    int b = 0;
    
    
    
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == '1')
        {
            b++;
        }
    }
    return b;
}


int determineCows1(int userOnes, int userZeros, int compOnes, int compZeros)//Determines cows ignoring all bulls
{
    int cows;
    
    if (userOnes >= compOnes)
    {
        cows = compOnes;
    }
    else
    {
        cows = userOnes;
    }
    if (userZeros >= compZeros)
    {
        cows += compZeros;
    }
    else
    {
        cows += userZeros;
    }
    return cows;
}

int findBulls(string a, string b) // counts bulls
{
    int bulls = 0;
    for (int i = 0; i < 9; i++)
    {
        if (a[i] == b[i])
        {
            bulls += 1;
        }
    }
    
    return bulls;
}

string genterateCode()  // Generates secret code
{
    string secretCode;
    
    for (int i = 0; i < 9; i++)
    {
        secretCode[i] = myRand(0, 1);
    }
    
    return secretCode;
}


bool justNumbersCheck(string secretCode) // checks secret code is made of just 1's and 0's
{
    bool number = true;
    
    for (int i = 0; i < 9; i++)
    {
        bool one = true;
        bool zero = true;
        
        
        if (secretCode[i] != '1')
        {
            one = false;
            
            if (secretCode[i] != '0')
            {
                zero = false;
            }
        }
        
        if (one == false && zero == false)
        {
            number = false;
            break;
        }
    }
    return number;
}


string enterUserCode(int attempts, bool justNumbers) // lets user enter guess (GAME ONE)
{
    string userCode;
    do
    {
        
        if (justNumbers == false) // warns player when their code doesnt just contain 1's and 0's
        {
            cout << "Dont be silly! Try using just 1's and 0's in your secret code this time! " << endl;
            
        }
        
        cout << "-------------------------------" << endl;
        cout << "Please enter your 9 digit guess" << endl;
        cout << "-------------------------------" << endl;
        if (attempts == 6)
        {
            cout << "Its your last go! Good luck!" << endl; //warns player on their last attempt
        }
        cin >> userCode;
        if (userCode.size() != 9)
        {
            cout << "That wasnt 9 digits! Try again. " << endl;
        }
        
        justNumbers = justNumbersCheck(userCode ); // Check the secret code is made form just 1's and 0's
        
    } while (userCode.size() != 9 || justNumbers == false);
    
    return userCode;
}



//-------------------------FUNCTIONS(GAME TWO ONLY)------------------


string index2code (int i) // returns i (a 9 bit binary number) as a string
{
    return bitset<9>(i).to_string();
}



string getNextGuess(vector<bool>allPossible) // runs through remaining possible answers and picks one
{
    string nextGuess;
    for(int i = 0; i < 512; i++)
    {
        if(allPossible[i] == true)
        {
            nextGuess = index2code(i);
        }
    }
    return nextGuess;
}



bool eliminate(string indexElement, string guess, int originalCows, int originalBulls) // compares in guess to indexElement
{
    bool trueOrFalse;
    int guessOnes = countOnes(guess);
    int guessZeros = 9 - guessOnes;
    int indexElementOnes = countOnes(indexElement);
    int indexElementZeros = 9 - indexElementOnes;
    
    int tempCows = determineCows1(guessOnes, guessZeros, indexElementOnes, indexElementZeros);
    int tempBulls = findBulls(guess, indexElement);
    tempCows = tempCows - tempBulls;
    
    if (tempCows != originalCows || tempBulls!= originalBulls)
    {
        trueOrFalse = false;
    }
    else
    {
        trueOrFalse = true;
    }
    
    return trueOrFalse;
}






string enterSecretCode(bool justNumbers) // lets user enter secretCode
{
    string secretCode;
    
    do
    {
        
        
        if (justNumbers == false)
        {
            cout << "Dont be silly! Try using just 1's and 0's in your secret code this time! " << endl;
            cout << "--------------------------------------" << endl;
            cout << "Please enter a new code!"<< endl;
        }
        
        
        cin >> secretCode;
        if (secretCode.size() != 9)
        {
            cout << "That wasnt 9 digits! Try again. " << endl;
        }
        
        
        justNumbers = justNumbersCheck(secretCode ); // Check the secret code is made form just 1's and 0's
        
        
        
    }
    while(secretCode.size() != 9 || justNumbers == false);
    
    return secretCode;
}







//------------------------------GAME ONE---------------------------------


void gameOne()
{
    srand(time(NULL));
    
    
    string secretCode = genterateCode();
    
    
    
    /*  comment this back in to view secret code in game one when debugging. Shows the secret code the computer has generated.
     
    cout << "Secret Code: ";
    for (int i = 0; i < 9; i++)
    {
         cout << secretCode[i];
    }
    */
    cout << endl;
    
    
    
    
    bool victory = false; //variable to determine a win. loop breaks when victory = True
    int attempts = 0; //variable to determine amount of attempts. loop breaks when attempts = 7
    int finalBulls; // used for final print statement
    
    do
    {
        bool justNumbers = true;
        string userCode = enterUserCode(attempts, justNumbers); // lets user enter code
        
        
        attempts++; // Increases the attempt counter keeping track of amount of attempts
        
        cout << "Attempt "<< attempts << ": " << userCode << endl; //prints userCode and attempt number
        
        
        int compOnes = countOnes(secretCode);
        int compZeros = 9 - compOnes;
        int userOnes = countOnes(userCode);
        int userZeros = 9 - userOnes;
        
        
        int cows = determineCows1(userOnes, userZeros, compOnes, compZeros);//Determines cows ignoring bulls
        
        
        int bulls = findBulls(userCode, secretCode);//Determines Bulls
        
        
        
        cout << "Bulls: " << bulls << endl; // just prints bulls
        
        
        cows = cows - bulls;  // determines cows final step
        
        cout << "Cows: " << cows << endl; // just prints cows
        
        
        
        if (bulls == 9) // Determines a win
        {
            victory = true;
        }
        
        
        finalBulls = bulls; //for the final print statement
        
        
    } while (victory == false && attempts < 7);
    
    if (finalBulls == 9) // Print statement if they win
    {
        
        cout << "Secret Code:";
        for (int i = 0; i < 9; i++)
        {
            cout << secretCode[i];
        }
        
        if (attempts == 1)//print if they win first try
        {
            
            cout << endl;
            cout << "--------------WELL DONE!!!--------------" << endl;
            cout << "You broke my code in your first attempt!" << endl;
            cout << "----------------------------------------" << endl;
        }
        else //print if they win with more than one attempt
        {
            cout << endl;
            cout << "------------WELL DONE!!!------------" << endl;
            cout << "You broke my code in just " << attempts << " attempts!" << endl;
        }
    }
    else //Print if they lose
    {
        cout << "Better luck next time!" << endl;
        cout << "----------------------" << endl;
    }
    
 
}





//----------------------------GAME TWO-----------------------------------



void gameTwo()
{
    
    {
        int attempts = 0; //track attempts
        int bulls;
        int cows;
        string guess (9, '1'); // stores each guess. Computers first guess is always 9 1's
        vector<bool>allPossible(512, true); // records whether or not each element in index2code is a possible next guess
        
        
        cout << "--------------Time for me to crack your code!!!-------------" << endl;
        cout << "Please enter you secret 9 digit code made of ones and zeros!" << endl;
        
        bool justNumbers = true;
        

        
        string secretCode = enterSecretCode(justNumbers); //Lets User enter secret code
        
        
        
        
        /* as the computers first guess is (1,1,1,1,1,1,1,1,1) bulls would indicate the amount of ones (and therefore zeros) in any given secret code after the first guess. therefore I feel it is fair to use "countOnes()" to determine these values */
        
        
        
        int secretOnes = countOnes(secretCode); // tracks ones in secretCode
        int secretZeros = 9 - secretOnes; // tracks zeros in secretCode
        
        
        
        
        
        do // main loop
        {
            
            
            attempts ++; // increase attempts at start of each run
            bulls = 0; // bulls, cows, guessOnes and guessZeros all reset each iteration
            cows = 0;
            int guessOnes = countOnes(guess);
            int guessZeros = 9 - guessOnes;
            
            cows = determineCows1(guessOnes, guessZeros, secretOnes, secretZeros); // cows ignoring bulls
            
            bulls = findBulls(guess, secretCode); //finds bulls
            
            cows = cows - bulls; // cows final step
            
            
            cout << "Attempt " << attempts << ": " << guess << endl;
            cout << "Bulls: " << bulls << " Cows: " << cows << endl;
            
            
            
            
            
            
            
            
            if(bulls == 9) // if they've won break
            {
                break;
            }
            else // things to do if they havent won yet
            {
                cout << "---------------------------------" << endl;
                cout << "Press enter and I'll guess again!" << endl;
                cout << "---------------------------------" << endl;
                
                system("read"); // creates a pause (on mac, may need to change to "pause" for windows)
                
                for(int i = 0; i<512; i++) // go through each possible and eliminate impossible answers
                {
                    if(allPossible[i] == true)
                    {
                        string holder = index2code(i);
                        allPossible[i] = eliminate(holder, guess, cows, bulls); // eliminate impossible answers
                    }
                }
                
            }
            
            guess = getNextGuess(allPossible); // set next guess just before loop starts again
            
            
        }
        while( attempts <7);
        
        if(bulls == 9) // print if computer cracks the code
        {
            cout << "--------I CRACKED IT!!!--------" << endl;
            cout << "-IT ONLY TOOK ME " << attempts <<" ATTEMPTS!!!-" << endl;
            cout << "-------------------------------" << endl;
            
        }
        else // print if the computer doesnt get the combination
        {
            cout << "AH, YOU BEAT ME THIS TIME!!!" << endl;
            
        }
        
        
        
    }
    
}








//--------------------------------MAIN-----------------------------------



int main()
{
    
    cout << "-----Welcome to Bulls and Cows!!!-----" << endl;
    cout << endl;
    
    bool exit = false;
    
    do
    {
        char choice;
        
    
        cout << "MAIN MENU" << endl;
        cout << endl;
        cout << "Press (1) to try and crack my code!" << endl;
        cout << "Press (2) and I'll try crack your code!" <<endl;
        cout << "Press (i) for instructions!" <<endl;
        cout << "Press (q) to quit!" <<endl;
        cout << endl;
        cout << "--------------------------------------" <<endl;
        
        cin >> choice;
        
        if (choice == '1') // play game one
        {
            gameOne();
        }
        if (choice == '2') // play game two
        {
            gameTwo();
        }
        if (choice == 'i') // show instructions
        {
            cout << "Instructions:" << endl;
            cout << endl;
            cout << "In Cows and Bulls you are pitted against the computer, the aim is to uncover a 9 digit secret code made from 1's and 0's within just 7 attempts!!! After each attempt, if you havent guessed correctly, you will be told how many 'bulls' and how many 'cows' you have. 'bulls' represent the right number in the right postion (for example, if the secret code has a 1 in position 0, and the guess has a 1 in position 0 this would be a 'bull') and cows represent how many of the right number you have in wrong positions, not including any bulls." << endl;

            cout << endl;
            cout << "If you're finding it tricky press (2) on the main menu, i'll show you how its done!!!" << endl;
            
            cout << "---------------------------------------" << endl;
            cout << "Press enter to go back to the main menu" << endl;
            cout << "---------------------------------------" << endl;
            system("read"); // creates a pause (on mac, may need to change to "pause" for windows)
            
        }
        if (choice == 'q') // quits game
        {
            exit = true;
            cout << endl;
            cout << "--------------GOODBYE!!!--------------" << endl;
            cout << endl;
        }
        if (choice!= '1' && choice!= '2' && choice != 'i' && choice !='q')
        {
            cout << "Sorry, Lets try that again" << endl;
        }
        
        
    }
    while (exit == false);
    
    return 0;
}


/*
 TO DO:



 - *** change 'press enter for new guess' Mac/PC ***
 - try on windows before submitting
 
 
 */
