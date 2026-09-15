#include <pthread.h>
#include <errno.h>
#include "hae_local_memory.h"
#include "hae_output.h"
#include "hae_inet.h"
#include "hae_misc.h"

//#include "hae_crypt.h"

#include "hae_net_msg.h"

#define NETBUF_VERSION		0x00010001

#define NETBUF_MAGIC		0xc4b03743

typedef struct 
{ 
	u32_t magic;
	u32_t version;
	int size; 
} HaeNetMsgPdu; 
 
#define haeNetMsgFrag_spaceRemain(ptr)		(NETBUFFER_FRAG_SIZE - (ptr)->end)
#define haeNetMsgFrag_dataRemain(ptr)		((ptr)->end - (ptr)->start)

#define nbData(ptr)							((ptr)->data + (ptr)->start)
#define nbSpace(ptr)						((ptr)->data + (ptr)->end)
#define nbSize(ptr)							((ptr)->end - (ptr)->start)

///////////////////////////////////////////////////////////////////////////////
// HaeNetMsgFrag
///////////////////////////////////////////////////////////////////////////////
static HaeNetMsgFrag *haeNetMsgFrag_new(void)
{
	HaeNetMsgFrag *ret = (HaeNetMsgFrag *)LOCAL_MALLOC(sizeof(HaeNetMsgFrag));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsgFrag_new() : Memory allocation error\n");
		exit(1);
	}
	memset(ret, 0, sizeof(HaeNetMsgFrag));
	return ret;
}

static void haeNetMsgFrag_del(HaeNetMsgFrag *frag)
{
	HaeNetMsgFrag *next;
	while(frag)
	{
		next = frag->next;
		LOCAL_FREE(frag);
		frag = next;
	}
}

static int haeNetMsg_getSize(HaeNetMsg *buf)
{
	int len = 0;
	HaeNetMsgFrag *p = NULL;
	if (!buf) return len;
	for (p = buf->head; p; p=p->next)
		len += nbSize(p);
	return len;
}

///////////////////////////////////////////////////////////////////////////////
// HaeNetMsg
///////////////////////////////////////////////////////////////////////////////
static void haeNetMsg_add(HaeNetMsg *buf, HaeNetMsgFrag *frag)
{
	if (buf->head)
	{
		buf->tail->next = frag;
		buf->tail = frag;
	}
	else
		buf->head = buf->tail = frag;
}

HaeNetMsg *haeNetMsg_new(void)
{
	HaeNetMsg *ret = (HaeNetMsg *)LOCAL_MALLOC(sizeof(HaeNetMsg));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsg_new() : Memory allocation error\n");
		exit(1);
	}
	ret->head = ret->tail = NULL;
	return ret;
}

HaeNetMsg *haeNetMsg_clone(HaeNetMsg *buf)
{
	HaeNetMsg *ret = NULL;
	HaeNetMsgFrag *p = NULL, *frag = NULL;
	if (!buf) return NULL;
	ret = haeNetMsg_new();
	for (p = buf->head; p; p=p->next)
	{
		frag = haeNetMsgFrag_new();
		memcpy(frag->data, p->data, NETBUFFER_FRAG_SIZE);
		frag->start = p->start;
		frag->end = p->end;
		haeNetMsg_add(ret, frag);
	}
	return ret;
}

void haeNetMsg_del(void *p)
{
	HaeNetMsg *buf = (HaeNetMsg *)p;
	if (buf->head) haeNetMsgFrag_del(buf->head);
	LOCAL_FREE(buf);
}

void haeNetMsg_dump(HaeNetMsg *list, int tab)
{
	HaeNetMsgFrag *p;
	if (!list) return;
	if (!list->head)
		HaeOut->printf(tab, "Empty\n");
	else
	{
		for (p = list->head; p; p=p->next)
			HaeOut->printb(tab, nbData(p), nbSize(p));
	}
}

///////////////////////////////////////////////////////////////////////////////
// HaeNetMsg core APIs
///////////////////////////////////////////////////////////////////////////////
static int haeNetMsg_pushBIN(HaeNetMsg *buf, u8_t *data, u32_t len)
{
	if (buf->head)
	{
		HaeNetMsgFrag *p = buf->tail;
		if (haeNetMsgFrag_spaceRemain(p)>=len)
		{
			memcpy(nbSpace(p), data, len);
			p->end += len;
			return len;
		}
		else
		{
			int length = haeNetMsgFrag_spaceRemain(p);
			if (length == 0)
			{
				haeNetMsg_add(buf, haeNetMsgFrag_new());
				return haeNetMsg_pushBIN(buf, data, len);
			}
			else
			{
				memcpy(nbSpace(p), data, length);
				data += length;
				p->end += length;
				len -= length;
				return length + haeNetMsg_pushBIN(buf, data, len);
			}
		}

	}
	else
	{
		haeNetMsg_add(buf, haeNetMsgFrag_new());
		return haeNetMsg_pushBIN(buf, data, len);
	}
}

static void haeNetMsg_headClean(HaeNetMsg *buf)
{
	HaeNetMsgFrag *next, *p = buf->head;
	while(p && p->start == p->end)
	{
		next = p->next;
		LOCAL_FREE(p);
		p = next;
	}
	buf->head = p;
}

static int haeNetMsg_popBIN(HaeNetMsg *buf, u8_t *data, u32_t len)
{
	haeNetMsg_headClean(buf);
	if (buf->head)
	{
		HaeNetMsgFrag *p = buf->head;
		if (haeNetMsgFrag_dataRemain(p)>=len)
		{
			memcpy(data, nbData(p), len);
			p->start+=len;
			return len;
		}
		else
		{
			int length = haeNetMsgFrag_dataRemain(p);
			memcpy(data, nbData(p), length);
			data += length;
			p->start += length;
			len -= length;
			return length + haeNetMsg_popBIN(buf, data, len);
		}
	}
	else
	{
		HaeOut->printf(0, "haeNetMsg_popBIN() : HaeNetMsg is Empty\n");
		return -1;
	}
}

static int _haeNetMsg_strlen(HaeNetMsgFrag *p)
{
	int len = 0;
	int c;
	if (!p)
	{
		HaeOut->printf(0,"_haeNetMsg_strlen() : HaeNetMsgFrag is NULL\n");
		return 0;
	}
	if (p->start == p->end)
	{
		if (p->next)
		{
			return len + _haeNetMsg_strlen(p->next);
		}
		else
		{
			HaeOut->printf(0,"_haeNetMsg_strlen() : HaeNetMsgFrag is Empty (%d, %d, %p)\n", p->start, p->end, p->next);
			return 0;
		}
	}
	c = p->start;
	while(c < (int)p->end && *(p->data + c) != '\0')
	{
		len ++;
		c++;
	}
	if (c == NETBUFFER_FRAG_SIZE)
	{
		return len + _haeNetMsg_strlen(p->next);
	}
	else
		return len;
}

static int haeNetMsg_strlen(HaeNetMsg *buf)
{
	if (!buf) 
	{
		HaeOut->printf(0,"haeNetMsg_strlen() : HaeNetMsg is NULL\n");
		return 0;
	}
	if (!buf->head)
	{
		HaeOut->printf(0,"haeNetMsg_strlen() : HaeNetMsg is empty\n");
		return 0;
	}
	return _haeNetMsg_strlen(buf->head);
}

///////////////////////////////////////////////////////////////////////////////
// HaeNetMsg Push/Pop APIs
///////////////////////////////////////////////////////////////////////////////
int haeNetMsg_push8(HaeNetMsg *buf, u8_t data)
{
	return haeNetMsg_pushBIN(buf, (u8_t *)&data, sizeof(u8_t));
}

int haeNetMsg_pop8(HaeNetMsg *buf, u8_t *data)
{
	int len = 0;
	if ((len = haeNetMsg_popBIN(buf, (u8_t *)data, sizeof(u8_t))) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_pop8() : Decode Fail\n");
		return -1;
	}
	return len;
}

int haeNetMsg_push16(HaeNetMsg *buf, u16_t data)
{
	data = htons(data);
	return haeNetMsg_pushBIN(buf, (u8_t *)&data, sizeof(u16_t));
}

int haeNetMsg_pop16(HaeNetMsg *buf, u16_t *data)
{
	int len = 0;
	if ((len = haeNetMsg_popBIN(buf, (u8_t *)data, sizeof(u16_t))) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_pop16() : Decode Fail\n");
		return -1;
	}
	*data = ntohs(*data);
	return len;
}

int haeNetMsg_push32(HaeNetMsg *buf, u32_t data)
{
	data = htonl(data);
	return haeNetMsg_pushBIN(buf, (u8_t *)&data, sizeof(u32_t));
}

int haeNetMsg_pop32(HaeNetMsg *buf, u32_t *data)
{
	int len = 0;
	if ((len = haeNetMsg_popBIN(buf, (u8_t *)data, sizeof(u32_t))) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_pop32() : Decode Fail\n");
		return -1;
	}
	*data = ntohl(*data);
	return len;
}

int haeNetMsg_push64(HaeNetMsg *buf, u64_t data)
{
	data = hae_htonll(data);
	return haeNetMsg_pushBIN(buf, (u8_t *)&data, sizeof(u64_t));
}

int haeNetMsg_pop64(HaeNetMsg *buf, u64_t *data)
{
	int len = 0;
	if ((len = haeNetMsg_popBIN(buf, (u8_t *)data, sizeof(u64_t))) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_pop64() : Decode Fail\n");
		return -1;
	}
	*data = hae_ntohll(*data);
	return len;
}

int haeNetMsg_pushStr(HaeNetMsg *buf, str_t data)
{
	if (!data) return haeNetMsg_pushBIN(buf, (u8_t *)"", 1);
	return haeNetMsg_pushBIN(buf, (u8_t *)data, strlen(data)+1);
}

int haeNetMsg_popStr(HaeNetMsg *buf, char **data)
{
	int len = 0;
	len = haeNetMsg_strlen(buf)+1;
	*data = (str_t)LOCAL_MALLOC(len);
	if (!(*data))
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsg_popStr() : Memory allocation error\n");
		exit(1);
	}
	if ((len = haeNetMsg_popBIN(buf, (u8_t *)*data, len)) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_popStr() : Decode Fail\n");
		return -1;
	}
	return len;
}

int haeNetMsg_pushBin(HaeNetMsg *buf, str_t data, int len)
{
	int ret = 0, result;
	if ((result = haeNetMsg_push32(buf, len)) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_pushBin() : Encode Fail\n");
		return -1;
	}
	else
		ret += result;
	if (len)
	{
		if ((result = haeNetMsg_pushBIN(buf, (u8_t *)data, len)) == -1)
		{
			HaeOut->printf(0,"haeNetMsg_pushBin() : Encode Fail\n");
			return -1;
		}
		else
			ret += result;
	}
	return ret;
}

int haeNetMsg_popBin(HaeNetMsg *buf, str_t *data, int *len)
{
	int ret = 0;
	int result;
	if ((result = haeNetMsg_pop32(buf, (u32_t *)len)) == -1)
	{
		HaeOut->printf(0,"haeNetMsg_popBin() : Decode Fail\n");
		return -1;
	}
	else
		ret += result;
	if (*len)
	{
		*data = (str_t)LOCAL_MALLOC(*len);
		if (!(*data))
		{
			HaeOut->fprintf(stdout, 0,"haeNetMsg_popBin() : Memory allocation error\n");
			exit(1);
		}
		if ((result = haeNetMsg_popBIN(buf, (u8_t *)*data, *len)) == -1)
		{
			HaeOut->printf(0,"haeNetMsg_popBin() : Decode Fail\n");
			return -1;
		}
		else
			ret += result;
	}
	else
		data = NULL;
	HaeOut->printf(0,"haeNetMsg_popBin() : ret = %d\n", ret);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// NetMsgPdu API
///////////////////////////////////////////////////////////////////////////////
static void haeNetMsgPdu_pack(HaeNetMsg *buf, char *msg)
{
	HaeNetMsgFrag *p;
	int len;
	for (p = buf->head; p; p=p->next)
	{
		len = nbSize(p);
		memcpy(msg, nbData(p), len);
		msg += len;
	}
}

static void haeNetMsgPdu_unpack(HaeNetMsg *buf, char *msg, int len)
{
	HaeNetMsgFrag *frag;
	while(len)
	{
		frag = haeNetMsgFrag_new();
		if (len > NETBUFFER_FRAG_SIZE)
		{
			memcpy(nbSpace(frag), msg, NETBUFFER_FRAG_SIZE);
			frag->end = NETBUFFER_FRAG_SIZE;
			len -= NETBUFFER_FRAG_SIZE;
			msg += NETBUFFER_FRAG_SIZE;
		}
		else
		{
			memcpy(nbSpace(frag), msg, len);
			frag->end = len;
			len -= len;
			msg += len;
		}
		haeNetMsg_add(buf, frag);
	}
}


///////////////////////////////////////////////////////////////////////////////
// NetMsg PDU API
///////////////////////////////////////////////////////////////////////////////
int haeNetMsg_getStream(HaeNetMsg *buf, void **stream)
{
	int size;
	HaeNetMsgPdu *msg = NULL;
	if (!buf)
	{
		HaeOut->printf(0,"haeNetMsg_getStream() : HaeNetMsg is NULL\n");
		return -1;
	}
	if (*stream)
	{
		HaeOut->printf(0,"haeNetMsg_getStream() : stream is not NULL\n");
		return -1;
	}
	size = haeNetMsg_getSize(buf) + sizeof(HaeNetMsgPdu);
	*stream = (void *)LOCAL_MALLOC(size);
	if (!*stream)
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsg_getStream() : Memory allocation error\n");
		return -1;
	}
	msg = (HaeNetMsgPdu *)*stream;

	msg->magic = htonl(NETBUF_MAGIC);
	msg->version = htonl(NETBUF_VERSION);

	msg->size = htonl(size - sizeof(HaeNetMsgPdu));
	haeNetMsgPdu_pack(buf, ((char *)msg+sizeof(HaeNetMsgPdu)));

	return size;
}

///////////////////////////////////////////////////////////////////////////////
// NetMsg Send APIs
///////////////////////////////////////////////////////////////////////////////
static void memory_free(void *p) { LOCAL_FREE(p); }

// return SOCKET Error or 0
int haeNetMsg_send(SOCKET fd, HaeNetMsg *buf)
{
	int size, ret;
	void *ptr = NULL;
	size = haeNetMsg_getStream(buf, &ptr);
	pthread_cleanup_push(memory_free, ptr);
	if (size < 0) return FALSE;
	ret = hae_inet_sendStream(fd, ptr, size, NULL);
	pthread_cleanup_pop(1); //(memory_free, ptr);
	return ret;
}

#define SEND_TO_SEG_LEN		(1460 * 3)
static int haeNetMsgPdu_socketSendto(SOCKET fd, char *msg, int len, struct sockaddr *to, int to_len)
{
	int length;
	if ((length = sendto(fd, msg, sizeof(HaeNetMsgPdu), 0, to, to_len))<0)
	{
		HaeOut->printf(0,"haeNetMsgPdu_socketSendto() : length = %d, sendto = %s(%d)\n", length, strerror(errno), errno);
		HaeOut->printb(0, (char *)to, to_len);
		return FALSE;
	}
	else
	{
		len -= sizeof(HaeNetMsgPdu);
		msg += sizeof(HaeNetMsgPdu);
		while(len)
		{
			if (len >= SEND_TO_SEG_LEN)
				length = sendto(fd, msg, SEND_TO_SEG_LEN, 0, to, to_len);
			else
				length = sendto(fd, msg, len, 0, to, to_len);
			if (length <= 0)
			{
				HaeOut->printf(0,"haeNetMsgPdu_socketSendto() : length = %d, sendto = %s(%d)\n", length, strerror(errno), errno);
				return FALSE;
			}
			msg+=length;
			len -= length;
		}
	}
	return TRUE;
}

int haeNetMsg_sendto(SOCKET fd, HaeNetMsg *buf, struct sockaddr *to, int to_len)
{
	int size, ret;
	void *msg = NULL;
	size = haeNetMsg_getStream(buf, &msg);
	pthread_cleanup_push(memory_free, msg);
	ret = haeNetMsgPdu_socketSendto(fd, (char *)msg, size, to, to_len);
	pthread_cleanup_pop(1); //(memory_free, msg);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// NetMsg Send APIs
///////////////////////////////////////////////////////////////////////////////
HaeNetMsg *haeNetMsg_recv(SOCKET fd)
{
	HaeNetMsgPdu pdu, *msg;
	HaeNetMsg *buf = NULL;
	int status = 0;
	if ((status = hae_inet_recvStreamPdu(fd, (void *)&pdu, sizeof(HaeNetMsgPdu), NULL)) != 0)
	{
		HaeOut->printf(0, "haeNetMsg_recv() : err=%s(%d)\n", strerror(status), status);
		return NULL;
	}

	pdu.magic = ntohl(pdu.magic);
	pdu.version = ntohl(pdu.version);
	pdu.size = ntohl(pdu.size);

	if (pdu.magic != NETBUF_MAGIC || pdu.version != NETBUF_VERSION)
	{
		HaeOut->printf(0,"haeNetMsg_recv() : Invalid Pdu\n");
		return NULL;
	}

	HaeOut->printf(0, "haeNetMsg_recv() : pdu.size = %u from socket %d\n", pdu.size, fd);

	msg = (HaeNetMsgPdu *)LOCAL_MALLOC(pdu.size + sizeof(HaeNetMsgPdu));
	if (!msg)
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsg_recv() : Memory allocation error\n");
		exit(1);
	}

	pthread_cleanup_push(memory_free, (void *)msg);

	memset(msg, 0, pdu.size + sizeof(HaeNetMsgPdu));
	memcpy(msg, &pdu, sizeof(HaeNetMsgPdu));

	if ((status = hae_inet_recvStreamPdu(fd, (void *)((char *)msg + sizeof(HaeNetMsgPdu)), pdu.size, NULL)) != 0)
		HaeOut->printf(0, "haeNetMsg_recv() : err=%s(%d)\n", strerror(status), status);
	else
	{
		buf = haeNetMsg_new();
		haeNetMsgPdu_unpack(buf, ((char *)msg+sizeof(HaeNetMsgPdu)), msg->size);
	}
	pthread_cleanup_pop(1); // (memory_free, (void *)msg);
	HaeOut->printf(0, "haeNetMsg_recv() : return %p\n", buf);
	return buf;
}

HaeNetMsg *haeNetMsg_recvfrom(SOCKET fd, struct sockaddr *his, int *his_len)
{
	int status = 0;
	HaeNetMsgPdu pdu, *msg;
	char *dataPtr = NULL;
	HaeNetMsg *buf = NULL;
	int readByte = recvfrom(fd, (char *)&pdu, sizeof(HaeNetMsgPdu), 0, his, (socklen_t *)his_len);
	if (readByte <= 0) 
	{
		HaeOut->printf(0, "haeNetMsg_recv(0) : readByte = %d err=%s(%d)\n", readByte, strerror(errno), errno);
		return NULL;
	}
	pdu.magic = ntohl(pdu.magic);
	pdu.version = ntohl(pdu.version);
	pdu.size = ntohl(pdu.size);
	if (pdu.magic != NETBUF_MAGIC || pdu.version != NETBUF_VERSION)
	{
		HaeOut->printf(0,"haeNetMsg_recv() : Invalid Pdu (%x, %x, %x)\n", pdu.magic, pdu.version, pdu.size);
		return NULL;
	}
	HaeOut->printf(0, "haeNetMsg() : pdu.size = %u\n", pdu.size);
	msg = (HaeNetMsgPdu *)LOCAL_MALLOC(pdu.size + sizeof(HaeNetMsgPdu));
	if (!msg)
	{
		HaeOut->fprintf(stdout, 0,"haeNetMsg_recv() : Memory allocation error\n");
		exit(1);
	}
	pthread_cleanup_push(memory_free, (void *)msg);

	memcpy(msg, &pdu, sizeof(HaeNetMsgPdu));
	dataPtr = (char *)msg + sizeof(HaeNetMsgPdu);

	status = 0;

	while(pdu.size)
	{
		readByte = recvfrom(fd, dataPtr, pdu.size, 0, his, (socklen_t *)his_len);
		if (readByte <= 0) 
		{
			HaeOut->printf(0, "haeNetMsg_recv(1) : readByte = %d\n", readByte);
			if (readByte == 0)
				status = EPIPE;
			else
				status = errno;
			break;
		}
		pdu.size -= readByte;
		dataPtr += readByte;
	}

	if (status == 0)
	{
		buf = haeNetMsg_new();
		haeNetMsgPdu_unpack(buf, ((char *)msg+sizeof(HaeNetMsgPdu)), msg->size);
	}
	pthread_cleanup_pop(1); // (memory_free, (void *)msg);
	HaeOut->printf(0, "haeNetMsg_recv() : return %p\n", buf);
	return buf;
}

int haeNetMsg_save(HaeNetMsg *buf, FILE *fp)
{
	int size, ret = 0;
	void *msg = NULL;
	size = haeNetMsg_getStream(buf, &msg);
	pthread_cleanup_push(memory_free, msg);
	if (fwrite(msg, size, 1, fp) == 0) ret = ferror(fp);
	pthread_cleanup_pop(1); //(memory_free, msg);
	return ret;
}

HaeNetMsg *haeNetMsg_load(FILE *fp, int *err)
{
	int local_err, *errp = err ? err : &local_err;

	HaeNetMsgPdu pdu, *msg;
	HaeNetMsg *buf = NULL;

	*errp = 0;

	if (fread(&pdu, sizeof(HaeNetMsgPdu), 1, fp) == 0)
	{
		*errp = ferror(fp);
		return NULL;
	}

	pdu.magic = ntohl(pdu.magic);
	pdu.version = ntohl(pdu.version);
	pdu.size = ntohl(pdu.size);

	if (pdu.magic != NETBUF_MAGIC || pdu.version != NETBUF_VERSION)
	{
		*errp = EINVAL;
		return NULL;
	}

	msg = (HaeNetMsgPdu *)LOCAL_MALLOC(pdu.size + sizeof(HaeNetMsgPdu));
	if (!msg)
	{
		*errp = ENOMEM;
		return NULL;
	}

	pthread_cleanup_push(memory_free, (void *)msg);

	memset(msg, 0, pdu.size + sizeof(HaeNetMsgPdu));
	memcpy(msg, &pdu, sizeof(HaeNetMsgPdu));

	if (fread(((char *)msg + sizeof(HaeNetMsgPdu)), pdu.size, 1, fp) == 0)
	{
		*errp = ferror(fp);
	}
	else
	{
		buf = haeNetMsg_new();
		haeNetMsgPdu_unpack(buf, ((char *)msg+sizeof(HaeNetMsgPdu)), msg->size);
	}
	pthread_cleanup_pop(1); // (memory_free, (void *)msg);
	return buf;

}
///////////////////////////////////////////////////////////////////////////////
// HaeNetMsg MISC APIs
///////////////////////////////////////////////////////////////////////////////
void haeNetMsg_analysis(HaeNetMsg *buf)
{
	int size;
	HaeNetMsgPdu *msg = NULL;
	size = haeNetMsg_getSize(buf);
	msg = (HaeNetMsgPdu *)LOCAL_MALLOC(size+sizeof(HaeNetMsgPdu));
	msg->magic = htonl(NETBUF_MAGIC);
	msg->version = htonl(NETBUF_VERSION);
	haeNetMsgPdu_pack(buf, ((char *)msg+sizeof(HaeNetMsgPdu)));
	HaeOut->printb(0, (char *)msg, size + sizeof(HaeNetMsgPdu));
	LOCAL_FREE(msg);
}

