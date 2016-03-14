#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "UMTS_cid_dynamic_struct.h"

void ini_UMTS_cid (UMTS_cid *UMTS_cid_struct)
{
	UMTS_cid_unit **new_array = (UMTS_cid_unit **) malloc (sizeof(UMTS_cid_unit **));
	assert(new_array != NULL);
	UMTS_cid_struct->array = new_array;
	UMTS_cid_struct->array_size = 1;
	UMTS_cid_struct->array_member = 0;
	return ;
}

void add_UMTS_cid (UMTS_cid *UMTS_cid_struct, int channel, const char *cid)
{
	int i;
	// 如果目前的 cid 已經加入過 陣列 
	for (i = 0; i < UMTS_cid_struct->array_member; i++)
		if (channel == UMTS_cid_struct->array[i]->channel && strcmp(cid , UMTS_cid_struct->array[i]->cid) == 0) { 	
			UMTS_cid_struct->array[i]->count++;		// 則 count++ 
			break;
		}
	// 如果目前加 cid 尚未加入過陣列 
	if (i == UMTS_cid_struct->array_member) {
		// 如果 陣列 欄位使用滿了
		// 擴大 陣列 欄位 
		if (UMTS_cid_struct->array_member == UMTS_cid_struct->array_size) {
			int new_size = UMTS_cid_struct->array_size * 2;
			#ifdef DEBUG
			printf("%s:%d\n", __FILE__, __LINE__);
			printf("array size grow to %d\n", new_size);
			#endif // DEBUG
			UMTS_cid_unit **new_array = (UMTS_cid_unit **) malloc (sizeof(UMTS_cid_unit **) * new_size);
			assert(new_array != NULL);
			memcpy(new_array, UMTS_cid_struct->array, sizeof(UMTS_cid_unit **) * new_size);
			free(UMTS_cid_struct->array);
			UMTS_cid_struct->array = new_array;
			UMTS_cid_struct->array_size = new_size;
		}
		// 將新的 channel 及 cid 加入陣列尾端並 count 為 1 ，接著 array_member++ 
		if (UMTS_cid_struct->array_member < UMTS_cid_struct->array_size) {
			UMTS_cid_unit *new_unit = (UMTS_cid_unit *) malloc (sizeof(UMTS_cid_unit));
			assert(new_unit != NULL);
			new_unit->channel = channel;
			strcpy(new_unit->cid, cid);
			new_unit->count = 1;
			UMTS_cid_struct->array[UMTS_cid_struct->array_member++] = new_unit;
		}
	}
	return ;
}

void print_UMTS_cid(UMTS_cid *UMTS_cid_struct)
{
	int i;
	for (i = 0; i < UMTS_cid_struct->array_member; i++)
		printf("UMTS,%d,%s,%d\n", UMTS_cid_struct->array[i]->channel, UMTS_cid_struct->array[i]->cid,
								  UMTS_cid_struct->array[i]->count);
	return;
}

void close_UMTS_cid(UMTS_cid *UMTS_cid_struct)
{
	int i;
	// 先釋放所有 unit 
	for (i = 0; i < UMTS_cid_struct->array_member; i++)
		free(UMTS_cid_struct->array[i]);
	// 釋放存放 unit 的 array 
	free(UMTS_cid_struct->array);
	return;
}
