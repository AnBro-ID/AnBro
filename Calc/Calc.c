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

number* max_len(number *a, number *b)
{
	return a->len >= b->len ? a : b;
}

number* min_len(number *a, number *b)
{
	return a->len < b->len ? a : b;
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
	number *c = max_len(a, b);
	b = min_len(a, b);
	
	int minLen = b->len;
	int carry = 0;

	for (int i = 0; i < minLen || carry; ++i)
	{
	    if (i > c->len - 1)
	    {
	      c->len++;
		  c->num = (int*)realloc(c->num, c->len * sizeof(int));
		  c->num[c->len - 1] = 0;
        }		
        
		c->num[i] += (i < minLen ? b->num[i] : 0) + carry;
		carry = c->num[i] / base;
		c->num[i] %= base;		
	}
	
	return c;
}

void print(number *n)
{
	if (n->sign == '-') printf("-");

	for (int i = n->len - 1; i >= 0; --i)
		printf("%d", n->num[i]);
}

number* maxOf(number *a, number *b)
{
	if (a->len > b->len) return a;
	else if (a->len < b->len) return b;
	else
	for (int i = a->len - 1; i >= 0; --i)
	{
		if (a->num[i] > b->num[i]) return a;
		else if (a->num[i] < b->num[i]) return b;
	}

	return a;
}

int main()
{
    number *a, *b, *c;
    
    a = init();
    b = init();
    
    c = sum(a, b);
    print(c);    

	getchar();getchar();
    return 0;
}
