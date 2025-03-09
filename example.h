#include <stdio.h>

#include "headers/multimethod.h"

typedef enum Animal {
  Dog,
  Cat,
  Bird,
  Cow
} Animal;

defmulti(char*, get_noise, Animal, Animal, animal);