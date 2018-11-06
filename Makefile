
all: lab1 

lab1 : main.cpp 
	g++ main.cpp -Wall -Wextra -o lab1 

clean:
	rm -f lab1 

