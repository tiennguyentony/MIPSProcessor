//**********************************************************************
//* This class reads in a MIPS assembly file and checks its syntax.  If
//* the file is syntactically correct, this class will retain a list 
//* of Instructions (one for each instruction from the file).  This
//* list of Instructions can be iterated through.
#ifndef __ASMPARSER_H__
#define __ASMPARSER_H__

#include <iostream>
#include <fstream>
#include "Converter.h"
#include "Instruction.h"
#include "RegisterTable.h"
#include "Opcode.h"
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

class ASMParser{
 public:

  ASMParser();
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
  ASMParser(string filename);

  // Returns true if the file specified was syntactically correct.  Otherwise,
  // returns false.
  bool isFormatCorrect() { return myFormatCorrect; };

  // Iterator that returns the next Instruction in the list of Instructions.
  Instruction getNextInstruction();

  string getAssemblyLine(string encoding);

private:
  std::map<std::string,std::string> myMap; //map holding the assembly line instructions and their corresponding encoding
  vector<Instruction> myInstructions;      // list of Instructions
  int myIndex;                             // iterator index
  bool myFormatCorrect;
  Converter converter;

  RegisterTable registers;                 // encodings for registers
  OpcodeTable opcodes;                     // encodings of opcodes
  int myLabelAddress;   // Used to assign labels addresses

  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
  void getTokens(string line, string &opcode, string *operand, int &num_operands);

  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
  bool getOperands(Instruction &i, Opcode o, string *operand, int operand_count);

  // Return list of instructions
  const vector<Instruction>& getInstruction() const {return myInstructions;}
  // Helper functions
  bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };
  bool isDigit(char c)         { return (c >= '0' && c <= '9'); };
  bool isAlphaUpper(char c)    { return (c >= 'A' && c <= 'Z'); };
  bool isAlphaLower(char c)    { return (c >= 'a' && c <= 'z'); };
  bool isSign(char c)          { return (c == '-' || c == '+'); };
  bool isAlpha(char c)         {return (isAlphaUpper(c) || isAlphaLower(c)); };
  
  // Returns true if s represents a valid decimal integer
  bool isNumberString(string s);

  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
  int  cvtNumString2Number(string s);


  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
  string encode(Instruction i);

  // Helper functions to encode specific instruction types; returns a string of the binary
  // encoding for the given instruction.
  string encodeRTYPE( Instruction i );
  string encodeITYPE( Instruction i );
  string encodeJTYPE( Instruction i );

  string removeSpaces(string input);

};

#endif
