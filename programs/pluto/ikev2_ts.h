/* IKEv2 Traffic Selectors, for libreswan
 *
 * Copyright (C) 2018  Andrew cagney
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <https://www.gnu.org/licenses/gpl2.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef IKEV2_TS_H
#define IKEV2_TS_H

#include "ip_range.h"
#include "packet.h"	/* for pb_stream */

struct msg_digest;
struct traffic_selector;
struct end;
struct connection;
struct child_sa;
struct state;

/* IKEv2, this struct will be mapped into a ikev2_ts1 payload  */
struct traffic_selector {
	uint8_t ts_type;
	uint8_t ipprotoid;
	uint16_t startport;
	uint16_t endport;
	ip_range net;	/* for now, always happens to be a CIDR */
};

void ikev2_print_ts(const struct traffic_selector *ts);
stf_status ikev2_process_ts_respnse(struct msg_digest *md);
struct traffic_selector ikev2_end_to_ts(const struct end *e);
stf_status ikev2_emit_ts_payloads(const struct child_sa *cst,
				  pb_stream *outpbs,
				  enum sa_role role,
				  const struct connection *c0,
				  const enum next_payload_types_ikev2 np);
stf_status ikev2_resp_accept_child_ts(const struct msg_digest *md,
				      struct state **ret_cst,
				      enum original_role role, enum
				      isakmp_xchg_types isa_xchg);

#endif
