#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "add: entering function\n");
  }


  // Fill the function, the goal is to compute lhs + rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result

  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  int lhs_len = strlen(lhs);
  int rhs_len = strlen(rhs);
  int max_len = lhs_len > rhs_len ? lhs_len : rhs_len;

  char *result = (char *)malloc(max_len + 2); // +1 for possible carry, +1 for '\0'
  if (!result) {
    debug_abort("Memory allocation failed");
    return NULL;
  }

  int carry = 0;
  int result_pos = 0;
  for (int i = 0; i < max_len || carry; i++) {
    int lhs_digit = i < lhs_len ? get_digit_value(lhs[lhs_len - 1 - i]) : 0;
    int rhs_digit = i < rhs_len ? get_digit_value(rhs[rhs_len - 1 - i]) : 0;

    int sum = lhs_digit + rhs_digit + carry;
    result[result_pos++] = to_digit(sum % base);
    carry = sum / base;
  }

  result[result_pos] = '\0';
  reverse(result);

  return result;
}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "sub: entering function\n");
  }


  // Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result

  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  int lhs_len = strlen(lhs);
  int rhs_len = strlen(rhs);

  char *result = (char *)malloc(lhs_len + 1);
  if (!result) {
    debug_abort("Memory allocation failed");
    return NULL;
  }

  int borrow = 0;
  int result_pos = 0;
  for (int i = 0; i < lhs_len; i++) {
    int lhs_digit = get_digit_value(lhs[lhs_len - 1 - i]);
    int rhs_digit = i < rhs_len ? get_digit_value(rhs[rhs_len - 1 - i]) : 0;

    int diff = lhs_digit - rhs_digit - borrow;
    if (diff < 0) {
      diff += base;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result[result_pos++] = to_digit(diff);
  }

  result[result_pos] = '\0';
  reverse(result);

  char *final_result = strdup(drop_leading_zeros(result));
  free(result);

  return final_result;
}


char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
  if (VERBOSE) {
    fprintf(stderr, "mul: entering function\n");
  }

  lhs = drop_leading_zeros(lhs);
  rhs = drop_leading_zeros(rhs);

  int lhs_len = strlen(lhs);
  int rhs_len = strlen(rhs);

  char *result = (char *)calloc(lhs_len + rhs_len + 1, sizeof(char));
  if (!result) {
    debug_abort("Memory allocation failed");
    return NULL;
  }

  for (int i = 0; i < lhs_len; i++) {
    int lhs_digit = get_digit_value(lhs[lhs_len - 1 - i]);
    int carry = 0;

    for (int j = 0; j < rhs_len || carry; j++) {
      int rhs_digit = j < rhs_len ? get_digit_value(rhs[rhs_len - 1 - j]) : 0;
      int current = carry + get_digit_value(result[i + j]) + lhs_digit * rhs_digit;

      result[i + j] = to_digit(current % base);
      carry = current / base;
    }
  }

  reverse(result);

  return drop_leading_zeros(result);
}



// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to a digit from get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value];
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}
