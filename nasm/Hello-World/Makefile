NASM = nasm
ASMFLAGS = -f bin

SOURCE = hello-world.asm
BINARY = hello-world.com

$(BINARY): $(SOURCE)
	$(NASM) $(ASMFLAGS) $< -o $(BINARY)
