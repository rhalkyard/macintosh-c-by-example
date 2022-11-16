#include <string.h>
#include <OSUtils.h>

void CtoPstr(char * str) {
    unsigned char len = strlen(str);

    memmove(str+1, str, len);
    str[0] = len;
}

void PtoCstr(char * str) {
    unsigned char len = str[0];

    memmove (str, str+1, len);
    str[len] = '\0';
}
