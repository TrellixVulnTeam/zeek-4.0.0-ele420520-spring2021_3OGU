// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "zeek-config.h"

ZEEK_FORWARD_DECLARE_NAMESPACED(TraversalCallback, zeek::detail);

namespace zeek::detail {

enum TraversalCode {
	TC_CONTINUE = 0,
	TC_ABORTALL = 1,
	TC_ABORTSTMT = 2,
};

#define HANDLE_TC_STMT_PRE(code) \
	{ \
	if ( (code) == zeek::detail::TC_ABORTALL || (code) == zeek::detail::TC_ABORTSTMT ) \
		return (code); \
	}

#define HANDLE_TC_STMT_POST(code) \
	{ \
	if ( (code) == zeek::detail::TC_ABORTALL ) \
		return (code); \
	else if ( (code) == zeek::detail::TC_ABORTSTMT ) \
		return zeek::detail::TC_CONTINUE; \
	else \
		return (code); \
	}

#define HANDLE_TC_EXPR_PRE(code) \
	{ \
	if ( (code) != zeek::detail::TC_CONTINUE ) \
		return (code); \
	}

#define HANDLE_TC_EXPR_POST(code) \
	return (code);

} // namespace zeek::detail

using TraversalCode [[deprecated("Remove in v4.1. Use zeek::detail::TraversalCode.")]] = zeek::detail::TraversalCode;
constexpr auto TC_CONTINUE [[deprecated("Remove in v4.1. Use zeek::detail::TC_CONTINUE.")]] = zeek::detail::TC_CONTINUE;
constexpr auto TC_ABORTALL [[deprecated("Remove in v4.1. Use zeek::detail::TC_ABORTALL.")]] = zeek::detail::TC_ABORTALL;
constexpr auto TC_ABORTSTMT [[deprecated("Remove in v4.1. Use zeek::detail::TC_ABORTSTMT.")]] = zeek::detail::TC_ABORTSTMT;
