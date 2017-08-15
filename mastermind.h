#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_

struct Mastermind {
  int seed;
  int codeLength;
  int guessLimit;
  char* code;
  Mastermind();
  // You may add any data members you require
  // as well as any member functions you like.
  // So long as all the methods below are properly
  // implemented.
  Mastermind(int seed, int codeLength, int guessLimit);
  ~Mastermind();
  void playGame();
};

#endif
