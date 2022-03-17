#pragma once
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/** Functions to manipulate DNS labels
 *
 * @file src/lib/util/dns.h
 *
 * @copyright 2019 Network RADIUS SARL (legal@networkradius.com)
 */
RCSIDH(dns_h, "$Id$")

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint16_t	start;
	uint16_t	end;
} fr_dns_block_t;

typedef struct {
	uint8_t const	*start;		//!< start of packet
	uint8_t const	*end;		//!< end of the packet
	uint8_t		*mark;		//!< markup buffer used for decoding.
	int		num;		//!< number of used labels
	int		max;		//! maximum number of labels
	fr_dns_block_t	*blocks;	//!< array holding "max" labels
} fr_dns_labels_t;

ssize_t		fr_dns_label_from_value_box(size_t *need, uint8_t *buf, size_t buflen, uint8_t *where, bool compression, fr_value_box_t const *value, fr_dns_labels_t *lb);

ssize_t		fr_dns_label_from_value_box_dbuff(fr_dbuff_t *dbuff, bool compression, fr_value_box_t const *value, fr_dns_labels_t *lb);

ssize_t		fr_dns_label_uncompressed_length(uint8_t const *packet, uint8_t const *buf, size_t buf_len, uint8_t const **p_label, fr_dns_labels_t *lb);

ssize_t		fr_dns_labels_network_verify(uint8_t const *packet, uint8_t const *buf, size_t buf_len, uint8_t const *start, fr_dns_labels_t *lb) CC_HINT(nonnull(1,2,4));

ssize_t		fr_dns_label_to_value_box(TALLOC_CTX *ctx, fr_value_box_t *dst,
					    uint8_t const *src, size_t len, uint8_t const *label,
					    bool tainted, fr_dns_labels_t *lb);

#ifdef __cplusplus
}
#endif
