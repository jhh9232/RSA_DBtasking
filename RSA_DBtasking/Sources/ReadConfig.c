#include "../Headers/ReadConfig.h"

FILE* fp = NULL;
char key[LARGELEN] = { null };
char value[LARGELEN] = { null };

int openCfg(const char* filen)
{
	fp = fopen(filen, "r, ccs=UTF-8");
	if (fp == NULL)
		return false;
	return true;
}

void CfgSplit(char* data)
{
	char* sp = NULL, * ep = NULL;
	//Initialize
	memset(key, null, LARGELEN);
	memset(value, null, LARGELEN);

	//find equal mark, new line character
	sp = strstr(data, EQUALMARK);
	ep = strstr(data, NEXTLINE);

	if (ep == NULL)
	{
		ep = strstr(data, EQUALMARK);
		while (*ep != null)
			ep++;
	}

	//get key
	memcpy(key, data, (size_t)(sp - data));
	key[sp - data + 1] = null;

	//get value
	memcpy(value, sp + 1, (size_t)(ep - sp));
	value[ep - sp - 1] = null;
}

int CfgFindSection(char* secn)
{
	if (strlen(secn) >= READSIZE)
		return false;
	rewind(fp);
	char section[LARGELEN] = { null };
	char cfgbuf[LARGELEN] = { null };
	int rtv = false;
	section[0] = '[';
	strncpy(section + 1, secn, strlen(secn));
	section[strlen(section)] = ']';
	size_t secLen = strlen(section);

	while (fgets(cfgbuf, READSIZE, fp))
	{
		if (!strncmp(section, cfgbuf, secLen))
		{
			rtv = true;
			break;
		}
	}
	return rtv;
}

char* CfgNextItem()
{
	char cfgbuf[LARGELEN] = { null };
	while (true)
	{
		if (fgets(cfgbuf, READSIZE, fp) == NULL)
			return NULL;
		if (cfgbuf[0] != COMMENT)
		{
			if (strstr(cfgbuf, EQUALMARK)) break;
		}
	}
	if (cfgbuf[0] == NEXTSECTION)
		return NULL;
	CfgSplit(cfgbuf);
	return key;
}

char* CfgGetValue(char* secn, char* keyn)
{
	rewind(fp);
	char cfgbuf[LARGELEN] = { null };
	size_t namelen = strlen(keyn);
	char section[LARGELEN] = { null };

	section[0] = '[';
	strncpy(section + 1, secn, strlen(secn));
	section[strlen(section)] = ']';
	size_t secLen = strlen(section);

	memset(value, null, strlen(value));

	//find section
	while (fgets(cfgbuf, READSIZE, fp))
	{
		if (cfgbuf[0] == COMMENT) continue;

		if (!strncmp(section, cfgbuf, secLen))
			break;
	}

	//find key
	while (fgets(cfgbuf, READSIZE, fp))
	{
		if (cfgbuf[0] == COMMENT) continue;

		if (!strncmp(cfgbuf, keyn, namelen)
			&& cfgbuf[namelen] == '=')
		{
			CfgSplit(cfgbuf);
			return value;
		}
		else if (cfgbuf[0] == NEXTSECTION)
			return NULL;
	}
	return NULL;
}

LInt CfgGetData(char* secn, char* keyn)
{
	LInt result = { null, 0, NULL };
	if (openCfg("RSA_KEY.conf") == false)
	{
		printf("Unable to open or find \"RSA_KEY.conf\"\n");
		return result;
	}
	char* valueData = CfgGetValue(secn, keyn);
	if (valueData == NULL)
	{
		//printf("not find KEYS -> VALUE\n");
		fclose(fp);
		return result;
	}

	//printf("[%s]\n%s=\"%s\"\n", secn, keyn, valueData);
	fclose(fp);

	result = SetLArray(valueData);

	return result;
}