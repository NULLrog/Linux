// Copyleft (ↄ) 2017 Marinkevich Sergey (G-Ray_Hook). All lefts reserved.
// Contact: s@marinkevich.ru
// =============================================================================
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int arr[] = {1, 2, 3, 4, 5};
  int a = arr[0] + // 1 +
          1[arr] + // 2 +
          0[arr + 2] + // 3 +
          (13 + arr)[-10] + // 4 +
          (0[arr] + arr)[2[arr]]; // 5
  printf("%d\n", a); // = 15
}
// arr[i] => *(arr + i) = *(i + arr)
// i[arr] => *(i + arr) = *(arr + i)
