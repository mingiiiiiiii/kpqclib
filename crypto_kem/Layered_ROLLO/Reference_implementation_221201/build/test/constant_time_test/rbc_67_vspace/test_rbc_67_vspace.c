/*
 * Constant-time test
 */

#include <stdlib.h>
#include <stdio.h>
#include "rbc.h"
#include "poison.h"

// #define VERBOSE 1


/*
 * Variables
 */
int INSTANCES = 10;

#define ADIM 5
#define BDIM 5

rbc_67_vspace a;
rbc_67_vspace b;
rbc_67_vspace product;
rbc_67_vspace inter;
rbc_67_vspace invProd[ADIM];



/*
 * Initialization and destruction
 */
void test_setup() {
  // Initialization
  rbc_67_field_init();
  rbc_67_vspace_init(&a, ADIM);
  rbc_67_vspace_init(&b, BDIM);
  rbc_67_vspace_init(&product, ADIM * BDIM);
  rbc_67_vspace_init(&inter, ADIM * BDIM);
  for(int i = 0 ; i < ADIM ; i++) rbc_67_vspace_init(&invProd[i], ADIM * BDIM);
}

//void test_teardown() {};
void clear(){
  unpoison(a,sizeof(a));
  unpoison(b,sizeof(b));
  unpoison(product,sizeof(product));
  unpoison(inter,sizeof(inter));
  unpoison(invProd,sizeof(invProd));

  rbc_67_vspace_clear(a);
  rbc_67_vspace_clear(b);
  rbc_67_vspace_clear(product);
  rbc_67_vspace_clear(inter);
  for(int i = 0 ; i < ADIM ; i++) rbc_67_vspace_clear(invProd[i]);

}



/*
 * Test functions
 */
void test_cst_time_vspace(){
  //Get random vector space for A and B
  random_source prng;
  random_init(&prng, RANDOM_SOURCE_PRNG);

  rbc_67_vspace_set_random_full_rank(&prng, a, ADIM);
  rbc_67_vspace_set_random_full_rank(&prng, b, BDIM);

  // Compute product vector space
  rbc_67_vspace_product(product, a, b, ADIM, BDIM); 

  // Compute A[i]^-1 * product
  rbc_67_elt inverse;

  for(int i = 0 ; i < ADIM ; i++) {
    rbc_67_elt_inv(inverse, a[i]);
    rbc_67_vec_scalar_mul(invProd[i], product, inverse, ADIM*BDIM);
  }

  unsigned int interDim = 0;
  poison(inter,sizeof(inter));
  poison(invProd,sizeof(invProd));

  // Intersect every invProd. The resulting intersection should be at least of dimension BDIM (equal with high probability if m is high enough)
  interDim = rbc_67_vspace_intersection(inter, invProd[0], invProd[1], ADIM * BDIM, ADIM * BDIM);
  for(int i = 2 ; i < ADIM ; i++) {
    interDim = rbc_67_vspace_intersection(inter, inter, invProd[i], interDim, ADIM * BDIM);
  }
}



/*
 * Test execution*/
int main(){
  for(int i = 0 ; i < INSTANCES ; ++i) {
    test_setup();
    test_cst_time_vspace();
    clear();
  }
}