SRC_DIR = src
IDIR = include
LDIR = lib
ODIR = obj
CC = g++
CFLAGS = -I$(IDIR) -std=c++17 -g -O2 -Wall -Wextra -DLOCAL

_HEADERS =
HEADERS = $(patsubst %,$(SRC_DIR)/%,$(_HEADERS))

_OBJ = glad.o Main.o Window.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ifeq ($(OS),Windows_NT)
	LIBS = -lglfw3 -lopengl32 -lgdi32
	PRE =
	SUF = .exe
else
	LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	PRE = ./
	SUF = .out
endif

$(ODIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@$(SUF) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

run:
	$(PRE)main$(SUF)

clean:
ifeq ($(OS),Windows_NT)
	del /S /Q *.o
else
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
endif