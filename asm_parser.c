/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : Huifang Ye                                                *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										                                       * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */

int read_asm_file (char* filename, char program [ROWS][COLS]) {
  char line[COLS];
  int word_len = 0;
  
  // read file by the filename
  FILE *file = fopen(filename, "r");
  
  // error check the filename
  if (!file) {
    fprintf(stderr, "error2: read_asm_file() failed\n");
    return 2;
  }
  
  for (int i = 0; i < ROWS; i++) {               // iterate line by line through the file
    if (fgets(line, COLS, file) != NULL){
      for (int j = 0; j < COLS; j++) {
        // calculate the word length in every row
        if (line[j] == '\0' ||line[j] == '\r' || line[j] == '\n'){                    // when it reaches the end
            word_len = j;
            if (word_len >= COLS) {                                                      // if the word length exceeds the COLS, print an error
                  fprintf(stderr, "error2: read_asm_file() failed\n");
                  return 2;
            }
         break;
        }
      }
      
      // store the characters to the program[][]
      for (int k = 0; k < word_len; k++) {
        program[i][k] = line[k];
      }
      program[i][word_len] = '\0';
    } else {
      program[i][0] = '\0';
    }
  }
    
    // test for read_asm_file() functionality
//     for (int a = 0; a < ROWS; a++) {
//       for (int b = 0; b < COLS; b++) {
//         printf("%c", program[a][b]);
//       }
//     printf("\n");
//   }
    
    if (feof(file)) {                            // successfully read the entire file
      fclose(file);
      return 0;
    } else {                                     // something wrong happened so return an error
      fprintf(stderr, "error2: read_asm_file() failed\n");
      fclose(file);
      return 2;
    }
  return 0;
}

int parse_instruction (char* instr, char* instr_bin_str){
  char *token;
  
  // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error3: parse_instruction() failed.\n");
    return 3;
  }
  
  // get the opcode, the delimiter is " "
  token = strtok(instr, " ");
  
  // decide the opcode to later convert it into a binary equivalent
  if (strcmp(token, "ADD") == 0) {
    parse_add(instr, instr_bin_str);
  } else if (strcmp(token, "MUL") == 0) {
    parse_mul(instr, instr_bin_str);
  } else if (strcmp(token, "SUB") == 0) {
    parse_sub(instr, instr_bin_str);
  } else if (strcmp(token, "DIV") == 0) {
    parse_div(instr, instr_bin_str);
  } else if (strcmp(token, "AND") == 0) {
    parse_and(instr, instr_bin_str);
  } else if (strcmp(token, "OR") == 0) {
    parse_or(instr, instr_bin_str);
  } else if (strcmp(token, "XOR") == 0) {
    parse_xor(instr, instr_bin_str);
  } else {
    fprintf(stderr, "error3: parse_instruction() failed.\n");
    return 3;
  }
  
  return 0;
}

int parse_reg (char reg_num, char* instr_bin_str) {
  
  char *binary_char;
  
  // error check  
  if (reg_num == '\0'||((reg_num != '0')&&(reg_num != '1')&&(reg_num != '2')&&(reg_num != '3')&&(reg_num != '4')&&(reg_num != '5')&&(reg_num != '6')&&(reg_num != '7'))) {
    fprintf(stderr, "error5: parse_reg() failed.\n");
    return 5;      
  }
  
  switch(reg_num) {
    case '0':
      binary_char = "000";
      break;
    case '1':
      binary_char = "001";
      break;
    case '2':
      binary_char = "010";
      break;
    case '3':
      binary_char = "011";
      break;
    case '4':
      binary_char = "100";
      break;
    case '5':
      binary_char = "101";
      break;
    case '6':
      binary_char = "110";
      break;     
    case '7':
      binary_char = "111";
      break;       
  }
  strcat(instr_bin_str, binary_char);
  return 0;
}

int parse_add (char* instr, char* instr_bin_str) {
  // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_add() failed.\n");
    return 4;
  }
  
  // ADD Rd, Rs, Rt -> 0001dddsss000ttt
  char *opcode = "0001";                               // the opcode of ADD is 0001
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "000";                               // the subopcode of ADD is 000
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  
  // return 0 if no error
  return 0;
}

int parse_mul (char* instr, char* instr_bin_str){
    // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_mul() failed.\n");
    return 4;
  }
  
  // MUL Rd, Rs, Rt -> 0001dddsss001ttt
  char *opcode = "0001";                               // the opcode of MUL is 0001
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "001";                               // the subopcode of MUL is 001
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}

int parse_sub (char* instr, char* instr_bin_str) {
  // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_sub() failed.\n");
    return 4;
  }
  
  // SUB Rd, Rs, Rt -> 0001dddsss010ttt
  char *opcode = "0001";                               // the opcode of SUB is 0001
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "010";                               // the subopcode of SUB is 010
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}

int parse_div (char* instr, char* instr_bin_str) {
  // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_div() failed.\n");
    return 4;
  }
  
  // DIV Rd, Rs, Rt -> 0001dddsss011ttt
  char *opcode = "0001";                               // the opcode of DIV is 0001
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "011";                               // the subopcode of SUB is 011
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}
int parse_and (char* instr, char* instr_bin_str) {
    // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_and() failed.\n");
    return 4;
  }
  
  // AND Rd, Rs, Rt -> 0101dddsss000ttt
  char *opcode = "0101";                               // the opcode of AND is 0101
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "000";                               // the subopcode of AND is 000
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}
int parse_or (char* instr, char* instr_bin_str) {
      // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_or() failed.\n");
    return 4;
  }
  
  // OR Rd, Rs, Rt -> 0101dddsss010ttt
  char *opcode = "0101";                               // the opcode of OR is 0101
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "010";                               // the subopcode of OR is 010
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}

int parse_xor (char* instr, char* instr_bin_str) {
  // error check
  if (instr == '\0' || instr == NULL) {
    fprintf(stderr, "error4: parse_xor() failed.\n");
    return 4;
  }
  
  // XOR Rd, Rs, Rt -> 0101dddsss011ttt
  char *opcode = "0101";                               // the opcode of XOR is 0101
  for (int i = 0; i < 4; i++) {
    instr_bin_str[i] = opcode[i];                      // save the opcode to instr_bin_str
  }
  
  // pass the binary character after the first "R" and change it into binary character
  char *token = NULL;
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);

  // pass the binary character after the second "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // pass the subopcode to instr_bin_str string
  char *subopcode = "011";                               // the subopcode of XOR is 011
  for (int i = 0; i < 3; i++) {
    instr_bin_str[i + 10] = subopcode[i];                // save the subopcode to instr_bin_str
  }
  
  // pass the binary character after the third "R" and change it into binary character
  token = strtok(NULL, ", ");
  parse_reg(token[1], instr_bin_str);
  
  // return 0 if no error
  return 0;
}

unsigned short int str_to_bin (char* instr_bin_str) {
  unsigned short int binary;
  // use strtol() to get take a binary string and convert it to binary
  binary = strtol(instr_bin_str, NULL, 2);
  if (binary == 0) {
    fprintf(stderr, "error6: str_to_bin() failed.\n");
    return 6;
  }
  // test of str_to_bin() function
//   printf("The hex equivalent is 0x%X\n", binary);
  return binary;
}

// unsigned short int endian_convert(unsigned short int num) {
//   unsigned short int byte0;
//   unsigned short int byte1;
//   unsigned short int swap_value;
//   byte0 = (num & 0x00FF) >> 0;
//   byte1 = (num & 0xFF00) >> 8;
//   swap_value = ((byte0 << 8) | (byte1 << 0));
//   return swap_value;
// }

int write_obj_file (char* filename, unsigned short int program_bin[ROWS]){
  
  // change the last 4 letters of filename to ".obj"
  const char *index = strchr(filename, '.');
  
  filename[index - filename + 1] = 'o';
  filename[index - filename + 2] = 'b';
  filename[index - filename + 3] = 'j';
  
  // open up the file for writing and in "binary" format
  FILE *obj_file = fopen("tmp", "wb");
  
  // error check
  if (obj_file == NULL || obj_file == '\0') {
    fprintf(stderr, "error7: write_obj_file() failed.\n");
    return 7;
  }  
  
  // write out the first word in the header: 0xCADE
  unsigned short int cade = 0xCADE;
  fwrite(&cade, sizeof(unsigned short int), 1, obj_file);
  
  // write out the the address 0x0000 thee program should be loaded at
  unsigned short int address = 0x0000;
  fwrite(&address, sizeof(unsigned short int), 1, obj_file);
  
  // count the number of rows that contain data and write out <n>
  int row_num = 0;
  for (;program_bin[row_num]; row_num++);
  fwrite(&row_num, sizeof(unsigned short int), 1, obj_file);
  fwrite(program_bin, sizeof(unsigned short int), row_num, obj_file);
  fclose(obj_file);
  
  // swap the file
  unsigned short int tmp[1];
  FILE *obj_file1 = fopen("tmp", "rb");
  FILE *final = fopen(filename, "wb");
  
  if (obj_file1 == NULL || final == NULL){
    fprintf(stderr, "error2: read_asm_file() failed\n");
    return 7;
  }
  
  while(fread(tmp, sizeof(unsigned short int), 1, obj_file1)){
    *tmp = (*tmp >> 8) | (*tmp << 8);
    fwrite(&tmp, sizeof(unsigned short int), 1, final);
  }
  
  fclose(final);
  fclose(obj_file1);
  return 0;
}

