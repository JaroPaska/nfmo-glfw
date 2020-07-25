SRC_DIR = src
IDIR = include
LDIR = lib
ODIR = obj
CC = g++
CFLAGS = -I$(IDIR) -std=c++17 -g

_HEADERS = Window.h Stage.h StageObject.h Get.h Shader.h Polygon.h Model.h CarModel.h Loader.h Renderer.h
HEADERS = $(patsubst %,$(SRC_DIR)/%,$(_HEADERS))

_OBJ = glad.o Main.o Window.o Stage.o StageObject.o Get.o Model.o CarModel.o Loader.o Renderer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ifeq ($(OS),Windows_NT)
	LIBS = -lglfw3 -lopengl32 -lgdi32
	PREm =
	SUF = .exe
else
	LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
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