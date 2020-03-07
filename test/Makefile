CFLAGS = -Wall -g -O2 -std=c++0x
Target := test_set_insertion test_utf8_string pinyinization serialize

RM := @rm -rf
CC := g++

utf8_string_objs = utf8_string.o utf8_iterator.o

all: $(Target)

test_set_insertion: test_set_insertion.o
	$(CC) $(CFLAGS) $^ -o $@

test_utf8_string: test_utf8_string.o $(utf8_string_objs)
	$(CC) $(CFLAGS) $^ -o $@

pinyinization: pinyinization.o $(utf8_string_objs) 
	$(CC) $(CFLAGS) $^ -o $@

serialize: serialize.o $(utf8_string_objs)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	$(RM) *.o $(Target)

.PHONY: clean all
