#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define bufsize 80

int var_arg(char *fmt, ...);

int main(){
	var_arg("This", "is", "a", "variable", "arg", "func", "\0");
	return 0;
}

int var_arg(char *fmt, ...){
	va_list ap;
	char buf[bufsize];

	va_start(ap, fmt);
	vsnprintf(buf, bufsize, fmt, ap);
	puts(buf);
	while (1) {
		char *arg = va_arg(ap, char *);
		if (arg == "\0")
		    break;
		printf("arg: %s\n", arg);
	}
	va_end(ap);
}
