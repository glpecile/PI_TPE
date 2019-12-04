COMPILER=gcc -Wall -pedantic -std=c99 -g -fsanitize=address
OUTPUT_FILE=TPFinal
CREATED_FILES=query1.csv query2.csv query3.csv
FILES=main.c provinciasADT.c yearADT.c

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES)
clean:
	rm $(OUTPUT_FILE) $(CREATED_FILES)
