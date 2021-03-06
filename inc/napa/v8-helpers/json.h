// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#pragma once

#include <napa/v8-helpers/maybe.h>
#include <napa/v8-helpers/function.h>
#include <napa/v8-helpers/flow.h>

namespace napa {
namespace v8_helpers {
    namespace JSON {
        /// <summary> JSON.stringify </summary>
        /// TODO @asib: Use v8::JSON::Stringify when available
        inline v8::MaybeLocal<v8::String> Stringify(v8::Isolate* isolate, const v8::Local<v8::Value>& value) {
            v8::EscapableHandleScope scope(isolate);
            auto context = isolate->GetCurrentContext();

            auto json = context->Global()
                ->Get(context, v8::String::NewFromUtf8(isolate, "JSON"))
                .ToLocalChecked()->ToObject(context)
                .ToLocalChecked();

            constexpr int argc = 1;
            v8::Local<v8::Value> argv[] = { value };
            return scope.Escape(ToLocal<v8::String>(Call(json, "stringify", argc, argv)));
        }

        /// <summary> JSON.parse </summary>
#if (V8_MINOR_VERSION >= 6)
        inline v8::MaybeLocal<v8::Value> Parse(v8::Local<v8::Context> context, const v8::Local<v8::String>& jsonString) {
            return v8::JSON::Parse(context, jsonString);
        }
#else
        inline v8::MaybeLocal<v8::Value> Parse(const v8::Local<v8::String>& jsonString) {
            return v8::JSON::Parse(jsonString);
        }
#endif
    }
}
}