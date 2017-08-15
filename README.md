# MasterMind

1. Mastermind is a 2-player boardgame wherein one player the \Codemaster" prepares a code
of four colours from a set of six, the \Codebreaker" then repeatedly tries to guess the code
and receives feedback from the Codemaster. The feedback given by the Codemaster is in
the form of white and black pegs where each white peg represents a correct colour in the
wrong position and a black peg represents a correct colour in the correct position. For this
question you will create a class Mastermind that acts as the Codemaster in a variant of this
game. In this variant the passcode, instead of being of length 4 can be any length greater
than 0. Your Mastermind should take in three integers in its constructor, the rst parameter
being the random seed, the second the length of the code, and the last the number of guesses
the \Codebreaker" has to guess the code. You may assume the codeLength and guessLimit
being passed to your constructor are greater than zero. Each character in the passcode in
our game will be one of the characters in the set (A;B;C;D;E; F): Consider the following
object definition for the Mastermind class.


struct Mastermind {
int seed;
int codeLength;
int guessLimit;
char* code;
Mastermind(int seed, int codeLength, int guessCount);
~Mastermind();
playGame();
};


You must implement the undened constructor, destructor, and playGame method to the
following specications. You may add any data members or helper methods you want to the
class, and indeed you will need to add some data member to the class to hold the passcode
in any way you see t. For this problem you will include cstdlib and use the srand and
rand functions as per the specications. The specications for password generation are very
important as if you do not follow them exactly you will fail the test cases.
 Upon construction you must call srand once on the seed passed to your constructor.
 Upon a call to playGame you must rst set the password, with exactly codeLength
calls to rand without any other rand calls in your program, setting the characters in
the passcode starting with index 0 until every character has been set. Each character
should be set based on the remainder of the rand call when divided by 6, a 0 representing
A, 1 representing B, etc.
 Once the password is set playGame should print out the welcome message and read in
from stdin until you've received codeLength valid characters.
 When reading in characters from the user you must accept upper and lowercase charac-
ters from the set (A,B,C,D,E,F) as valid characters and ignore any other input.
 After each guess you should print out the number of black and white pegs the user
got correct in form \Xb, Yw" where X and Y are the number of black and white pegs
respectively. Then if the game has not been won or lost you should print out the next
guess message which includes the number of guesses left and read in another guess.
 If the code is guessed before the guess limit is reached you should print the win message
\You won in guessCount guesses!"
 If the code is not guessed before the guess limit is reached you should print the loss
message \You lost! The password was:" and print the password on the following line.
 The number of black pegs given for each guess is equal to the number of characters the
user has in the correct position in the code.
 The number of white pegs given for each guess is equal to the number of characters the
user has that are in the code but in the wrong position, however the number of black
and white pegs can never exceed the size of the code. This means that if a code has
only one A and the user guesses 2 A's in the wrong position they receive only one white
peg for A, additionally if the code has only one A and the user has guessed 3 A's, two
in the wrong position and one in the correct position the user only receives the single
black peg for the A's - no white peg.
 Once the game is over, win or lose, you must ask the user if they would like to play again
and if they enter Y or y you must recursively call playGame otherwise you are done.
For example consider the following playGame call example to a Mastermind object that was
initialized with 5, 4, 3. Lines preceded with > represent user input. You must follow the
exact message form as shown below.

Welcome to Mastermind! Please enter your first guess.
>AAAA
2b,0w
2 guesses left. Enter guess:
>BCDE
1b,0w
1 guesses left. Enter guess:
>bcaa
3b,0w
You lost! The password was:
BFAA
Would you like to play again? (Y/N): N
Note that the N in the last line is input by the user. You will be provided a simple test harness
main.cc that will take in four command line arguments corresponding to seed, codeLength,
and guessLimit and constructs a Mastermind object with those values and calls playGame,
do not modify this file.

