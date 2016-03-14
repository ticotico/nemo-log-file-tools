#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "LTE_cid_dynamic_struct.h"

void ini_LTE_cid (LTE_cid *LTE_cid_struct)
{
	LTE_cid_unit **new_array = (LTE_cid_unit **) malloc (sizeof(LTE_cid_unit **));
	assert(new_array != NULL);
	LTE_cid_struct->array = new_array;
	LTE_cid_struct->array_size = 1;
	LTE_cid_struct->array_member = 0;
	return ;
}

void add_LTE_cid (LTE_cid *LTE_cid_struct, int channel, long cid)
{
	int i;
	// 如果目前的 cid 已經加入過 陣列 
	for (i = 0; i < LTE_cid_struct->array_member; i++)
		if (channel == LTE_cid_struct->array[i]->channel && cid == LTE_cid_struct->array[i]->cid) { 	
			LTE_cid_struct->array[i]->count++;		// 則 count++ 
			break;
		}
	// 如果目前加 cid 尚未加入過陣列 
	if (i == LTE_cid_struct->array_member) {
		// 如果 陣列 欄位使用滿了
		// 擴大 陣列 欄位 
		if (LTE_cid_struct->array_member == LTE_cid_struct->array_size) {
			int new_size = LTE_cid_struct->array_size * 2;
			#ifdef DEBUG
			printf("%s:%d\n", __FILE__, __LINE__);
			printf("array size grow to %d\n", new_size);
			#endif // DEBUG
			LTE_cid_unit **new_array = (LTE_cid_unit **) malloc (sizeof(LTE_cid_unit **) * new_size);
			assert(new_array != NULL);
			memcpy(new_array, LTE_cid_struct->array, sizeof(LTE_cid_unit **) * new_size);
			free(LTE_cid_struct->array);
			LTE_cid_struct->array = new_array;
			LTE_cid_struct->array_size = new_size;
		}
		// 將新的 channel 及 cid 加入陣列尾端並 count 為 1 ，接著 array_member++ 
		if (LTE_cid_struct->array_member < LTE_cid_struct->array_size) {
			LTE_cid_unit *new_unit = (LTE_cid_unit *) malloc (sizeof(LTE_cid_unit));
			assert(new_unit != NULL);
			new_unit->channel = channel;
			new_unit->cid = cid;
			new_unit->count = 1;
			LTE_cid_struct->array[LTE_cid_struct->array_member++] = new_unit;
		}
	}
	return ;
}

void print_LTE_cid(LTE_cid *LTE_cid_struct)
{
	int i;
	for (i = 0; i < LTE_cid_struct->array_member; i++)
		printf("LTE,%d,%ld,%d\n", LTE_cid_struct->array[i]->channel, LTE_cid_struct->array[i]->cid,
								  LTE_cid_struct->array[i]->count);
	return;
}

void close_LTE_cid(LTE_cid *LTE_cid_struct)
{
	int i;
	// 先釋放所有 unit 
	for (i = 0; i < LTE_cid_struct->array_member; i++)
		free(LTE_cid_struct->array[i]);
	// 釋放存放 unit 的 array 
	free(LTE_cid_struct->array);
	return;
}
