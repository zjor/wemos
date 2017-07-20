#include <stdio.h>
#include "fw/src/mgos.h"
#include "mongoose/mongoose.h"

#include "common/platform.h"
#include "fw/src/mgos_app.h"
#include "fw/src/mgos_gpio.h"
#include "fw/src/mgos_mongoose.h"
#include "fw/src/mgos_sys_config.h"

static uint32_t s_our_ip_addr;
static const char *s_listening_addr = "udp://:53";

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data, void *user_data) {
    struct mg_dns_message *msg;
    struct mg_dns_resource_record *rr;
    struct mg_dns_reply reply;
    int i;

    switch (ev) {
        case MG_DNS_MESSAGE: {
            struct mbuf reply_buf;
            mbuf_init(&reply_buf, 512);
            msg = (struct mg_dns_message *) ev_data;
            reply = mg_dns_create_reply(&reply_buf, msg);

            for (i = 0; i < msg->num_questions; i++) {
                char rname[256];
                rr = &msg->questions[i];
                mg_dns_uncompress_name(msg, &rr->name, rname, sizeof(rname) - 1);
                fprintf(stdout, "Q type %d name %s\n", rr->rtype, rname);
                if (rr->rtype == MG_DNS_A_RECORD) {
                    mg_dns_reply_record(&reply, rr, NULL, rr->rtype, 10, &s_our_ip_addr,
                                        4);
                }
            }

            /*
             * We don't set the error flag even if there were no answers
             * matching the MG_DNS_A_RECORD query type.
             * This indicates that we have (synthetic) answers for MG_DNS_A_RECORD.
             * See http://goo.gl/QWvufr for a distinction between NXDOMAIN and NODATA.
             */

            mg_dns_send_reply(nc, &reply);
            nc->flags |= MG_F_SEND_AND_CLOSE;
            mbuf_free(&reply_buf);
            break;
        }
    }
    (void) user_data;
}

enum mgos_app_init_result mgos_app_init(void) {
    struct mg_mgr *mgr;

    s_our_ip_addr = inet_addr("192.168.4.1");

    mgr = mgos_get_mgr();

    struct mg_bind_opts bopts;
    memset(&bopts, 0, sizeof(bopts));

    struct mg_connection *lc = mg_bind_opt(mgr, s_listening_addr, ev_handler, NULL, bopts);
    mg_set_protocol_dns(lc);

    if (lc == NULL) {
        LOG(LL_ERROR, ("Failed to initialize DNS listener"));
        return MGOS_APP_INIT_ERROR;
    } else {
        LOG(LL_INFO, ("Listening on %s", s_listening_addr));
    }

    return MGOS_APP_INIT_SUCCESS;
}
