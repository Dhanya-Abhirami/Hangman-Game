#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

const int MAX_TRIES=5;

int letterFill (char guess, string secretword, string &guessword)
{
    int i;
    int matches=0;
    int len=secretword.length();
    for (i = 0; i< len; i++)
    {
    // Did we already match this letter in a previous guess?
    if (guess == guessword[i])
    return 0;

    // Is the guess in the secret word?
        if (guess == secretword[i])
        {
            guessword[i] = guess;
            matches++;
        }
    }
return matches;
}


int main ()
{
    string name;
    char letter;
    int num_of_wrong_guesses=0;

   //Input file
   ifstream inFile;
   inFile.open("dictionary2.txt");

   //Vector with elements preallocated
   //to increase push_back speed
   vector<string> dict;

    //Temporary string
    string temp;

    //Grab words from file into vector
    while(inFile >> temp)
    {
      dict.push_back( temp );
    }
    //Close input file
    inFile.close();

    //Seed random number generator
    srand(time(NULL));

    //Generate a random index
    int index = rand() % dict.size();

    //Word to use for hangman
    string hangManWord = dict[index];
    cout << hangManWord << endl;


    // Initialize the secret word with the * character.
    string unknown(hangManWord.length(),'*');

    // welcome the user
    cout << "\nWelcome to hangman";
    cout << "\nEach letter is represented by an underscore.";
    cout << "\nYou have to type only one letter in one try";
    cout << "\nYou have " << MAX_TRIES << " attempts left";
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    // Loop until the guesses are used up
    while (num_of_wrong_guesses < MAX_TRIES)
    {
        cout << "\n" << unknown;
        cout << "\n Guess a letter: ";
        cin >> letter;
        // Fill secret word with letter if the guess is correct,
        // otherwise increment the number of wrong guesses.
        if (letterFill(letter, hangManWord, unknown)==0)
        {
            cout << endl << "Whoops! That letter isn't in there!" << endl;
            num_of_wrong_guesses++;
        }
        else
        {
            cout << endl << "You found a letter! Isn't that exciting!" << endl;
        }
        // Tell user how many guesses has left.
        cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
        cout << " guesses left." << endl;
        // Check if user guessed the word.
        if (hangManWord==unknown)
        {
            cout << hangManWord << endl;
            cout << "Yeah! You got it!";
            break;
        }
    }
    if(num_of_wrong_guesses == MAX_TRIES)
    {
        cout << "\nSorry, you lose...you've been hanged." << endl;
        cout << "The word was : " << hangManWord << endl;
    }
    cin.ignore();
    cin.get();
    return 0;
}
