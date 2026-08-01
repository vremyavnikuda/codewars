int minOperations(char *s) {
  int a = 0, b = 0, t = 0;
  for (; *s; ++s, t ^= 1)
    a += ((*s ^ 48) ^ t), ++b;
  b -= a;
  return b ^ ((a ^ b) & -(a < b));
}
