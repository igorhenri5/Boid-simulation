all:  build_util build_entities build_simulation build_main link run
linux: build_util build_entities build_simulation build_main link_alt

.PHONY: all

run: 
	./main.out

link:
	g++ -std=c++11 -I"glm" -o main.out *.o -L"freeglut\lib" -lfreeglut -lopengl32 -lglu32
	# g++ -o main.out *.o -L"freeglut\lib" -lfreeglut -lopengl32 -lglu32


link_alt:
	g++ -o main.out *.o -L"freeglut\lib" -lglut -lGL -lGLU 

build_main:
	g++ -c main.cpp -I"freeglut\include" -I"glm"

build_simulation:
	g++ -c simulation/*.cpp -I"freeglut\include" -I"glm"

build_entities:
	g++ -c entities/*.cpp -I"freeglut\include" -I"glm"

build_util:
	g++ -c util/*.cpp -I"freeglut\include" -I"glm"

# clean:
# 	rm -f *.o *.exe
