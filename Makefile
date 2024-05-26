
# Compilers
CC = gcc
CXX = g++

# Compilers flags
CFLAGS = -std=c11 -Wall -ggdb
CXXFLAGS = -std=c++11 -Wall -ggdb

TARGET = main

# DEBUG = RELEASE
DEBUG = DEBUG

CXX_SRCS = ./ask1/src/58633_11.cpp

C_SRCS = ./lib/dbg_assert.c \
		 ./lib/shader_utl.c \
		 ./lib/windowGlfw.c \
		 ./lib/vertexArray/vao.c \
		 ./lib/vertexArray/vbo.c \
		 ./lib/vertexArray/vbLayout.c

CXX_OBJS = $(CXX_SRCS:.cpp=.o)
C_OBJS = $(C_SRCS:.c=.o)

INCLUDES = -I/usr/include -I.

LIB_DIRS = -L/usr/lib

LD_FLAGS = $(LIB_DIRS) -lglfw -lrt -lm -ldl -lGLEW -lGL -lXrandr -lXi -lX11

CXXFLAGS += $(INCLUDES) $(LD_FLAGS) -D$(DEBUG)
CFLAGS += $(INCLUDES) $(LD_FLAGS) -D$(DEBUG)



all: $(TARGET)

$(TARGET): $(CXX_OBJS) $(C_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@


.PHONY: clean exec gitignore
exec:
	./$(TARGET)

clean:
	rm $(TARGET) $(C_OBJS) $(CXX_OBJS)

gitignore:
	@echo $(TARGET) >> .gitignore
	@echo $(C_OBJS) >> .gitignore
	@echo $(CXX_OBJS) >> .gitignore
