#include "UMTS_cid_unit.h"

#ifndef UMTS_cid_def
#define UMTS_cid_def
typedef struct {
	UMTS_cid_unit **array;
	int array_size;
	int array_member; 
} UMTS_cid;
#endif // UMTS_cid_def
