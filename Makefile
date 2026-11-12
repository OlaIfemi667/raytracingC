CFLAGS = -Wall -Wextra

main:
	clang  -o main	main.c src/*c  -lm $(CFLAGS)

clean:
	rm main 
