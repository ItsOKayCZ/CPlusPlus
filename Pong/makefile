main: main.o Window.o Player.o PlayerAI.o Ball.o
	g++ -o main main.o Window.o Player.o PlayerAI.o Ball.o -lsfml-graphics -lsfml-window -lsfml-system

%.o: Includes/%.cpp Headers/%.hpp
	g++ -c -o $@ $<

main.o: main.cpp
	g++ -c -o $@ $<

clean:
	rm *.o main