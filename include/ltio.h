#ifndef LT_64_IO_H
#define LT_64_IO_H

#include "ltconst.h"
#include "ltrun.h"
#include "stdio.h"
#include "stddef.h"

/* Read the bytes of the program from the given file into the given memory
 * array.
 * On success returns the length of the program in words. On errors prints a
 * message to stderr and returns 0. 
 */
size_t read_program(WORD* mem, const char* filename);

/* Display a range of words from memory as space separated hex values.
 * The range goes up to but not includeing end. I.e. [start, end).
 * If debug is true it prints the range to stderr instead of stdout.
 * I.e. display_range(memory, 1, 3);
 * (out) 00aa bbcc
 */
void display_range(WORD* mem, ADDRESS start, ADDRESS end, bool debug);

/* Print a null terminated string from memory.
 * Assumes each word holds two characters, one in the top byte
 * and one in the bottom byte of a 16 bit word. I.e. If a word is 0x6566
 * then AB would be printed for that word.
 * The given max is the maximum number of words to traverse if a null byte is
 * not found. Null bytes can be in either position to stop the printing.
 */
void print_string(WORD* mem, ADDRESS start, ADDRESS max);

/* Reads characters from stdin and stores them in memory starting from start.
 * Will read until a newline is discovered or the max number of characters
 * has been read. Every two characters will be packed into a word with the
 * first character read being in the words top byte. Always leaves at least one
 * null byte after the final read character. For an even number of characters
 * the next word is set to 0. For an uneven number of characters the top byte
 * of the last word is set to 0x00.
 *
 * TODO push a flag value onto the stack to indicate if max was reached before
 * all input characters were read. This way it is possible to know that more
 * input needs to be read.
 */
void read_string(WORD* mem, ADDRESS start, ADDRESS max);

/* Displays the name of a given op code to the given stream.
 */
void display_op_name(OP_CODE op, FILE* stream);

/* Main debugging function. Shows the state of the stack and the current op
 * along with some pointers.
 */
void debug_info_display(WORD* data_stack, WORD* return_stack, ADDRESS dsp,
                        ADDRESS rsp, ADDRESS pc, WORD op);

/* If steps is 0 it will pause and ask for a steps value. Pressing enter without
 * a value will pause again on the next call. Giving a value will return that
 * value. If called with a non-zero steps count will not pause and will
 * return the steps - 1.
 */
size_t debug_step(size_t steps);

#endif
