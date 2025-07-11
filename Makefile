CXXFLAGS  := -L./lib -l:libraylib.a -lopengl32 -lgdi32 -lwinmm -O2
#-mwindows

all: game.exe run
	
renderer.o: src/renderer.cpp
	g++ -c src/renderer.cpp

editor.o:  src/editor.cpp
	g++ -c src/editor.cpp

main.o: src/main.cpp
	g++ -c src/main.cpp

game.exe: main.o  renderer.o editor.o
	g++ *.o -o game $(CXXFLAGS)

run:
	./game
