
# Compilers
CC = gcc
CXX = g++

# Compilers flags
CFLAGS = -std=c11 -Wall -ggdb 
CXXFLAGS = -std=c++11 -Wall -ggdb 


# DEBUG = RELEASE
DEBUG = DEBUG

CXX_SRCS = ./ask1/src/58633_11.cpp \
		   ./ask1/src/polygon.cpp

LIB_SRCS = ./lib/dbg_assert.c \
		   ./lib/shader_utl.c \
		   ./lib/windowGlfw.c \
		   ./lib/vertexArray/vao.c \
		   ./lib/vertexArray/vbo.c \
		   ./lib/vertexArray/vbLayout.c

IMGUI_DIR = ./imgui
IMGUI_SRCS = ./$(IMGUI_DIR)/imgui.cpp \
			 ./$(IMGUI_DIR)/imgui_demo.cpp \
			 ./$(IMGUI_DIR)/imgui_draw.cpp \
			 ./$(IMGUI_DIR)/imgui_tables.cpp \
			 ./$(IMGUI_DIR)/imgui_widgets.cpp \
			 ./$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
			 ./$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

CXX_OBJS = $(CXX_SRCS:.cpp=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)
IMGUI_OBJS = $(IMGUI_SRCS:.cpp=.o)

INCLUDES = -I/usr/include -I. -I$(IMGUI_DIR)

LIB_DIRS = -L/usr/lib

LD_FLAGS = $(LIB_DIRS) -lglfw -lrt -lm -ldl -lGLEW -lGL -lXrandr -lXi -lX11

CXXFLAGS += $(INCLUDES) $(LD_FLAGS) -D$(DEBUG)
CFLAGS += $(INCLUDES) $(LD_FLAGS) -D$(DEBUG)


ASK1_TARGET = ASK1_TARGET
ASK2_TARGET = ASK2_TARGET

##---------------
## BUILD RULES
##---------------

ask1T: $(ASK1_TARGET)

$(ASK1_TARGET): $(CXX_OBJS) $(LIB_OBJS) $(IMGUI_OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@


.PHONY: clean cleanImgui exec1
exec1:
	./$(ASK1_TARGET)

clean:
	rm $(ASK1_TARGET_TARGET) $(LIB_OBJS) $(CXX_OBJS) imgui.ini

cleanImgui:
	rm $(IMGUI_OBJS)
