#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char randomChar = ' ' + rand() % 94;
	return randomChar;
}

char* inputString()
{
	char* randomString = malloc(5);
	char vowel[5] = { 'a', 'e', 'i', 'o', 'u' };
	char con[21] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };

	int randChar;
	randChar = rand() % 5;
	randomString[1] = vowel[randChar];
	randChar = rand() % 5;
	randomString[3] = vowel[randChar];

	randChar = (rand() % 19);
	randomString[0] = con[randChar];
	randomString[2] = con[randChar + 1];
	randomString[4] = con[randChar + 2];
	return randomString;
}

void testme()
{
	int tcCount = 0;
	char* s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' ' && state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}


int main(int argc, char* argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
