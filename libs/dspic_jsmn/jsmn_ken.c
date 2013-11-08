#include "jsmn.h"
#include <stdlib.h>
#include <stdio.h>

jsmn_parser json_parser;
#define NUM_JSON_TOKENS 30
jsmntok_t json_tokens[NUM_JSON_TOKENS];

int main(){
	char* str = " { \"name\" : \"Jack\", \"age\" : 27}";
	unsigned i;
	jsmn_init(&json_parser);
	int err = jsmn_parse(&json_parser,str,json_tokens,NUM_JSON_TOKENS);
	
	printf("%d err %d children: %u type: %d\n",err,json_tokens[0].end-json_tokens[0].start,json_tokens[0].size,json_tokens[0].type);	
	for(i=0;i<json_tokens[0].size;++i){
		printf("%d children: %u type: %d\n",json_tokens[i+1].end-json_tokens[i+1].start,json_tokens[i+1].size,json_tokens[i+1].type);

	}
	return 0;
}
