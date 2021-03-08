// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include <utility>
#include <string>
#include <string_view>
#include <map>

#include "zeek/Obj.h"
#include "zeek/ZeekList.h"
#include "zeek/IntrusivePtr.h"
#include "zeek/TraverseTypes.h"

ZEEK_FORWARD_DECLARE_NAMESPACED(Type, zeek);
using BroType [[deprecated("Remove in v4.1. Use zeek::Type instead.")]] = zeek::Type;

ZEEK_FORWARD_DECLARE_NAMESPACED(ID, zeek::detail);
ZEEK_FORWARD_DECLARE_NAMESPACED(Attr, zeek::detail);

namespace zeek {

template <class T> class IntrusivePtr;
using TypePtr = IntrusivePtr<Type>;

namespace detail {

using AttrPtr = IntrusivePtr<Attr>;
using IDPtr = IntrusivePtr<ID>;

class Scope;
using ScopePtr = IntrusivePtr<Scope>;

class Scope : public Obj {
public:
	explicit Scope(IDPtr id,
	               std::unique_ptr<std::vector<AttrPtr>> al);

	const IDPtr& Find(std::string_view name) const;

	template<typename N>
	[[deprecated("Remove in v4.1.  Use Find().")]]
	ID* Lookup(N&& name) const
		{ return Find(name).get(); }

	template<typename N, typename I>
	void Insert(N&& name, I&& id) { local[std::forward<N>(name)] = std::forward<I>(id); }

	IDPtr Remove(std::string_view name);

	[[deprecated("Remove in v4.1.  Use GetID().")]]
	ID* ScopeID() const		{ return scope_id.get(); }

	const IDPtr& GetID() const
		{ return scope_id; }

	const std::unique_ptr<std::vector<AttrPtr>>& Attrs() const
		{ return attrs; }

	[[deprecated("Remove in v4.1.  Use GetReturnTrype().")]]
	Type* ReturnType() const	{ return return_type.get(); }

	const TypePtr& GetReturnType() const
		{ return return_type; }

	size_t Length() const		{ return local.size(); }
	const auto& Vars()	{ return local; }

	IDPtr GenerateTemporary(const char* name);

	// Returns the list of variables needing initialization, and
	// removes it from this Scope.
	std::vector<IDPtr> GetInits();

	// Adds a variable to the list.
	void AddInit(IDPtr id)
		{ inits.emplace_back(std::move(id)); }

	void Describe(ODesc* d) const override;

	TraversalCode Traverse(TraversalCallback* cb) const;

protected:
	IDPtr scope_id;
	std::unique_ptr<std::vector<AttrPtr>> attrs;
	TypePtr return_type;
	std::map<std::string, IDPtr, std::less<>> local;
	std::vector<IDPtr> inits;
};

// If no_global is true, don't search in the default "global" namespace.
extern const IDPtr& lookup_ID(
	const char* name, const char* module,
	bool no_global = false,
	bool same_module_only = false,
	bool check_export = true);

extern IDPtr install_ID(
	const char* name, const char* module_name,
	bool is_global, bool is_export);

extern void push_scope(IDPtr id, std::unique_ptr<std::vector<AttrPtr>> attrs);
extern void push_existing_scope(Scope* scope);

// Returns the one popped off.
extern ScopePtr pop_scope();
extern Scope* current_scope();
extern Scope* global_scope();

// Current module (identified by its name).
extern std::string current_module;

} // namespace detail
} // namespace zeek

extern bool in_debug;

using Scope [[deprecated("Remove in v4.1. Use zeek::detail::Scope instead.")]] = zeek::detail::Scope;
extern std::string& current_module [[deprecated("Remove in v4.1. Use zeek::detail::current_module.")]];

constexpr auto install_ID [[deprecated("Remove in v4.1 Use zeek::detail::install_ID instead.")]] = zeek::detail::install_ID;
constexpr auto push_scope [[deprecated("Remove in v4.1 Use zeek::detail::push_scope instead.")]] = zeek::detail::push_scope;
constexpr auto push_existing_scope[[deprecated("Remove in v4.1 Use zeek::detail::push_existing_scope instead.")]] = zeek::detail::push_existing_scope;
constexpr auto pop_scope [[deprecated("Remove in v4.1 Use zeek::detail::pop_scope instead.")]] = zeek::detail::pop_scope;
constexpr auto current_scope [[deprecated("Remove in v4.1 Use zeek::detail::current_scope instead.")]] = zeek::detail::current_scope;
constexpr auto global_scope [[deprecated("Remove in v4.1 Use zeek::detail::global_scope instead.")]] = zeek::detail::global_scope;

// Because of the use of default arguments, this function can't be aliased like the rest.
[[deprecated("Remove in v4.1 Use zeek::detail::lookup_ID instead.")]]
extern zeek::detail::ID* lookup_ID(
	const char* name, const char* module,
	bool no_global = false,
	bool same_module_only = false,
	bool check_export = true);
