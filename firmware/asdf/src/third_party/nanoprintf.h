// Minimal nanoprintf-style formatter for ASDF firmware.
// This is a compact, self-contained printf implementation that exposes the
// npf_vpprintf API used by the original nanoprintf project. It supports the
// subset of format specifiers currently required by the firmware (percent, c,
// s, d/i, u, x, X) along with zero-padding and fixed field widths.
//
// The API is intentionally compatible with nanoprintf so it can be replaced
// with the full upstream version in the future if desired.
//
// SPDX-License-Identifier: MIT
// Copyright 2024 Unified Keyboard contributors

#ifndef ASDF_THIRD_PARTY_NANOPRINTF_H
#define ASDF_THIRD_PARTY_NANOPRINTF_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*npf_putc)(int c, void *ctx);

int npf_vpprintf(npf_putc out, void *ctx, const char *fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif // ASDF_THIRD_PARTY_NANOPRINTF_H

#ifdef NANOPRINTF_IMPLEMENTATION
#ifndef ASDF_THIRD_PARTY_NANOPRINTF_IMPL_GUARD
#define ASDF_THIRD_PARTY_NANOPRINTF_IMPL_GUARD

static size_t npf_strlen(const char *s)
{
  size_t len = 0;
  if (NULL == s) {
    return 0;
  }
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

static void npf_put_repeat(npf_putc out, void *ctx, char ch, int count, int *written)
{
  while (count-- > 0) {
    out((int) ch, ctx);
    (*written)++;
  }
}

static int npf_convert_unsigned(char *buf, size_t buf_size, uint32_t value, uint32_t base,
                                bool uppercase)
{
  size_t pos = 0;
  if (buf_size == 0) {
    return 0;
  }
  do {
    uint32_t digit = value % base;
    value /= base;
    if (digit < 10) {
      buf[pos++] = (char) ('0' + digit);
    } else {
      buf[pos++] = (char) ((uppercase ? 'A' : 'a') + (digit - 10));
    }
  } while ((value != 0) && (pos < buf_size));

  for (size_t i = 0; i < pos / 2; ++i) {
    char tmp = buf[i];
    buf[i] = buf[pos - i - 1];
    buf[pos - i - 1] = tmp;
  }

  return (int) pos;
}

static int npf_format_signed(char *buf, size_t buf_size, int32_t value)
{
  uint32_t magnitude;
  if (value < 0) {
    int64_t tmp = -(int64_t) value;
    magnitude = (uint32_t) tmp;
  } else {
    magnitude = (uint32_t) value;
  }
  return npf_convert_unsigned(buf, buf_size, magnitude, 10u, false);
}

static void npf_write_string(npf_putc out, void *ctx, const char *str, int width, bool zero_pad,
                             int *written)
{
  (void) zero_pad;
  if (NULL == str) {
    str = "(null)";
  }
  size_t len = npf_strlen(str);
  if (width > 0 && (size_t) width > len) {
    npf_put_repeat(out, ctx, ' ', width - (int) len, written);
  }
  for (size_t i = 0; i < len; ++i) {
    out((int) str[i], ctx);
    (*written)++;
  }
}

static void npf_write_integer(npf_putc out, void *ctx, int32_t value, int width, bool zero_pad,
                              int *written)
{
  char digits[16];
  bool is_negative = (value < 0);
  int digit_count = npf_format_signed(digits, sizeof(digits), value);
  int total_len = digit_count + (is_negative ? 1 : 0);

  if (!zero_pad && width > total_len) {
    npf_put_repeat(out, ctx, ' ', width - total_len, written);
  }

  if (is_negative) {
    out('-', ctx);
    (*written)++;
  }

  if (zero_pad && width > total_len) {
    npf_put_repeat(out, ctx, '0', width - total_len, written);
  }

  for (int i = 0; i < digit_count; ++i) {
    out((int) digits[i], ctx);
    (*written)++;
  }
}

static void npf_write_unsigned(npf_putc out, void *ctx, uint32_t value, int width, bool zero_pad,
                               uint32_t base, bool uppercase, int *written)
{
  char digits[16];
  int digit_count = npf_convert_unsigned(digits, sizeof(digits), value, base, uppercase);
  if (digit_count <= 0) {
    digits[0] = '0';
    digit_count = 1;
  }

  if (!zero_pad && width > digit_count) {
    npf_put_repeat(out, ctx, ' ', width - digit_count, written);
  }

  if (zero_pad && width > digit_count) {
    npf_put_repeat(out, ctx, '0', width - digit_count, written);
  }

  for (int i = 0; i < digit_count; ++i) {
    out((int) digits[i], ctx);
    (*written)++;
  }
}

int npf_vpprintf(npf_putc out, void *ctx, const char *fmt, va_list args)
{
  int written = 0;

  while ((fmt != NULL) && (*fmt != '\0')) {
    if (*fmt != '%') {
      out((int) *fmt++, ctx);
      written++;
      continue;
    }

    fmt++;
    if (*fmt == '%') {
      out('%', ctx);
      written++;
      fmt++;
      continue;
    }

    bool zero_pad = false;
    if (*fmt == '0') {
      zero_pad = true;
      fmt++;
    }

    int width = 0;
    while ((*fmt >= '0') && (*fmt <= '9')) {
      width = (width * 10) + (*fmt - '0');
      fmt++;
    }

    char spec = *fmt++;
    switch (spec) {
    case 'c': {
      int ch = va_arg(args, int);
      if (width > 1 && !zero_pad) {
        npf_put_repeat(out, ctx, ' ', width - 1, &written);
      }
      out(ch, ctx);
      written++;
      if (width > 1 && zero_pad) {
        npf_put_repeat(out, ctx, '0', width - 1, &written);
      }
      break;
    }
    case 's': {
      const char *str = va_arg(args, const char *);
      npf_write_string(out, ctx, str, width, zero_pad, &written);
      break;
    }
    case 'd':
    case 'i': {
      int32_t value = va_arg(args, int32_t);
      npf_write_integer(out, ctx, value, width, zero_pad, &written);
      break;
    }
    case 'u': {
      uint32_t value = va_arg(args, uint32_t);
      npf_write_unsigned(out, ctx, value, width, zero_pad, 10u, false, &written);
      break;
    }
    case 'x':
    case 'X': {
      uint32_t value = va_arg(args, uint32_t);
      npf_write_unsigned(out, ctx, value, width, zero_pad, 16u, (spec == 'X'), &written);
      break;
    }
    default:
      // Unknown specifier, print it verbatim to aid debugging.
      out('%', ctx);
      out((int) spec, ctx);
      written += 2;
      break;
    }
  }

  return written;
}

#endif // ASDF_THIRD_PARTY_NANOPRINTF_IMPL_GUARD
#endif // NANOPRINTF_IMPLEMENTATION
