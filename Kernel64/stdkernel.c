void print(char *str, char line, char column, unsigned char color){
	unsigned char *videoMem = (unsigned char*)(0xB8000 + (80 * 2 * line) + (column * 2));
	
	for(int i = 0; str[i] != 0; i++){
		*videoMem++ = str[i];
		*videoMem++ = color;		
	}
}

