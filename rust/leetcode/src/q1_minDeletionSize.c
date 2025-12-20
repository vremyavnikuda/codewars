int minDeletionSize(char **strs, int strsSize) {
  if (strsSize == 0)
    return 0;

  int n = 0;
  while (strs[0][n] != '\0')
    n++;

  int c = 0;

  for (int j = 0; j < n; j++) {
    for (int i = 1; i < strsSize; i++) {
      if (strs[i][j] < strs[i - 1][j]) {
        c++;
        break;
      }
    }
  }

  return c;
}
