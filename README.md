# Laço

A better REPL for lua. This was mainly for luajit because the default
interactive mode, ie. the REPL, was pretty bad. You couldn't move back
and forth in the to edit, and no going through history. With laco you
can actually do that, and I also believe that that regular lua can as
well.

## Features

Printing of tables instead of just the table address.

```lua
> {foo=true, bar=42}
{ foo = true
, bar = 42
}
> {1,2,3,4}
{1,2,3,4}
```

This is still in early development so there isn't much so far, but I
think its enough to use a replacement (atleast for luajit users).

## Laço?

In Portuguese, laco mean loop and since Lua is a Portuguese name and a
REPL is a read eval print loop, the name was born.

## Building

Since laco depends on [linenoise](https://github.com/antirez/linenoise#tested-with),
I don't think this will work for Windows terminals, but nevertheless,
here are the step on building.

**Denpendencies (not included):**

* cmake
* Lua or Luajit

```bash
mkdir build
cd build
cmake ..
make
```

The binary will be located in `build/bin` and it can be run from there.