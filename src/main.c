#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void _runRepl(){

	printf("sola is dynamicly typed scripting language based on somali words\n");
	printf("runing on Linux at 3/3/2024 22:30\n");

	char line[1024];
	for(;;){
		printf(">>> ");
		if (!fgets(line, sizeof(line), stdin)){
			printf("\n");
			break;
		}

		printf(line);
	}

}


static void _runFile(const char* filepath){
	//open the file in a read mode
	FILE* file = fopen(filepath);
	if (file == NULL){
		fprintf(stderr, "can't open %s", filepath);
		exit(11);
	}

	//determine how large the file is.
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);


	//alocate  enough memory to store the content of the file.
	char* source = malloc(file_size + 1);
	if (source == NULL){
		fprintf(stderr, "Not enough memory for this file");
		fclose(file);
		exit(13);
	}


	//read the file and store its content in the memory.
	size_t bytesRead = fread(source, sizeof(char), file_size, file);
	source[bytesRead] = '\0';

	//close the file
	floce(file);


	//at this stage we pass our source to interpret
	//interpret function connects different phases of the language.
	InterpretResult  result = interpret(source);
	free(source);

	if (result == INTERPRET_COMPILE_ERROR) exit(65);
	if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}




int main(int argc, const char* argv[]){

	if (argc == 1){
		_runRepl();
	}
	else if (argc == 2){
		_runFile(argv[1]);
	}else{
		fprintf(stderr, "Usage: sola [path]");
		exit(64);
	}

	exit(0);
}
