int minFlips(char *s) {
  int a = 0, b = 0, c = 0, d, e;
  for (; s[a]; ++a)
    b += ((s[a] ^ 48) != (a & 1));
  c = b ^ (((a - b) ^ b) & -((a - b) < b));
  for (d = 0; d < a; ++d) {
    b += ((s[d] ^ 48) != ((d + a) & 1)) - ((s[d] ^ 48) != (d & 1));
    e = b ^ (((a - b) ^ b) & -((a - b) < b));
    c ^= (e ^ c) & -(e < c);
  }
  return c;
}
