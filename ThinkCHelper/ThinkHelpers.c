#include <string.h>
#include <OSUtils.h>

/* Helper functions for in-place conversion of null-terminated C strings to
 * length-prefixed Pascal strings and vice-versa.
 */

void CtoPstr(char * str) {
    const unsigned char len = strlen(str);

    memmove(str+1, str, len);
    str[0] = len;
}

void PtoCstr(char * str) {
    const unsigned char len = str[0];

    memmove (str, str+1, len);
    str[len] = '\0';
}
