// Copyright 2011 Mariano Iglesias <mgiglesias@gmail.com>
#include "./events.h"

node_db::EventEmitter::EventEmitter() : node::ObjectWrap() {
}

void node_db::EventEmitter::Init() {
}

bool node_db::EventEmitter::Emit(const char* event, int argc, v8::Handle<v8::Value> argv[]) {
    v8::HandleScope scope;

    int nArgc = argc + 1;
    v8::Handle<v8::Value>* nArgv = new v8::Handle<v8::Value>[nArgc];
    if (nArgv == NULL) {
        return false;
    }

    nArgv[0] = v8::String::New(event);
    for (int i=0; i < argc; i++) {
        nArgv[i + 1] = argv[i];
    }

    node::MakeCallback(this->handle_, "emit", nArgc, nArgv);

    delete [] nArgv;

    return true;
}
