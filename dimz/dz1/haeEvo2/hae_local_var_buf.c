#include "hae_output.h"
#include "hae_local_memory.h"
#include "hae_local_var_buf.h"

static int haeLocalVarBufFrag_getDataSize(HaeLocalVarBufFrag *p)
{
	return p->head - p->tail;
}

static int haeLocalVarBufFrag_getSpaceSize(HaeLocalVarBufFrag *p)
{
	return HAE_VAR_BUF_FRAG_SIZE - haeLocalVarBufFrag_getDataSize(p);
}

static HaeLocalVarBufFrag *haeLocalVarBufFrag_create(void)
{
	HaeLocalVarBufFrag *ret = (HaeLocalVarBufFrag *)malloc(sizeof(HaeLocalVarBufFrag));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalVarBufFrag_create() : Memory allocation error\n");
		exit(1);
	}
	ret->next = NULL;
	memset(ret->buf, 0, HAE_VAR_BUF_FRAG_SIZE);
	ret->head = ret->tail = 0;
	ret->getDataSize = haeLocalVarBufFrag_getDataSize;
	ret->getSpaceSize = haeLocalVarBufFrag_getSpaceSize;
	return ret;
}

static void haeLocalVarBufFrag_del(HaeLocalVarBufFrag *p)
{
	if (!p) return;
	free(p);
}

static void haeLocalVarBufFrag_dump(HaeLocalVarBufFrag *p, int tab)
{
	if (!p) return;
	else
	{
		char buf[HAE_VAR_BUF_FRAG_SIZE];
		char *cp = buf;
		int size = p->getDataSize(p);
		int contig_size = HAE_VAR_BUF_FRAG_SIZE - p->head;
		if (size > contig_size)
		{ // splited
			memcpy(cp, &p->buf[p->head], contig_size);
			cp += contig_size;
			memcpy(cp, p->buf, p->tail);
		}
		else
			memcpy(cp, &p->buf[p->head], size);
		HaeOut->printb(tab, buf, size);
	}
}

static int haeLocalVarBuf_push(HaeLocalVarBuf *p, char c)
{
	if (p->head)
	{
		if (p->tail->getSpaceSize(p->tail))
		{
			p->tail->buf[p->tail->head++] = c;
			return TRUE;
		}
		else
		{
			p->tail->next = haeLocalVarBufFrag_create();
			p->tail = p->tail->next;
			return haeLocalVarBuf_push(p, c);
		}
	}
	else
	{
		p->head = p->tail = haeLocalVarBufFrag_create();
		return haeLocalVarBuf_push(p, c);
	}
}

static int haeLocalVarBuf_push_strl(HaeLocalVarBuf *p, str_t str, u32_t len)
{
	if (!str || !(len)) return FALSE;
	if (p->head)
	{
		u32_t contig_size = 0;
		if ((contig_size = p->tail->getSpaceSize(p->tail)) > 0)
		{
			if (contig_size >= len)
			{
				memcpy(&p->tail->buf[p->tail->head], str, len);
				p->tail->head += len;
				return TRUE;
			}
			else
			{
				memcpy(&p->tail->buf[p->tail->head], str, contig_size);
				p->tail->head += contig_size;
				str += contig_size;
				len -= contig_size;
				p->tail->next = haeLocalVarBufFrag_create();
				p->tail = p->tail->next;
				return haeLocalVarBuf_push_strl(p, str, len);
			}
		}
		else
		{
			p->tail->next = haeLocalVarBufFrag_create();
			p->tail = p->tail->next;
			return haeLocalVarBuf_push_strl(p, str, len);
		}
	}
	else
	{
		p->head = p->tail = haeLocalVarBufFrag_create();
		return haeLocalVarBuf_push_strl(p, str, len);
	}
}


static int haeLocalVarBuf_push_str(HaeLocalVarBuf *p, str_t str)
{
	int len = 0;
	if (!str || !(len = strlen(str))) return FALSE;
	return haeLocalVarBuf_push_strl(p, str, len);
}

static int haeLocalVarBuf_len(HaeLocalVarBuf *p)
{
	int ret = 0;
	HaeLocalVarBufFrag *node = NULL;
	for (node = p->head; node; node = node->next)
		ret += node->getDataSize(node);
	return ret;
}

str_t _haeLocalVarBuf_concat(HaeLocalVarBuf *p HAE_LOCAL_MEMORY_TRC_ARG)
{
	int len = 0;
	str_t ret = NULL, dst = NULL;
	HaeLocalVarBufFrag *node = NULL;
	if (!p || !(len = haeLocalVarBuf_len(p))) return NULL;
	dst = ret = LOCAL_MALLOC_TRC(len + 1);
	for (node = p->head; node; node = node->next)
	{
		memcpy(dst, &node->buf[node->tail], node->getDataSize(node));
		dst += node->getDataSize(node);
	}
	ret[len] = '\0';
	return ret;
}

HaeLocalVarBuf *_haeLocalVarBuf_create(HAE_LOCAL_MEMORY_TRC_ARG1)
{
	HaeLocalVarBuf *ret = (HaeLocalVarBuf *)LOCAL_MALLOC_TRC(sizeof(HaeLocalVarBuf));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalVarBuf_create() : Memory allocation error\n");
		exit(1);
	}
	ret->head = ret->tail = NULL;
	ret->push = haeLocalVarBuf_push;
	ret->push_str = haeLocalVarBuf_push_str;
	ret->push_strl = haeLocalVarBuf_push_strl;
	return ret;
}

void haeLocalVarBuf_del(HaeLocalVarBuf *p)
{
	HaeLocalVarBufFrag *node = NULL, *next = NULL;
	if (!p) return;
	node = p->head;
	while(node)
	{
		next = node->next;
		haeLocalVarBufFrag_del(node);
		node = next;
	}
	LOCAL_FREE(p);
}

void haeLocalVarBuf_dump(HaeLocalVarBuf *p, int tab)
{
	HaeLocalVarBufFrag *i;
	if (!p) return;
	for (i = p->head; i; i = i->next)
		haeLocalVarBufFrag_dump(i, tab);
}

void haeLocalVarBuf_cancel(void *p) { haeLocalVarBuf_del((HaeLocalVarBuf *)p); }
