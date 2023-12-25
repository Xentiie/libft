#include "libft.h"

t_error_code		ft_errno;
const_string		ft_error_lookup_table[] = { //TODO
	"SUCCESS",
	"FT_ERROR",
	"FT_OMEM",
	"FT_BAD_FD",
	"FT_MAP_FULL",
	"FT_MAP_MISSING",
};