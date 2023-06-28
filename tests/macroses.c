#define ADD_TEST(suite, test)                          \
    {                                                  \
        if ((NULL == CU_add_test(suite, #test, test))) \
        {                                              \
            CU_cleanup_registry();                     \
            return CU_get_error();                     \
        }                                              \
    }

#define ADD_SUITE(suite, suite_name)                               \
    {                                                              \
        suite = CU_add_suite(suite_name, init_suite, clean_suite); \
        if (NULL == suite)                                         \
        {                                                          \
            CU_cleanup_registry();                                 \
            return CU_get_error();                                 \
        }                                                          \
    }
