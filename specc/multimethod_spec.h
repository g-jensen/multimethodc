#include "../headers/multimethod.h"

struct hi {
  int a;
  int b;
};

defmulti(int, a_method, struct hi, a);
defmulti(struct hi, other_method, int, a);