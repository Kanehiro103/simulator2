CC = gcc
FLAGS = -Wall
TARGET = test
SRCS = main.c library.c instruction.c register.c print.c alu.c grad_list.c fpu.c branch.c WB.c EX.c RF.c IF.c driver.c read.c error.c pseudo.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS): $(SRCS)
	$(CC) $(FLAGS) -c $(SRCS)

all: clean $(OBJS) $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)