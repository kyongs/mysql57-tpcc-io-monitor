/*
 Copyright (c) 2012, Oracle and/or its affiliates. All rights
 reserved.
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License, version 2.0,
 as published by the Free Software Foundation.

 This program is also distributed with certain software (including
 but not limited to OpenSSL) that is licensed under separate terms,
 as designated in a particular file or component or in included license
 documentation.  The authors of MySQL hereby grant you an additional
 permission to link the program and your derivative works with the
 separately licensed software that they have included with MySQL.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License, version 2.0, for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301  USA
*/

#include "NdbWrappers.h"

using v8::Arguments;

class NdbNativeCodeError : public NativeCodeError {
public:
  const NdbError & ndberr;
  NdbNativeCodeError(const NdbError &err) : NativeCodeError(0), ndberr(err)  {}
    
  Local<Value> toJS() {
    HandleScope scope;
    Local<String> JSMsg = String::New(ndberr.message);
    Local<Object> Obj = Exception::Error(JSMsg)->ToObject();
    Obj->Set(String::NewSymbol("ndb_error"), NdbError_Wrapper(ndberr));

    return scope.Close(Obj);
  }
};


template<typename R, typename C> 
NativeCodeError * getNdbErrorIfNull(R return_val, C * ndbapiobject) {
  NativeCodeError *err = 0;
  
  if(return_val == 0) {
    err = new NdbNativeCodeError(ndbapiobject->getNdbError());
  }
  
  return err;
};


template<typename R, typename C> 
NativeCodeError * getNdbErrorIfLessThanZero(R return_val, C * ndbapiobject) {
  NativeCodeError *err = 0;
  
  if(return_val < 0) {
    err = new NdbNativeCodeError(ndbapiobject->getNdbError());
  }
  
  return err;
};


template<typename R, typename C> 
NativeCodeError * getNdbErrorAlways(R return_val, C * ndbApiObject) {

  return new NdbNativeCodeError(ndbApiObject->getNdbError());
};


template<typename C> 
Handle<Value> getNdbError(const Arguments &args) {
  C * ndbApiObject = unwrapPointer<C *>(args.Holder());
  const NdbError & ndberr = ndbApiObject->getNdbError();
  return NdbError_Wrapper(ndberr);
};
