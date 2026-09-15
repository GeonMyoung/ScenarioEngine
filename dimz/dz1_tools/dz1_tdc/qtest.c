#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_cleanup.h>
#include <dz1_parser.h>
#include "publish_spec_dz1.h"
#include "dz1_mdefc_parser.h"
#include "misc.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpec *spec;

	Dz1Cleanup_init();

	if ((spec = PublishSpec_dz1(&err)) == NULL) ERR_OUT(&err);
	else
	{
		IncludeSpec *inc = NULL;
		pthread_cleanup_push((Dz1DelFunc)PublishSpec_del, (void *)spec);

		if ((inc = IncludeSpec_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			str_t file = "sample_module";
			char fn[1024];
			str_t text = NULL;

			pthread_cleanup_push((Dz1DelFunc)IncludeSpec_del, (void *)inc);

			sprintf(fn, "%s.tdc", file);

			if ((text = file_load(NULL, fn, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)text);

				Dz1MdefcModule *module = Dz1MdefcModule_compile(spec, inc, file, text, &err);
				if (module == NULL) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);
					Dz1Thread_printf("Result:");
					Dz1MdefcModule_dump(module, 0);
					Dz1Thread_printf("}\n");
					pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);
				}
				pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)text);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)IncludeSpec_del, (void *)inc);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)PublishSpec_del, (void *)spec);
	}
	return err.code;
}
