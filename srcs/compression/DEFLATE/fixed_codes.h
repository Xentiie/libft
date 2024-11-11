#if !defined(FT_INFLATE_FIXED_CODES_H)
#define FT_INFLATE_FIXED_CODES_H
#include "libft/compression/deflate.h"

static const struct s_code fixed_ll_codes[] = {
	{32, 7, 0}, {128, 8, 80}, {128, 8, 16}, {68, 8, 115}, {66, 7, 31}, {128, 8, 112}, {128, 8, 48}, {128, 9, 192}, {64, 7, 10}, {128, 8, 96}, 
	{128, 8, 32}, {128, 9, 160}, {128, 8, 0}, {128, 8, 128}, {128, 8, 64}, {128, 9, 224}, {64, 7, 6}, {128, 8, 88}, {128, 8, 24}, {128, 9, 144}, 
	{67, 7, 59}, {128, 8, 120}, {128, 8, 56}, {128, 9, 208}, {65, 7, 17}, {128, 8, 104}, {128, 8, 40}, {128, 9, 176}, {128, 8, 8}, {128, 8, 136}, 
	{128, 8, 72}, {128, 9, 240}, {64, 7, 4}, {128, 8, 84}, {128, 8, 20}, {69, 8, 227}, {67, 7, 43}, {128, 8, 116}, {128, 8, 52}, {128, 9, 200}, 
	{65, 7, 13}, {128, 8, 100}, {128, 8, 36}, {128, 9, 168}, {128, 8, 4}, {128, 8, 132}, {128, 8, 68}, {128, 9, 232}, {64, 7, 8}, {128, 8, 92}, 
	{128, 8, 28}, {128, 9, 152}, {68, 7, 83}, {128, 8, 124}, {128, 8, 60}, {128, 9, 216}, {66, 7, 23}, {128, 8, 108}, {128, 8, 44}, {128, 9, 184}, 
	{128, 8, 12}, {128, 8, 140}, {128, 8, 76}, {128, 9, 248}, {64, 7, 3}, {128, 8, 82}, {128, 8, 18}, {69, 8, 163}, {67, 7, 35}, {128, 8, 114}, 
	{128, 8, 50}, {128, 9, 196}, {65, 7, 11}, {128, 8, 98}, {128, 8, 34}, {128, 9, 164}, {128, 8, 2}, {128, 8, 130}, {128, 8, 66}, {128, 9, 228}, 
	{64, 7, 7}, {128, 8, 90}, {128, 8, 26}, {128, 9, 148}, {68, 7, 67}, {128, 8, 122}, {128, 8, 58}, {128, 9, 212}, {66, 7, 19}, {128, 8, 106}, 
	{128, 8, 42}, {128, 9, 180}, {128, 8, 10}, {128, 8, 138}, {128, 8, 74}, {128, 9, 244}, {64, 7, 5}, {128, 8, 86}, {128, 8, 22}, {64, 8, 0}, 
	{67, 7, 51}, {128, 8, 118}, {128, 8, 54}, {128, 9, 204}, {65, 7, 15}, {128, 8, 102}, {128, 8, 38}, {128, 9, 172}, {128, 8, 6}, {128, 8, 134}, 
	{128, 8, 70}, {128, 9, 236}, {64, 7, 9}, {128, 8, 94}, {128, 8, 30}, {128, 9, 156}, {68, 7, 99}, {128, 8, 126}, {128, 8, 62}, {128, 9, 220}, 
	{66, 7, 27}, {128, 8, 110}, {128, 8, 46}, {128, 9, 188}, {128, 8, 14}, {128, 8, 142}, {128, 8, 78}, {128, 9, 252}, {32, 7, 0}, {128, 8, 81}, 
	{128, 8, 17}, {69, 8, 131}, {66, 7, 31}, {128, 8, 113}, {128, 8, 49}, {128, 9, 194}, {64, 7, 10}, {128, 8, 97}, {128, 8, 33}, {128, 9, 162}, 
	{128, 8, 1}, {128, 8, 129}, {128, 8, 65}, {128, 9, 226}, {64, 7, 6}, {128, 8, 89}, {128, 8, 25}, {128, 9, 146}, {67, 7, 59}, {128, 8, 121}, 
	{128, 8, 57}, {128, 9, 210}, {65, 7, 17}, {128, 8, 105}, {128, 8, 41}, {128, 9, 178}, {128, 8, 9}, {128, 8, 137}, {128, 8, 73}, {128, 9, 242}, 
	{64, 7, 4}, {128, 8, 85}, {128, 8, 21}, {64, 8, 258}, {67, 7, 43}, {128, 8, 117}, {128, 8, 53}, {128, 9, 202}, {65, 7, 13}, {128, 8, 101}, 
	{128, 8, 37}, {128, 9, 170}, {128, 8, 5}, {128, 8, 133}, {128, 8, 69}, {128, 9, 234}, {64, 7, 8}, {128, 8, 93}, {128, 8, 29}, {128, 9, 154}, 
	{68, 7, 83}, {128, 8, 125}, {128, 8, 61}, {128, 9, 218}, {66, 7, 23}, {128, 8, 109}, {128, 8, 45}, {128, 9, 186}, {128, 8, 13}, {128, 8, 141}, 
	{128, 8, 77}, {128, 9, 250}, {64, 7, 3}, {128, 8, 83}, {128, 8, 19}, {69, 8, 195}, {67, 7, 35}, {128, 8, 115}, {128, 8, 51}, {128, 9, 198}, 
	{65, 7, 11}, {128, 8, 99}, {128, 8, 35}, {128, 9, 166}, {128, 8, 3}, {128, 8, 131}, {128, 8, 67}, {128, 9, 230}, {64, 7, 7}, {128, 8, 91}, 
	{128, 8, 27}, {128, 9, 150}, {68, 7, 67}, {128, 8, 123}, {128, 8, 59}, {128, 9, 214}, {66, 7, 19}, {128, 8, 107}, {128, 8, 43}, {128, 9, 182}, 
	{128, 8, 11}, {128, 8, 139}, {128, 8, 75}, {128, 9, 246}, {64, 7, 5}, {128, 8, 87}, {128, 8, 23}, {64, 8, 0}, {67, 7, 51}, {128, 8, 119}, 
	{128, 8, 55}, {128, 9, 206}, {65, 7, 15}, {128, 8, 103}, {128, 8, 39}, {128, 9, 174}, {128, 8, 7}, {128, 8, 135}, {128, 8, 71}, {128, 9, 238}, 
	{64, 7, 9}, {128, 8, 95}, {128, 8, 31}, {128, 9, 158}, {68, 7, 99}, {128, 8, 127}, {128, 8, 63}, {128, 9, 222}, {66, 7, 27}, {128, 8, 111}, 
	{128, 8, 47}, {128, 9, 190}, {128, 8, 15}, {128, 8, 143}, {128, 8, 79}, {128, 9, 254}, {32, 7, 0}, {128, 8, 80}, {128, 8, 16}, {68, 8, 115}, 
	{66, 7, 31}, {128, 8, 112}, {128, 8, 48}, {128, 9, 193}, {64, 7, 10}, {128, 8, 96}, {128, 8, 32}, {128, 9, 161}, {128, 8, 0}, {128, 8, 128}, 
	{128, 8, 64}, {128, 9, 225}, {64, 7, 6}, {128, 8, 88}, {128, 8, 24}, {128, 9, 145}, {67, 7, 59}, {128, 8, 120}, {128, 8, 56}, {128, 9, 209}, 
	{65, 7, 17}, {128, 8, 104}, {128, 8, 40}, {128, 9, 177}, {128, 8, 8}, {128, 8, 136}, {128, 8, 72}, {128, 9, 241}, {64, 7, 4}, {128, 8, 84}, 
	{128, 8, 20}, {69, 8, 227}, {67, 7, 43}, {128, 8, 116}, {128, 8, 52}, {128, 9, 201}, {65, 7, 13}, {128, 8, 100}, {128, 8, 36}, {128, 9, 169}, 
	{128, 8, 4}, {128, 8, 132}, {128, 8, 68}, {128, 9, 233}, {64, 7, 8}, {128, 8, 92}, {128, 8, 28}, {128, 9, 153}, {68, 7, 83}, {128, 8, 124}, 
	{128, 8, 60}, {128, 9, 217}, {66, 7, 23}, {128, 8, 108}, {128, 8, 44}, {128, 9, 185}, {128, 8, 12}, {128, 8, 140}, {128, 8, 76}, {128, 9, 249}, 
	{64, 7, 3}, {128, 8, 82}, {128, 8, 18}, {69, 8, 163}, {67, 7, 35}, {128, 8, 114}, {128, 8, 50}, {128, 9, 197}, {65, 7, 11}, {128, 8, 98}, 
	{128, 8, 34}, {128, 9, 165}, {128, 8, 2}, {128, 8, 130}, {128, 8, 66}, {128, 9, 229}, {64, 7, 7}, {128, 8, 90}, {128, 8, 26}, {128, 9, 149}, 
	{68, 7, 67}, {128, 8, 122}, {128, 8, 58}, {128, 9, 213}, {66, 7, 19}, {128, 8, 106}, {128, 8, 42}, {128, 9, 181}, {128, 8, 10}, {128, 8, 138}, 
	{128, 8, 74}, {128, 9, 245}, {64, 7, 5}, {128, 8, 86}, {128, 8, 22}, {64, 8, 0}, {67, 7, 51}, {128, 8, 118}, {128, 8, 54}, {128, 9, 205}, 
	{65, 7, 15}, {128, 8, 102}, {128, 8, 38}, {128, 9, 173}, {128, 8, 6}, {128, 8, 134}, {128, 8, 70}, {128, 9, 237}, {64, 7, 9}, {128, 8, 94}, 
	{128, 8, 30}, {128, 9, 157}, {68, 7, 99}, {128, 8, 126}, {128, 8, 62}, {128, 9, 221}, {66, 7, 27}, {128, 8, 110}, {128, 8, 46}, {128, 9, 189}, 
	{128, 8, 14}, {128, 8, 142}, {128, 8, 78}, {128, 9, 253}, {32, 7, 0}, {128, 8, 81}, {128, 8, 17}, {69, 8, 131}, {66, 7, 31}, {128, 8, 113}, 
	{128, 8, 49}, {128, 9, 195}, {64, 7, 10}, {128, 8, 97}, {128, 8, 33}, {128, 9, 163}, {128, 8, 1}, {128, 8, 129}, {128, 8, 65}, {128, 9, 227}, 
	{64, 7, 6}, {128, 8, 89}, {128, 8, 25}, {128, 9, 147}, {67, 7, 59}, {128, 8, 121}, {128, 8, 57}, {128, 9, 211}, {65, 7, 17}, {128, 8, 105}, 
	{128, 8, 41}, {128, 9, 179}, {128, 8, 9}, {128, 8, 137}, {128, 8, 73}, {128, 9, 243}, {64, 7, 4}, {128, 8, 85}, {128, 8, 21}, {64, 8, 258}, 
	{67, 7, 43}, {128, 8, 117}, {128, 8, 53}, {128, 9, 203}, {65, 7, 13}, {128, 8, 101}, {128, 8, 37}, {128, 9, 171}, {128, 8, 5}, {128, 8, 133}, 
	{128, 8, 69}, {128, 9, 235}, {64, 7, 8}, {128, 8, 93}, {128, 8, 29}, {128, 9, 155}, {68, 7, 83}, {128, 8, 125}, {128, 8, 61}, {128, 9, 219}, 
	{66, 7, 23}, {128, 8, 109}, {128, 8, 45}, {128, 9, 187}, {128, 8, 13}, {128, 8, 141}, {128, 8, 77}, {128, 9, 251}, {64, 7, 3}, {128, 8, 83}, 
	{128, 8, 19}, {69, 8, 195}, {67, 7, 35}, {128, 8, 115}, {128, 8, 51}, {128, 9, 199}, {65, 7, 11}, {128, 8, 99}, {128, 8, 35}, {128, 9, 167}, 
	{128, 8, 3}, {128, 8, 131}, {128, 8, 67}, {128, 9, 231}, {64, 7, 7}, {128, 8, 91}, {128, 8, 27}, {128, 9, 151}, {68, 7, 67}, {128, 8, 123}, 
	{128, 8, 59}, {128, 9, 215}, {66, 7, 19}, {128, 8, 107}, {128, 8, 43}, {128, 9, 183}, {128, 8, 11}, {128, 8, 139}, {128, 8, 75}, {128, 9, 247}, 
	{64, 7, 5}, {128, 8, 87}, {128, 8, 23}, {64, 8, 0}, {67, 7, 51}, {128, 8, 119}, {128, 8, 55}, {128, 9, 207}, {65, 7, 15}, {128, 8, 103}, 
	{128, 8, 39}, {128, 9, 175}, {128, 8, 7}, {128, 8, 135}, {128, 8, 71}, {128, 9, 239}, {64, 7, 9}, {128, 8, 95}, {128, 8, 31}, {128, 9, 159}, 
	{68, 7, 99}, {128, 8, 127}, {128, 8, 63}, {128, 9, 223}, {66, 7, 27}, {128, 8, 111}, {128, 8, 47}, {128, 9, 191}, {128, 8, 15}, {128, 8, 143}, 
	{128, 8, 79}, {128, 9, 255}, 
};
static const struct s_code fixed_dist_codes[] = {
	{128, 5, 1}, {135, 5, 257}, {131, 5, 17}, {139, 5, 4097}, {129, 5, 5}, {137, 5, 1025}, {133, 5, 65}, {141, 5, 16385}, {128, 5, 3}, {136, 5, 513}, 
	{132, 5, 33}, {140, 5, 8193}, {130, 5, 9}, {138, 5, 2049}, {134, 5, 129}, {128, 5, 0}, {128, 5, 2}, {135, 5, 385}, {131, 5, 25}, {139, 5, 6145}, 
	{129, 5, 7}, {137, 5, 1537}, {133, 5, 97}, {141, 5, 24577}, {128, 5, 4}, {136, 5, 769}, {132, 5, 49}, {140, 5, 12289}, {130, 5, 13}, {138, 5, 3073}, 
	{134, 5, 193}, {128, 5, 0}, 
};
#endif
