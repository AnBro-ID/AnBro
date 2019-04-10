#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int base = 10;
const int buff = 100;

typedef struct number
{
	char sign;  
	int *num;
	int len;
} number;

int max(int a, int b)
{
	return a > b ? a : b;
}

number* init()
{
    char input[buff];
    number *a;
    int i = 0;
  
    scanf("%s", input);
    
    a = (number*)malloc(sizeof(number));
    
    a->len = strlen(input);
    
    if (input[0] == '-')
    {
		a->len--;
		a->sign = '-';
		i++;
    }
    else a->sign = '+';
    
    a->num = (int*)malloc(a->len * sizeof(int));
    
    for (int j = a->len - 1; j >= 0; ++i, j--)
		a->num[j] = input[i] - '0';
    
    return a;
}

number* sum(number *a, number *b)
{
	number* c;

	c = (number*)malloc(sizeof(number));

	c->len = 2;
	c->sign = '+';
	c->num = (int*)malloc(c->len * sizeof(int));

	for (int i = 0; i < max(a->len, b->len); ++i)
	{
		if (i > c->len - 1)
		{
			c->len += max(a->len, b->len) - 1;
			c->num = (int*)realloc(c->num, c->len * sizeof(int));
		}
		
		c->num[i] += a->num[i] + b->num[i];
		c->num[i + 1] = c->num[i] / base;
		c->num[i] %= base;
	}

	if (c->num[c->len - 1] == 0) c->len--;

	return c;
}

void print(number *n)
{
	if (n->sign == '-') printf("-");

	for (int i = n->len - 1; i >= 0; --i)
		printf("%d", n->num[i]);
}

int main()
{
    number *a, *b, *c;
    
    a = init();
    b = init();
    
    c = sum(a, b);
    print(c);    

    return 0;
}