#include "ltrun.h"
#include "ltconst.h"
#include "ltio.h"
#include "stdio.h"
#include "stdbool.h"

size_t execute(WORD* memory, size_t length, WORD* data_stack, WORD* return_stack) {
  ADDRESS dsp, rsp, pc;
  dsp = 0;
  rsp = 0;
  pc = 0;

  WORD temp;
  
  bool run = true;
  while (run) {

    switch (memory[pc]) {
      case HALT:
        run = false;
        break;
      case PUSH:
        data_stack[++dsp] = memory[++pc];
        break;
      case POP:
        dsp--;
        break;
      case LOAD:
        data_stack[dsp] = memory[END_MEMORY - data_stack[dsp]];
        break;
      case STORE:
        memory[END_MEMORY - data_stack[dsp]] = data_stack[dsp-1];
        dsp-=2;
        break;
      case FST:
        data_stack[dsp+1] = data_stack[dsp];
        dsp++;
        break;
      case SEC:
        data_stack[dsp+1] = data_stack[dsp-1];
        dsp++;
        break;
      case NTH:
        data_stack[dsp] = data_stack[dsp - data_stack[dsp] - 1];
        break;
      case SWAP:
        temp = data_stack[dsp];
        data_stack[dsp] = data_stack[dsp-1];
        data_stack[dsp-1] = temp;
        break;
      case ROT:
        temp = data_stack[dsp-2];
        data_stack[dsp-2] = data_stack[dsp-1];
        data_stack[dsp-1] = data_stack[dsp];
        data_stack[dsp] = temp;
        break;
      case RPUSH:
        return_stack[++rsp] = data_stack[dsp--];
        break;
      case RPOP:
        data_stack[++dsp] = return_stack[rsp--];
        break;
      case RGRAB:
        data_stack[++dsp] = return_stack[rsp];
        break;

      /// BAD OP CODE ///
      default:
        fprintf(stderr, "Error: Unknown OP code: 0x%hx\n", memory[pc]);
        exit(EXIT_OP);
    }
    pc++;
  }

  // Test output
  if (TESTING) {
    display_range(data_stack, 0x0001, dsp + 1);
  }

  return EXIT_SUCCESS;
}
