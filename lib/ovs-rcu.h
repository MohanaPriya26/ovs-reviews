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

#ifndef OVS_RCU_H
#define OVS_RCU_H 1

#include "compiler.h"
#include "ovs-atomic.h"

enum ovs_rcuref_type {
    OVS_RCUREF_OWNER,
    OVS_RCUREF_NOTOWNER
};

#define IN_OVS_RCU_H
#ifdef HAVE_LIBURCU
#include "ovs-rcu-liburcu.h"
#else
#include "ovs-rcu-norcu.h"
#endif
#undef IN_OVS_RCU_H

#endif /* ovs-rcu.h */
