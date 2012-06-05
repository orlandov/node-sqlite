// Copyright 2011 Mariano Iglesias <mgiglesias@gmail.com>
#ifndef NODE_DEFS_H_
#define NODE_DEFS_H_

#include <node.h>

#define NODE_CONSTANT(constant) v8::Integer::New(constant)

#define NODE_ADD_PROTOTYPE_METHOD(templ, name, callback)                  \
do {                                                                      \
  v8::Local<v8::Signature> __callback##_SIG = v8::Signature::New(templ);  \
  v8::Local<v8::FunctionTemplate> __callback##_TEM =                      \
    v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(),          \
                          __callback##_SIG);                              \
  templ->PrototypeTemplate()->Set(v8::String::NewSymbol(name),            \
                                  __callback##_TEM);                      \
} while (0)

#define NODE_ADD_CONSTANT(target, name, constant)                         \
  (target)->Set(v8::String::NewSymbol(#name),                             \
                v8::Integer::New(constant),                               \
                static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete))

#define THROW_EXCEPTION(message) \
    return v8::ThrowException(v8::Exception::Error(v8::String::New(message)));

#define ARG_CHECK_OPTIONAL_STRING(I, VAR) \
    if (args.Length() > I && !args[I]->IsString()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid string") \
    }

#define ARG_CHECK_STRING(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsString()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid string") \
    }

#define ARG_CHECK_OPTIONAL_BOOL(I, VAR) \
    if (args.Length() > I && !args[I]->IsBoolean()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid boolean") \
    }

#define ARG_CHECK_BOOL(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsBoolean()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid boolean") \
    }

#define ARG_CHECK_OPTIONAL_UINT32(I, VAR) \
    if (args.Length() > I && !args[I]->IsUint32()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid UINT32") \
    }

#define ARG_CHECK_UINT32(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsUint32()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid UINT32") \
    }

#define ARG_CHECK_OPTIONAL_OBJECT(I, VAR) \
    if (args.Length() > I && (!args[I]->IsObject() || args[I]->IsFunction() || args[I]->IsUndefined())) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid object") \
    }

#define ARG_CHECK_OBJECT(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsObject() || args[I]->IsFunction() || args[I]->IsArray() || args[I]->IsDate() || args[I]->IsUndefined()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid object") \
    }

#define ARG_CHECK_OPTIONAL_FUNCTION(I, VAR) \
    if (args.Length() > I && !args[I]->IsFunction()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid function") \
    }

#define ARG_CHECK_FUNCTION(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsFunction()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid function") \
    }

#define ARG_CHECK_OPTIONAL_ARRAY(I, VAR) \
    if (args.Length() > I && !args[I]->IsArray()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid array") \
    }

#define ARG_CHECK_ARRAY(I, VAR) \
    if (args.Length() <= I) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" is mandatory") \
    } else if (!args[I]->IsArray()) { \
        THROW_EXCEPTION("Argument \"" #VAR "\" must be a valid array") \
    }

#define ARG_CHECK_OBJECT_ATTR_STRING(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (!VAR->Has(KEY##_##key)) { \
        THROW_EXCEPTION("Option \"" #KEY "\" is mandatory") \
    } else if (!VAR->Get(KEY##_##key)->IsString()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid string") \
    }

#define ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (VAR->Has(KEY##_##key) && !VAR->Get(KEY##_##key)->IsString()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid string") \
    }

#define ARG_CHECK_OBJECT_ATTR_UINT32(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (!VAR->Has(KEY##_##key)) { \
        THROW_EXCEPTION("Option \"" #KEY "\" is mandatory") \
    } else if (!VAR->Get(KEY##_##key)->IsUint32()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid UINT32") \
    }

#define ARG_CHECK_OBJECT_ATTR_OPTIONAL_UINT32(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (VAR->Has(KEY##_##key) && !VAR->Get(KEY##_##key)->IsUint32()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid UINT32") \
    }

#define ARG_CHECK_OBJECT_ATTR_BOOL(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (!VAR->Has(KEY##_##key)) { \
        THROW_EXCEPTION("Option \"" #KEY "\" is mandatory") \
    } else if (!VAR->Get(KEY##_##key)->IsBoolean()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid boolean") \
    }

#define ARG_CHECK_OBJECT_ATTR_OPTIONAL_BOOL(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (VAR->Has(KEY##_##key) && !VAR->Get(KEY##_##key)->IsBoolean()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid boolean") \
    }

#define ARG_CHECK_OBJECT_ATTR_FUNCTION(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (!VAR->Has(KEY##_##key)) { \
        THROW_EXCEPTION("Option \"" #KEY "\" is mandatory") \
    } else if (!VAR->Get(KEY##_##key)->IsFunction()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid function") \
    }

#define ARG_CHECK_OBJECT_ATTR_OPTIONAL_FUNCTION(VAR, KEY) \
    v8::Local<v8::String> KEY##_##key = v8::String::New("" #KEY ""); \
    if (VAR->Has(KEY##_##key) && !VAR->Get(KEY##_##key)->IsFunction()) { \
        THROW_EXCEPTION("Option \"" #KEY "\" must be a valid function") \
    }

#endif  // NODE_DEFS_H_
