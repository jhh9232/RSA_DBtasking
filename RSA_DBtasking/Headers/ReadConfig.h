#include "common.h"
#include <sys/types.h>

#define NEXTSECTION '['
#define NOTHREAD -1
#define READSIZE 4096

#define COMMENT '#'
#define EQUALMARK "="
#define NEXTLINE "\n"

int openCfg(const char*);
void CfgSplit(char*);
int CfgFindSection(char*);
char* CfgNextItem();
char* CfgGetValue(char*, char*);
LInt CfgGetData(char*, char*);