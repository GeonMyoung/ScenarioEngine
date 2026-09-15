#include <dz1_cleanup.h>
#include <dz1_parser.h>
#include "publish_spec_dz1.h"
#include "dz1_mdefc_parser.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpec *spec;

	Dz1Cleanup_init();

	if ((spec = PublishSpec_dz1(&err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)PublishSpec_del, (void *)spec);
		PublishSpec_dump(spec, 0);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)PublishSpec_del, (void *)spec);
	}
	return err.code;
}
