OUTPUT=out
MAIN=main.c

all: clean 
	gcc $(MAIN) -o $(OUTPUT) -Wall

run:
	./$(OUTPUT)

clean:
	rm -rf *.o out

teste1:
	./$(OUTPUT) < teste1.txt
teste2:
	./$(OUTPUT) < teste2.txt