
#include <stdio.h>

int counterStore[3] = {0, 0, 0};
int counterLoad[3] = {0, 0, 0};
int counterArithOp[3] = {0, 0, 0};
int counterCmpOp[3] = {0, 0, 0};

int counterFPTruncInst = 0;
int counterFPExtInst = 0;

long int score = 0;

// Store Instruction
void incrementStoreInstFloat() {
  counterStore[0]++;
  score += 8;
}

void incrementStoreInstDouble() {
  counterStore[1]++;
  score += 8;
}

void incrementStoreInstLongDouble() {
  counterStore[2]++;
  score += 8;
}

// Load Instruction
void incrementLoadInstFloat() {
  counterLoad[0]++;
  score += 8;
}

void incrementLoadInstDouble() {
  counterLoad[1]++;
  score += 8;
}

void incrementLoadInstLongDouble() {
  counterLoad[2]++;
  score += 8;
}

// ArithOp Instruction
void incrementArithOpInstFloat() {
  counterArithOp[0]++;
  score += 20;
}

void incrementArithOpInstDouble() {
  counterArithOp[1]++;
  score += 30;
}

void incrementArithOpInstLongDouble() {
  counterArithOp[2]++;
  score += 40;
}


// CmpOp Instruction
void incrementCmpOpInstFloat() {
  counterCmpOp[0]++;
  score += 20;
}

void incrementCmpOpInstDouble() {
  counterCmpOp[1]++;
  score += 30;
}

void incrementCmpOpInstLongDouble() {
  counterCmpOp[2]++;
  score += 40;
}


// Cast Instructions
void incrementFPTruncInst() {
  counterFPTruncInst++;
  score += 1;
}

void incrementFPExtInst() {
  counterFPExtInst++;
  score += 1;
}



// Printing counters
void printCounters() {
  printf("StoreInst\n");
  printf("\tFloat: %d\n", counterStore[0]);
  printf("\tDouble: %d\n", counterStore[1]);
  printf("\tLongDouble: %d\n", counterStore[2]);

  printf("LoadInst\n");
  printf("\tFloat: %d\n", counterLoad[0]);
  printf("\tDouble: %d\n", counterLoad[1]);
  printf("\tLongDouble: %d\n", counterLoad[2]);

  printf("ArithOpInst\n");
  printf("\tFloat: %d\n", counterArithOp[0]);
  printf("\tDouble: %d\n", counterArithOp[1]);
  printf("\tLongDouble: %d\n", counterArithOp[2]);

  printf("CmpOpInst\n");
  printf("\tFloat: %d\n", counterCmpOp[0]);
  printf("\tDouble: %d\n", counterCmpOp[1]);
  printf("\tLongDouble: %d\n", counterCmpOp[2]);

  printf("CastInst\n");
  printf("\tTruncInst: %d\n", counterFPTruncInst);
  printf("\tExtInst: %d\n", counterFPExtInst);

  printf("Score: %ld\n", score);

  return;
}
