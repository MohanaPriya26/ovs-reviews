/*
 * Copyright (c) 2014 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This header implements RCU primitives using liburcu. */
#ifndef IN_OVS_RCU_H
#error "This header should only be included indirectly via ovs-rcu.h."
#endif

#include <urcu-qsbr.h>

struct ovs_rcuref {
    struct ovs_refcount refcnt;
    struct rcu_head rcu_head;
};

static inline void
ovs_rcuref_init(struct ovs_rcuref *rcuref)
{
    ovs_refcount_init(&rcuref->refcnt);
}

static inline void
ovs_rcuref_destroy(struct ovs_rcuref *rcuref)
{
    ovs_refcount_destroy(&rcuref->refcnt);
}

static inline void
ovs_rcuref_ref(struct ovs_rcuref *rcuref, enum ovs_rcuref_type type)
{
    if (type == OVS_RCUREF_OWNER) {
        ovs_refcount_ref(&rcuref->refcnt);
    } else {
        rcu_read_lock();
    }
}

#define OVS_RCUREF_CONTAINER_OF(RCU_HEAD, STRUCT, MEMBER) \
    CONTAINER_OF(RCU_HEAD, STRUCT, MEMBER.rcu_head)

static inline void
ovs_rcuref_unref(struct ovs_rcuref *rcuref, enum ovs_rcuref_type type,
                 void (*free_cb)(struct rcu_head *))
{
    if (type == OVS_RCUREF_OWNER) {
        if (ovs_refcount_unref(&rcuref->refcnt) == 1) {
            call_rcu(&rcuref->rcu_head, free_cb);
        }
    } else {
        rcu_read_unlock();
    }
}
