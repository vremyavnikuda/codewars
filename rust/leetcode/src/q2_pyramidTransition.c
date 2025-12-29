#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_CACHE 50000

int d[7][7];

typedef struct {
  char key[32];
  bool val;
  bool used;
} CacheEntry;

CacheEntry cache[MAX_CACHE];

unsigned int hash(const char *str) {
  unsigned int h = 5381;
  int c;
  while ((c = *str++)) {
    h = ((h << 5) + h) + c;
  }
  return h % MAX_CACHE;
}

bool getCache(const char *key, bool *result) {
  unsigned int idx = hash(key);
  for (int i = 0; i < 100; i++) {
    unsigned int pos = (idx + i) % MAX_CACHE;
    if (!cache[pos].used) {
      return false;
    }
    if (strcmp(cache[pos].key, key) == 0) {
      *result = cache[pos].val;
      return true;
    }
  }
  return false;
}

void setCache(const char *key, bool val) {
  unsigned int idx = hash(key);
  for (int i = 0; i < 100; i++) {
    unsigned int pos = (idx + i) % MAX_CACHE;
    if (!cache[pos].used) {
      strcpy(cache[pos].key, key);
      cache[pos].val = val;
      cache[pos].used = true;
      return;
    }
    if (strcmp(cache[pos].key, key) == 0) {
      cache[pos].val = val;
      return;
    }
  }
}
bool dfs(char *s, char *t);
bool dfs(char *s, char *t) {
  int slen = strlen(s);
  int tlen = strlen(t);
  if (slen == 1) {
    return true;
  }
  if (tlen + 1 == slen) {
    return dfs(t, "");
  }
  char key[32];
  sprintf(key, "%s.%s", s, t);
  bool cached;
  if (getCache(key, &cached)) {
    return cached;
  }
  int a = s[tlen] - 'A';
  int b = s[tlen + 1] - 'A';
  int cs = d[a][b];
  for (int i = 0; i < 7; i++) {
    if ((cs >> i) & 1) {
      char newt[16];
      sprintf(newt, "%s%c", t, i + 'A');
      if (dfs(s, newt)) {
        setCache(key, true);
        return true;
      }
    }
  }
  setCache(key, false);
  return false;
}

bool pyramidTransition(char *bottom, char **allowed, int allowedSize) {
  memset(d, 0, sizeof(d));
  memset(cache, 0, sizeof(cache));
  for (int i = 0; i < allowedSize; i++) {
    int a = allowed[i][0] - 'A';
    int b = allowed[i][1] - 'A';
    int c = allowed[i][2] - 'A';
    d[a][b] |= 1 << c;
  }
  char empty[] = "";
  return dfs(bottom, empty);
}

int main() {
  char *a1[] = {"BCG", "CDE", "GEA", "FFF"};
  char *a2[] = {"AAA", "AAB", "ABA", "ABB", "BAC"};
  char *a3[] = {"DAD", "DAE", "DAB", "DAF", "DAC", "EAD", "EAE", "EAB",
                "EAF", "EAC", "BAD", "BAE", "BAB", "BAF", "BAC", "FAD",
                "FAE", "FAB", "FAF", "FAC", "CAD", "CAE", "CAB", "CAF",
                "CAC", "ADD", "ADE", "ADB", "ADF", "ADC", "AED", "AEE",
                "AEB", "AEF", "AEC", "ABD", "ABE", "ABB", "ABF", "ABC",
                "AFD", "AFE", "AFB", "AFF", "AFC", "ACD", "ACE", "ACB",
                "ACF", "ACC", "AAD", "AAE", "AAB", "AAF", "AAC", "AAA"};

  printf("Test 1: %d\n", pyramidTransition("BCD", a1, 4));
  printf("Test 2: %d\n", pyramidTransition("AABA", a2, 5));
  printf("Test 3: %d\n", pyramidTransition("DAAAAD", a3, 56));

  return 0;
}
