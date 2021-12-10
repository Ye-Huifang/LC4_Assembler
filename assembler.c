/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : Huifang                                                   *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										                         * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

	char* filename = NULL ;									  // name of ASM file
	char  program [ROWS][COLS] ; 							// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		    // instructions converted to a binary string
	unsigned short int program_bin [ROWS] ;   // instructions in binary (HEX)
  
  // initialize all arrays to 0 or '\0'
  for (int i = 0; i < ROWS; i++){
      for (int j = 0; j < COLS; j++) {
            program [i][j] = '\0';
      }
  }
  
  for (int i = 0; i < ROWS; i++){
      for (int j = 0; j < 17; j++) {
            program_bin_str [i][j] = '\0';
      }
  }
  
  // read in the arguments & error checking for filename
  if (argc != 2 || argv[1] == '\0') {
    fprintf(stderr, "error1: usage: ./assembler <assembly_file.asm>\n");
    return 1;                               // the program does not execute successfully and there is some error
  } else {
    filename = argv[1];
    if (strcmp(argv[1] + strlen(filename) - 4, ".asm") != 0) {
         fprintf(stderr, "error1: usage: ./assembler <assembly_file.asm>\n");
         return 1;                               // the program does not execute successfully and there is some error
    }
  }
  // test for filename
//   printf("Success! The file name is: ");
//   for (int i = 0; i < strlen(argv[1]); i++) {
//       printf("%c", argv[1][i]);
//   }
//   printf("\n");
  
  // Call read_asm_file() to read entire ASM file into the array: program[][]
  read_asm_file(filename, program);
  
  // in a loop, for each row X in program[][]
  for (int i = 0; program[i][0]; i++) {
    // call parse_instruction(), pass it the current row in program[X][] as input to parse_instruction
    char *instru = program[i];
    char *instru_bin_str = program_bin_str[i];
    parse_instruction(instru, instru_bin_str);
//     printf("%s\n", instru_bin_str);
    program_bin[i] = str_to_bin(instru_bin_str);
  }
  
  // write out the object filename
  write_obj_file(filename, program_bin);
  
  return 0;
}
