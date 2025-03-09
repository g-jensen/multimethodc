#include "specc.h"

__fun_list* __head = NULL; 
__fun_list* __tail = NULL;

size_t __pass_count = 0;
size_t __fail_count = 0;
size_t __fail_line = -1;
size_t __nest_level = 0;
int __spec_result = -1;
char* __current_fmt = NULL;
char* __current_it_msg = "[specc] something went wrong!";

void __fun_list_add(__function f) {
  if (!__head) {
    __head = (__fun_list*)malloc(sizeof(__fun_list));
    __head->f = f;
    __head->next = NULL;
    __tail = __head;
  } else {
    __tail->next = (__fun_list*)malloc(sizeof(__fun_list));
    __tail->next->f = f;
    __tail->next->next = NULL;
    __tail = __tail->next;
  }
}

void __printf_color_and_nest(size_t nest_level, const char* color, const char * format, ...) {
  va_list args;
  va_start(args,format);
  for (size_t i = 0; i < nest_level; i++) {
    printf("  ");
  }
  printf("%s",color);
  vprintf(format,args);
  printf(SPECC_COLOR_CLEAR);
}

const char* __type_to_fmt(const char* type) {
  if      (strcmp("char",type) == 0)
    return " | Expected: \'%c\' Actual: \'%c\'";
  else if (strcmp("int",type) == 0)
    return " | Expected: %d Actual: %d";
  else if (strcmp("float",type) == 0)
    return " | Expected: %f Actual: %f";
  else if (strcmp("unsigned int",type) == 0)
    return " | Expected: %i Actual: %i";
  else if (strcmp("short",type) == 0)
    return " | Expected: %hi Actual: %hi";
  else if (strcmp("unsigned short",type) == 0)
    return " | Expected: %hu Actual: %hu";
  else if (strcmp("long",type) == 0)
    return " | Expected: %ld Actual: %ld";
  else if (strcmp("long double",type) == 0)
    return " | Expected: %Lf Actual: %Lf";
  else if (strcmp("double",type) == 0)
    return " | Expected: %lf Actual: %lf";
  else if (strcmp("unsigned long",type) == 0)
    return " | Expected: %lu Actual: %lu";
  else if (strcmp("unsigned long long",type) == 0)
    return " | Expected: %hu Actual: %hu";
  else 
    return " | Expected: %p Actual: %p";
}

void static print_summary(size_t pass_count, size_t fail_count) {
  size_t total = pass_count + fail_count;
  printf("\nSpec Summary:\n");
  __printf_color_and_nest(0, SPECC_COLOR_GREEN,"- %lu Passed\n",pass_count);
  __printf_color_and_nest(0, SPECC_COLOR_RED,"- %lu Failed\n",fail_count);
  printf("- %lu Total\n",total);
}

void static call_flist(__fun_list* head) {
  __fun_list* cur = NULL; 
  for(cur = head; cur; cur = cur->next) {
    cur->f(); 
  }
}

void static free_flist(__fun_list* head) {
  if (head) {free_flist(head->next);}
  free(head);
}

int main() {
  call_flist(__head);
  free_flist(__head);
  print_summary(__pass_count,__fail_count);
}