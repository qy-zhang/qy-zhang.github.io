/**
 * @File : LongestSubstring.c
 * @Author : zhangqianyi
 * @Date : 2016/7/5
 * @Description : 
 		Given a string, find the length of the longest substring without repeating characters.
		Examples:

		Given "abcabcbb", the answer is "abc", which the length is 3.
		Given "bbbbb", the answer is "b", with the length of 1.
		Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubstring(char* s)
{
	int len = 0; // save the length of the substring
	int p = 0, q = 0; // the start index and end index of the substring
	int i;

	for (q = 0; q < strlen(s); ++q)
	{
		for (i = p; i < q; ++i)
		{
			if (s[i] == s[q])
			{
				if (q - p > len)
				{
					len = q - p;
				}
				p = i + 1;
				break;
			}
		}
	}
	len = len > q - p ? len : q - p;

	return len;
}

int main(int argc, char const *argv[])
{
	char* s = "nfvbiywbasfbu";
	int len = longestSubstring(s);

	printf("the length of string : %s is %d\n", s, len);

	return 0;
}