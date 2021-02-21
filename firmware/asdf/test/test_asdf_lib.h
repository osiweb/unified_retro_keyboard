#if !defined(TEST_ASDF_LIB_H)
#define TEST_ASDF_LIB_H

#define TEST_HOOK_VAL1 1
#define TEST_HOOK_VAL2 2
#define TEST_HOOK_VAL3 4
#define TEST_HOOK_VAL4 8
#define TEST_HOOK_VAL5 16

uint32_t max(uint8_t first, uint8_t second);
void test_hook_clear(void);
uint32_t test_hook_readback(void);
void test_hook_1(void);
void test_hook_2(void);
void test_hook_3(void);
void test_hook_4(void);
void test_hook_5(void);
void test_hook_each_scan(void);
uint8_t test_hook_read_row(uint8_t val);
void test_hook_output(uint8_t val);


#endif // if !defined(TEST_ASDF_LIB_H)
