#include <stdio.h>
#include <assert.h>
#include "LTE_cid_dynamic_struct.h"
#include "UMTS_cid_dynamic_struct.h"

void print_all_cid(LTE_cid *LTE_cid_struct, UMTS_cid *UMTS_cid_struct,
				   const char *out_filename)
{
	int i;
	FILE *fp_out = fopen(out_filename, "w");
	assert(fp_out != NULL);
	for (i = 0; i < LTE_cid_struct->array_member; i++)
		fprintf(fp_out, "LTE,%d,%ld,%d\n",
				LTE_cid_struct->array[i]->channel,
				LTE_cid_struct->array[i]->cid,
				LTE_cid_struct->array[i]->count);
	for (i = 0; i < UMTS_cid_struct->array_member; i++)
		fprintf(fp_out, "UMTS,%d,%s,%d\n",
				UMTS_cid_struct->array[i]->channel,
				UMTS_cid_struct->array[i]->cid,
				UMTS_cid_struct->array[i]->count);
	fclose(fp_out);
	return;
}
