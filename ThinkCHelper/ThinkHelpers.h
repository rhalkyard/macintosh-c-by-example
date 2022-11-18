/* Helper functions and macros provided by THINK C that are not present in the
 * Retro68 headers
 */

/* Extract the high and low words of a 32-bit long value. */
#define HiWord(x) ((x) >> 16)
#define LoWord(x) ((x) & 0xffff)

/* Shortcuts for getting the top-left and bottom-right points of a Rect */
#define topLeft(r) (*((Point*) &(r).top))
#define botRight(r) (*((Point*) &(r).bottom))

/* Inplace conversion of Pascal to C strings and vice-versa */
void PtoCstr(char *);
void CtoPstr(char *);
