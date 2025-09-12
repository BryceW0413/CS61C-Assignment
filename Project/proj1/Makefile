CC = clang
CFLAGS = -g -Wall -std=c99 -c
LDFLAGS = -g -Wall
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: PartA PartB

PartA: imageloader.o imageloadertester.o steganography.o
	$(CC) $(LDFLAGS) -o imageloadertester imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) -o steganography steganography.o imageloader.o

PartB: imageloader.o gameoflife.o
	$(CC) $(LDFLAGS) -o gameOfLife gameoflife.o imageloader.o

imageloader: imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) -o imageloadertester imageloader.o imageloadertester.o
	echo "Running imageloadertest"
	./imageloadertester testInputs/JohnConway.ppm > studentOutputs/JohnConway.ppm
	diff testInputs/JohnConway.ppm studentOutputs/JohnConway.ppm
	echo "Diff check: The above lines were different than expected. If no lines show up, then this passed"

imagememcheck: imageloaderasan

imageloaderasan: imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) $(ASANFLAGS) -o imageloadertester imageloader.o imageloadertester.o
	echo "Running ASan on imageloadertest"
	./imageloadertester testInputs/JohnConway.ppm > studentOutputs/JohnConway.ppm

steganography: imageloader.o steganography.o
	echo "Running steganography"
	$(CC) $(LDFLAGS) -o steganography steganography.o imageloader.o
	./steganography testInputs/JohnConway.ppm > studentOutputs/secretMessage.ppm

steganographymemcheck: steganographyasan

steganographyasan: imageloader.o steganography.o
	$(CC) $(LDFLAGS) $(ASANFLAGS) -o steganography steganography.o imageloader.o
	echo "Running ASan on steganography"
	./steganography testInputs/JohnConway.ppm > studentOutputs/secretMessage.ppm

gameoflife: imageloader.o gameoflife.o
	$(CC) $(LDFLAGS) -o gameOfLife gameoflife.o imageloader.o
	echo "Successfully compiled"
	echo "Run ./frames.csh for various tests"

gameoflifememcheck: gameoflifeasan

gameoflifeasan: imageloader.o gameoflife.o
	$(CC) $(LDFLAGS) $(ASANFLAGS) -o gameOfLife gameoflife.o imageloader.o
	echo "Running ASan on gameOfLife"
	./gameOfLife testInputs/JohnConway.ppm 0x1808 > studentOutputs/temp.ppm

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f gameOfLife
	rm -f steganography
	rm -f imageloadertester