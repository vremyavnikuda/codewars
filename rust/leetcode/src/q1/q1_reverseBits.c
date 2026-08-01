#include <stdint.h>

static inline uint32_t remix(uint32_t x, uint32_t mask, unsigned shift) {
  return ((x >> shift) & mask) | ((x & mask) << shift);
}

static inline uint32_t core(uint32_t n) {
  n = remix(n, 0x55555555u, 1);
  n = remix(n, 0x33333333u, 2);
  n = remix(n, 0x0f0f0f0fu, 4);
  n = remix(n, 0x00ff00ffu, 8);
  return (n >> 16) | (n << 16);
}

int reverseBits(int n) { return (int)core((uint32_t)n); }
