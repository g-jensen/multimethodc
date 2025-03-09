#include "../headers/multimethod.h"

struct hi {
  int a;
  int b;
};

defmulti(int, a_method, int, struct hi, a);
defmulti(struct hi, other_method, struct hi, int, a);

typedef enum Animal {
  Dog,
  Cat,
  Bird,
  Cow
} Animal;

defmulti(char*, get_noise, Animal, Animal, animal);