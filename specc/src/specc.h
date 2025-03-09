#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define SPECC

typedef void (*__function)(void);

struct __fun_list { 
  struct __fun_list* next; 
  __function f;
};

typedef struct __fun_list __fun_list;

extern __fun_list* __head; 
extern __fun_list* __tail;

extern size_t __pass_count;
extern size_t __fail_count;
extern size_t __fail_line;
extern size_t __nest_level;
extern int __spec_result;
extern char* __current_fmt;
extern char* __current_it_msg;

void __fun_list_add(__function f);
void __printf_color_and_nest(size_t nest_level, const char* color,const char * format, ...);
const char* __type_to_fmt(const char* type);

void static print_summary(size_t pass_count, size_t fail_count);
void static call_flist(__fun_list* head);
void static free_flist(__fun_list* head);

#define SPECC_PASS 1
#define SPECC_FAIL 0

#define SPECC_COLOR_GREEN "\033[0;32m"
#define SPECC_COLOR_RED "\033[1;31m"
#define SPECC_COLOR_CLEAR "\033[0m"

#define module(f,tests) \
  static void f(void); \
  static void __attribute__((constructor)) __construct_##f(void) {\
    __fun_list_add(f);\
  }\
  static void f(void) {printf("[%s]\n",__func__); tests}

#define describe(msg,...) __printf_color_and_nest(__nest_level,SPECC_COLOR_CLEAR,"- %s\n",msg); __nest_level++; {__VA_ARGS__}  __nest_level--;

#define context(msg,...) describe(msg,__VA_ARGS__)

#define pass() __spec_result = SPECC_PASS; __fail_line = -1

#define __inline_specc_fail()\
  __spec_result = SPECC_FAIL; \
  if (__fail_line == -1) \
  {__fail_line = __LINE__;} \
  __fail_count++; \
  __printf_color_and_nest(__nest_level, SPECC_COLOR_RED,"X %s\n",__current_it_msg);\
  __printf_color_and_nest(__nest_level+1, SPECC_COLOR_RED,"- %s:%d",__FILE__,__fail_line);\


#define specc_fail() \
  if (__spec_result != SPECC_FAIL) { \
    __inline_specc_fail(); \
    printf("\n"); \
  }

#define specc_fail_message(fmt, ...) \
  if (__spec_result != SPECC_FAIL) {\
    __inline_specc_fail();\
    printf(fmt,__VA_ARGS__); \
    printf("\n"); \
  }

#define it(msg, ...) \
  __current_it_msg = msg; \
  pass(); \
  {\
  __VA_ARGS__\
  }\
  if (__spec_result == SPECC_PASS) {\
    __pass_count++; \
    __printf_color_and_nest(__nest_level, SPECC_COLOR_GREEN,"- %s\n",msg);\
  }\

#define should(assertion) if (!(assertion)) {specc_fail();}

#define should_not(assertion) should(!(assertion))

#define should_eq(expected, actual, type) \
  if (!((expected) == (actual))) { \
    specc_fail_message((char*)__type_to_fmt(#type),expected,actual)\
  }

#define should_not_eq(expected, actual, type) \
  if (((expected) == (actual))) { \
    specc_fail_message((char*)__type_to_fmt(#type),expected,actual)\
  }

#define should_str_eq(expected, actual) \
  if (strcmp(expected,actual) != 0) { \
    specc_fail_message(" | Expected: \"%s\" Actual: \"%s\"",expected,actual)\
  }

#define should_str_not_eq(expected, actual) \
  if (strcmp(expected,actual) == 0) { \
    specc_fail_message(" | Expected strings to be different: \"%s\"",expected)\
  }

#define should_double_eq(expected,actual,err)\
  if (!(expected+err >= actual && expected-err <= actual)) {\
    specc_fail_message(" | Expected: %lf Actual: %lf With Error: %lf",expected,actual,err)\
  }

#define should_double_not_eq(expected,actual,err)\
  if (expected+err >= actual && expected-err <= actual) {\
    specc_fail_message(" | Expected: %lf Actual: %lf With Error: %lf",expected,actual,err)\
  }

#define should_float_eq(expected,actual,err)\
  if (!(expected+err >= actual && expected-err <= actual)) {\
    specc_fail_message(" | Expected: %f Actual: %f With Error: %f",expected,actual,err)\
  }

#define should_float_not_eq(expected,actual,err)\
  if (expected+err >= actual && expected-err <= actual) {\
    specc_fail_message(" | Expected: %f Actual: %f With Error: %f",expected,actual,err)\
  }
  