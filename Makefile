CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -pedantic -Ifirmware
BUILD_DIR := build
TEST_BIN := $(BUILD_DIR)/i2c_tests

.PHONY: test clean

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): firmware/i2c_driver.c firmware/i2c_driver.h tests/test_i2c_driver.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) firmware/i2c_driver.c tests/test_i2c_driver.c -o $(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)
