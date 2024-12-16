#include "libft/maths.h"

F32 rand_range(F32 min, F32 max, S32 *seed)
{
	return ft_frand((*seed)++) * (max - min) + min;
}

