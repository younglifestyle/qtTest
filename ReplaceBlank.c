#include <stdio.h>

void replaceBlank(char string[], int length)
{
	if( string == NULL || length == 0 )
		return;
		
	int originLen = 0;
	int BlankLen = 0;
	
	while( string[i] != '\0' )
	{
		i++;		
		originLen++;
		
		if( string[i] == ' ' )
		{
			BlankLen++;
		}
	}
	
	int LaterLen = originlen + BlankLen * 2;
	if( LaterLen > length )
		return;
	
	int indexOfOrigin = originLen;
	int indexNewLen   = LaterLen;
	
	while( indexNewLen > indexOfOrigin && indexOfOrigin >= 0 )
	{
		if( string[indexOfOrigin] == '\0' )
		{
			string[indexNewLen--] = '0'; 
			string[indexNewLen--] = '2';
			string[indexNewLen--] = '%';
		}
		else
		{
			string[indexNewLen--] = string[indexOfOrigin];
		}
		
		indexOfOrigin--;
	}
}

int main(void)
{
	
}

