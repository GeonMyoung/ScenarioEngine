#include <dz1_crc32.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static u32_t table[256] = { 0, };
bool_t initialized = FALSE;

void Dz1CRC32_IEEE802Dot3_buildTable(void)
{
	u32_t i, j;
	static const u8_t p[] = { 0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 16, 22, 23, 26 };
	u32_t c, poly = 0;

	for (i = 0; i < sizeof(p) / sizeof(u8_t); i++) poly |= 1 << (31 - p[i]);

	for (i = 0; i < 256; i++)
	{
		c = i;
		for (j = 0; j < 8; j++) c = (c & 1) ? poly ^ (c >> 1) : (c >> 1);
		table[i] = c;
	}
}

static void Dz1CRC32_IEEE802Dot3_init(void)
{
	pthread_mutex_lock(&lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
	if (initialized == FALSE)
	{
		Dz1CRC32_IEEE802Dot3_buildTable();
		initialized = TRUE;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
}

static u32_t _Dz1CRC32_IEEE802Dot3_buffer(u8_t *data, size_t size, u32_t crc)
{
	u8_t *cp = data;
	crc = ~crc;

	while(size--) crc = (crc >> 8) ^ table[(crc ^ *cp++) & 0xFF];

	return (~crc);
}

u32_t Dz1CRC32_IEEE802Dot3_buffer(u8_t *data, size_t size, u32_t crc)
{
	Dz1CRC32_IEEE802Dot3_init();

	return _Dz1CRC32_IEEE802Dot3_buffer(data, size, crc);
}

u32_t Dz1CRC32_IEEE802Dot3_file(FILE *fp, size_t size, u32_t crc)
{

	u8_t buf[0x10000];
	size_t sz;

	Dz1CRC32_IEEE802Dot3_init();

	while((sz = fread(buf, sizeof(u8_t), 0x10000, fp)) > 0)
	{
		crc = _Dz1CRC32_IEEE802Dot3_buffer(buf, sz, crc);
		size -= sz;

		if (size == 0) break;
	}

	return crc;
}
