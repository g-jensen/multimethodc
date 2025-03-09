#include <stdlib.h>

#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )

#define defmulti(return_type, function_name, dispatch_type, param_type, param_name)\
typedef return_type (*MACRO_CONCAT(__function__, function_name))(param_type param_name); \
typedef struct MACRO_CONCAT(___fun_node, function_name) MACRO_CONCAT(___fun_node, function_name); \
struct MACRO_CONCAT(___fun_node, function_name) { \
  MACRO_CONCAT(___fun_node, function_name)* next; \
  dispatch_type dispatch_value; \
  MACRO_CONCAT(__function__, function_name) f; \
}; \
extern MACRO_CONCAT(___fun_node, function_name)* function_name ## _head; \
extern MACRO_CONCAT(___fun_node, function_name)* function_name ## _tail; \
dispatch_type function_name ## _dispatch_fn (param_type param_name); \
return_type function_name (param_type param_name);

#define _implmulti(return_type, function_name, default_value, dispatch_type, param_type, param_name, compare_expression)\
MACRO_CONCAT(___fun_node, function_name)* function_name ## _head = NULL; \
MACRO_CONCAT(___fun_node, function_name)* function_name ## _tail = NULL; \
return_type function_name (param_type param_name) {\
  MACRO_CONCAT(___fun_node, function_name)* current = function_name ## _head;\
  while(current) {\
    if ( compare_expression ) {\
      return current->f(param_name);\
    }\
    current = current->next;\
  }\
  return default_value;\
}\
dispatch_type function_name ## _dispatch_fn (param_type param_name)

#define implmulti(return_type, function_name, default_value, dispatch_type, param_type, param_name)\
_implmulti(return_type, function_name, default_value, dispatch_type, param_type, param_name, \
  function_name ## _dispatch_fn (param_name) == current->dispatch_value)

#define implmulti_cmp(return_type, function_name, compare_fn, default_value, dispatch_type, param_type, param_name)\
_implmulti(return_type, function_name, default_value, dispatch_type, param_type, param_name, \
  compare_fn(function_name ## _dispatch_fn (param_name) , current->dispatch_value))

#define __multimethod(return_type, function_name, value, param_type, param_name, counter)\
static return_type MACRO_CONCAT(function_name,counter) (param_type param_name); \
static void __attribute__((constructor)) MACRO_CONCAT (__construct_, MACRO_CONCAT(function_name,counter)) (void) {\
  if (! function_name ## _head) { \
    function_name ## _head = (MACRO_CONCAT(___fun_node, function_name)*)malloc(sizeof(MACRO_CONCAT(___fun_node, function_name))); \
    function_name ## _head->f = MACRO_CONCAT(function_name,counter); \
    function_name ## _head->next = NULL; \
    function_name ## _head->dispatch_value = value;\
    function_name ## _tail = function_name ## _head; \
  } else { \
    function_name ## _tail->next = (MACRO_CONCAT(___fun_node, function_name)*)malloc(sizeof(MACRO_CONCAT(___fun_node, function_name))); \
    function_name ## _tail->next->f = MACRO_CONCAT(function_name,counter); \
    function_name ## _tail->next->next = NULL; \
    function_name ## _tail->next->dispatch_value = value;\
    function_name ## _tail = function_name ## _tail->next; \
  } \
  } \
  static return_type MACRO_CONCAT(function_name,counter) (param_type param_name)
  
#define multimethod(return_type, function_name, value, param_type, param_name)\
__multimethod(return_type, function_name, value, param_type, param_name, __COUNTER__)

#define free_multimethod(function_name)\
{\
  MACRO_CONCAT(___fun_node, function_name) *current = function_name ## _head; \
  while (current) { \
    MACRO_CONCAT(___fun_node, function_name) *temp = current; \
    current = current->next; \
    free(temp); \
  } \
}
