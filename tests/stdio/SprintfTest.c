#include "unity_fixture.h"
#include <stdio.h>
#include <memory.h>

TEST_GROUP(sprintf);

TEST_SETUP(sprintf)
{
}

TEST_TEAR_DOWN(sprintf)
{
}

TEST(sprintf, NoFormatOperations)
{
	char output[5];
	memset(output, 0xaa, sizeof(output));
	
	TEST_ASSERT_EQUAL(3, sprintf(output, "hey"));
	TEST_ASSERT_EQUAL_STRING("hey", output);
	TEST_ASSERT_BYTES_EQUAL(0xaa, output[4]);
}

TEST(sprintf, InsertString)
{
	char output[20] = "";
	memset(output, 0xaa, sizeof(output));
	
	TEST_ASSERT_EQUAL(12, sprintf(output, "Hello %s\n", "World"));
	TEST_ASSERT_EQUAL_STRING("Hello World\n", output);
	TEST_ASSERT_BYTES_EQUAL(0xaa, output[13]);
}
