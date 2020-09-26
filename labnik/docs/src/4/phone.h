#define NAME_LEN 20
#define NUM_LEN 20

struct phone{
	int group;
	char name[NAME_LEN];
	char num[NUM_LEN];
};

typedef struct phone phones;
