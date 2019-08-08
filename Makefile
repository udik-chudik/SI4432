UNITY_ROOT=test/unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -g

INC_DIRS=-Isrc -I$(UNITY_ROOT) -Itest -Iinc

SRC_FILES1=$(UNITY_ROOT)/unity.c src/si4432.c src/si4432_io_hal.c test/test_si4432.c test/test_runners/si4432_test_runner.c test/io_fake.c test/hal_fake.c test/test_si4432_io_hal.c test/test_runners/test_si4432_io_hal_runner.c
TEST_TARGET1=test1
TEST_TARGET2=test2

objects: $(SRC_FILES1)
	gcc $(CFLAGS) $(INC_DIRS) -c $(SRC_FILES1)
	mv *.o build/

default: objects
	gcc build/si4432_test_runner.o build/test_si4432.o build/unity.o build/si4432.o build/io_fake.o -o build/$(TEST_TARGET1)
	gcc build/test_si4432_io_hal_runner.o build/test_si4432_io_hal.o build/unity.o build/hal_fake.o build/si4432_io_hal.o -o build/$(TEST_TARGET2)

test/test_runners/si4432_test_runner.c: test/test_si4432.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_si4432.c test/test_runners/si4432_test_runner.c

test/test_runners/test_si4432_io_hal_runner.c: test/test_si4432_io_hal.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_si4432_io_hal.c test/test_runners/test_si4432_io_hal_runner.c

test: default
	build/${TEST_TARGET2}
	build/${TEST_TARGET1}
	

clean:
	rm -rf build/*