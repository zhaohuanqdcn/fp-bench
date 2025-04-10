// Searches a sorted list using linear and binary search methods. 
//


#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

#define FLOAT_TYPE float

bool is_sorted(FLOAT_TYPE data[N]) {
  // Returns true iff array is NaN-free and sorted
  for(int i = 0; i < N; i++) {
    if(isnan(data[i])) {
      return false;
    }
    if(i > 0 && data[i] < data[i-1]) {
      return false;
    }
  }
  return true;
}

bool linear_search(FLOAT_TYPE data[N], FLOAT_TYPE elem) {
  for(int i = 1; i < N; i++) {
    if(data[i] == elem) {
      return true;
    }
  }
  return false;
}

bool binary_search(FLOAT_TYPE data[N], FLOAT_TYPE elem) {
  // Range under consideration is closed.
  // i.e. [lo, hi]
  int lo = 0;
  int hi = N - 1;
  while(lo <= hi) {
    int mid = (hi+lo) / 2;
    if(data[mid] == elem) {
      return true;
    }
    if(data[mid] > elem) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return false;
}

int main(int argc, char** argv) {

  FLOAT_TYPE data[N];
  FLOAT_TYPE elem;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  for (int i = 0; i < N; i++) {
    fscanf(file, "%f", &data[i]);
  }

  fscanf(file, "%f", &elem);

  fclose(file);

  if(!is_sorted(data)) {
    return 0;
  }

  if (linear_search(data, elem) != binary_search(data, elem)) {
    printf("BUG triggered\n");
    return 1;
  }

  return 0;

}
