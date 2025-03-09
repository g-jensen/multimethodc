#include "src/specc.h"
#include "multimethod_spec.h"

#define should_hi_eq(expected,actual)\
  if (expected.a != actual.a || expected.b != actual.b) {\
    specc_fail_message("e: %d, %d, a: %d, %d",expected.a,expected.b,actual.a,actual.b);\
  }

int identity(int a) {
  return a;
}

int compare_fn(struct hi a, struct hi b) {
  return a.a == b.a && a.b == b.b;
}

implmulti(int, a_method, 0, struct hi, a) {
  return a.a+1;
};

multimethod(int, a_method, 0, struct hi, a) {
  return 512;
}

multimethod(int, a_method, 2, struct hi, a) {
  return 314;
}

multimethod(int, a_method, 3, struct hi, a) {
  return 218;
}

struct hi default_hi = (struct hi){.a=0,.b=0};
implmulti_cmp(struct hi, other_method, compare_fn, default_hi, int, a) {
  return (struct hi){.a=a,.b=0};
};

struct hi negative_hi  = (struct hi){.a=-1,.b=0};
multimethod(struct hi, other_method, negative_hi, int, a) {
  return (struct hi){.a=1,.b=1};
}

struct hi positive_hi  = (struct hi){.a=1,.b=0};
multimethod(struct hi, other_method, positive_hi, int, a) {
  return (struct hi){.a=-1,.b=-1};
}

module(multimethod_spec, {  
  describe("multimethod functionality", {
    struct hi the = {.a=0,.b=0};

    it("calls an unimplemented method", {
      should_eq(0,a_method(the),int);
    });

    it("calls an implemented method", {
      the = (struct hi){.a=-1,.b=0};
      should_eq(512,a_method(the),int);
    });

    it("calls a second implemented method", {
      the = (struct hi){.a=1,.b=0};
      should_eq(314,a_method(the),int);
    });

    it("calls a third implemented method", {
      the = (struct hi){.a=2,.b=0};
      should_eq(218,a_method(the),int);
    });

    it("calls an unimplemented method of second multimethod", {
      should_hi_eq(default_hi,other_method(512));
    });

    it("calls an implemented method of second multimethod", {
      the = (struct hi){.a=1,.b=1};
      should_hi_eq(the,other_method(-1));
    });

    it("calls a second implemented method of second multimethod", {
      the = (struct hi){.a=-1,.b=-1};
      should_hi_eq(the,other_method(1));
    });
  });
});