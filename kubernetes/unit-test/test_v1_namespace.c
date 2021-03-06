#ifndef v1_namespace_TEST
#define v1_namespace_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define v1_namespace_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/v1_namespace.h"
v1_namespace_t* instantiate_v1_namespace(int include_optional);

#include "test_v1_object_meta.c"
#include "test_v1_namespace_spec.c"
#include "test_v1_namespace_status.c"


v1_namespace_t* instantiate_v1_namespace(int include_optional) {
  v1_namespace_t* v1_namespace = NULL;
  if (include_optional) {
    v1_namespace = v1_namespace_create(
      "0",
      "0",
       // false, not to have infinite recursion
      instantiate_v1_object_meta(0),
       // false, not to have infinite recursion
      instantiate_v1_namespace_spec(0),
       // false, not to have infinite recursion
      instantiate_v1_namespace_status(0)
    );
  } else {
    v1_namespace = v1_namespace_create(
      "0",
      "0",
      NULL,
      NULL,
      NULL
    );
  }

  return v1_namespace;
}


#ifdef v1_namespace_MAIN

void test_v1_namespace(int include_optional) {
    v1_namespace_t* v1_namespace_1 = instantiate_v1_namespace(include_optional);

	cJSON* jsonv1_namespace_1 = v1_namespace_convertToJSON(v1_namespace_1);
	printf("v1_namespace :\n%s\n", cJSON_Print(jsonv1_namespace_1));
	v1_namespace_t* v1_namespace_2 = v1_namespace_parseFromJSON(jsonv1_namespace_1);
	cJSON* jsonv1_namespace_2 = v1_namespace_convertToJSON(v1_namespace_2);
	printf("repeating v1_namespace:\n%s\n", cJSON_Print(jsonv1_namespace_2));
}

int main() {
  test_v1_namespace(1);
  test_v1_namespace(0);

  printf("Hello world \n");
  return 0;
}

#endif // v1_namespace_MAIN
#endif // v1_namespace_TEST
