/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:15:51 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/14 19:41:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TIME_H
# define LIBFT_TIME_H

# include "_libft.h"

typedef struct s_tm
{
	S32 second;
	S32 minute;
	S32 hour;
	S32 week_day;
	S32 month_day;
	S32 year_day;
	S32 month;
	S32 year;
}	t_tm;

t_tm	ft_mktime(S64 t);
string	ft_strtime(t_tm *tm);

//https://github.com/jleffler/soq/tree/master/src/libsoq


/* Machine-independent time format */
typedef struct s_time
{
	U64	seconds;		/* Time in whole seconds */
	U64	nanoseconds;	/* Sub-seconds in nanoseconds */
} t_time;

typedef struct s_clock
{
	t_time	t1;			/* Start time */
	t_time	t2;			/* Stop time */
	U8		buffer[24];	/* Buffer for formatting elapsed time */
} t_clock;

extern void									clk_diff(t_time *t1, t_time *t2, long *sec, long *nsec);
extern void									clk_init(t_clock *clk);
extern void									clk_start(t_clock *clk);
extern void									clk_stop(t_clock *clk);

__attribute__ ((deprecated)) extern string	clk_elapsed_ms(t_clock *clk, string buffer, U64 buflen);
__attribute__ ((deprecated)) extern string	clk_elapsed_us(t_clock *clk, string buffer, U64 buflen);
__attribute__ ((deprecated)) extern string	clk_elapsed_ns(t_clock *clk, string buffer, U64 buflen);

#  ifndef TIMER_VERSION_1
/* Preferred */
extern string								clk_fmt_elapsed_ms(t_clock *clk);
extern string								clk_fmt_elapsed_us(t_clock *clk);
extern string								clk_fmt_elapsed_ns(t_clock *clk);
extern string								clk_fmt_elapsed_str(t_clock *clk);
extern double								clk_fmt_elapsed_dbl(t_clock *clk);
#  endif /*#  ifndef TIMER_VERSION_1*/

#endif