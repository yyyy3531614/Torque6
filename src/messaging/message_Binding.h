﻿//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "c-interface/c-interface.h"

ConsoleMethodGroupBeginWithDocs(Message, SimObject)

/*! Get message type (script class name or C++ class name if no script defined class)
    @return The type as a string
*/
ConsoleMethodWithDocs(Message, getType, const char *, 2, 2, ())
{
   return object->getType();
}

/*! Increment the reference count for this message
    @return No Return Value.
*/
ConsoleMethodWithDocs(Message, addReference, ConsoleVoid, 2, 2, ())
{
   object->addReference();
}

/*! Decrement the reference count for this message
    @return No Return Value.
*/
ConsoleMethodWithDocs(Message, freeReference, ConsoleVoid, 2, 2, ())
{
   object->freeReference();
}

ConsoleMethodGroupEndWithDocs(Message)

extern "C" {
   DLL_PUBLIC Message* MessageCreateInstance()
   {
      return new Message();
   }

   DLL_PUBLIC const char* MessageGetType(Message* message)
   {
      return CInterface::GetMarshallableString(message->getType());
   }

   DLL_PUBLIC void MessageAddReference(Message* message)
   {
      message->addReference();
   }

   DLL_PUBLIC void MessageFreeReference(Message* message)
   {
      message->freeReference();
   }
}