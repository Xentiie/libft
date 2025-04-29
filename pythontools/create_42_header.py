# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    create_42_header.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 19:45:50 by reclaire          #+#    #+#              #
#    Updated: 2025/04/22 19:46:06 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import datetime

def create_42_header(path:str, username:str, email:str):
	h = """/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {filena}        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: {username_email}    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: {created}       #+#    #+#             */
/*   Updated: {updated}      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

"""

	with open(path, "r") as f:
		existing_header = f.read(980)
		has_header = (existing_header.startswith(h, 0, 414)
			and existing_header.startswith(h, 453, 581)
			and existing_header.startswith(h, 615, 662)
			and existing_header.startswith(h, 696, 890))

	filename = os.path.basename(path)[:43].ljust(43)
	username_email = f"{username} <{email}>"[:39].ljust(39)
	username = username[:11].ljust(11)

	stat = os.stat(path)
	tz = datetime.datetime.now(datetime.timezone.utc).astimezone().tzinfo

	if (has_header):
		created = existing_header[581:615]
	else:
		date_str = datetime.datetime.fromtimestamp(stat.st_ctime, tz=tz).strftime('%Y/%m/%d %H:%M:%S')
		created = f"{date_str} by {username}"

	date_str = datetime.datetime.fromtimestamp(stat.st_mtime, tz=tz).strftime('%Y/%m/%d %H:%M:%S')
	updated = f"{date_str} by {username}"

	return h.format(
	filena=filename,
	username_email=username_email,
	created=created,
	updated=updated)