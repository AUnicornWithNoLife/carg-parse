// c argument parser - Rose (github.com/AUnicornWithNoLife)

#include "carg-parse.h"
#include <stdlib.h>

carg_parse_data* carg_parse(int argc, char** argv)
{
    carg_parse_data *data = (carg_parse_data*)malloc(sizeof(carg_parse_data));

    char **values = (char**)malloc(sizeof(char*) * argc);
    uint32_t values_cp = 0;

    char **lv_labels = (char**)malloc(sizeof(char*) * argc);
    char **lv_values = (char**)malloc(sizeof(char*) * argc);
    uint32_t lv_cp = 0;

	char **flags = (char**)malloc(sizeof(char*) * argc);
	uint32_t flags_cp = 0;

    data->exec_name = argv[0];

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-') // label / flag
        {
			if (argv[i][1] != '\0' && argv[i][1] == '-') // flag
			{
				flags[flags_cp] = argv[i] + 2;

				flags_cp++;
			}
			else // label
			{
            	lv_labels[lv_cp] = argv[i] + 1;

            	if (argc > i + 1 && argv[i + 1][0] != '-')
            	{
                	i++;

                	lv_values[lv_cp] = argv[i];
            	}
            	else
            	{
                	lv_values[lv_cp] = NULL;
            	}

            	lv_cp++;
			}
        }
        else // not labelled
        {
            values[values_cp] = argv[i];

            values_cp++;
        }
    }

    data->values_len = values_cp;
    if (values_cp > 0)
    {
        data->values = realloc(values, sizeof(char*) * values_cp);
    }
    else
    {
        data->values = NULL;
    }

    data->lv_len = lv_cp;
    if (lv_cp > 0)
    {
        data->lv_labels = realloc(lv_labels, sizeof(char*) * lv_cp);
        data->lv_values = realloc(lv_values, sizeof(char*) * lv_cp);
    }
    else
    {
        data->lv_labels = NULL;
        data->lv_values = NULL;
    }

	data->flags_len = flags_cp;
	if (flags_cp > 0)
	{
		data->flags = realloc(flags, sizeof(char*) * flags_cp);
	}
	else
	{
		data->flags = NULL;
	}

    return data;
}

void carg_parse_free(carg_parse_data* data)
{
    free(data->values);
    free(data->lv_labels);
    free(data->lv_values);
    free(data->flags);

    free(data);
}
