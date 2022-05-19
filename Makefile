garbage: producer_consumer.c
	gcc -pthread -o garbage producer_consumer.c -W -Wall -pedantic

.PHONY: clean run

run:
	./garbage

clean:
	rm -rf garbage
