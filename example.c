#include "example.h"

implmulti(char*, get_noise, "Unknown Animal", Animal, Animal, animal) {
  return animal;
};

multimethod(char*, get_noise, Dog, Animal, animal) {
  return "Bark";
}

multimethod(char*, get_noise, Cat, Animal, animal) {
  return "Meow";
}

multimethod(char*, get_noise, Bird, Animal, animal) {
  return "Chirp";
}

int main() {
  printf("%s!\n",get_noise(Dog));
  printf("%s!\n",get_noise(Cat));
  printf("%s!\n",get_noise(Bird));
  printf("%s!\n",get_noise(Cow));
  free_multimethod(get_noise); // freeing isn't necessary, but if you want to for some reason.
}