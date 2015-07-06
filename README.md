# Laço

A better REPL for lua. This was created mainly for luajit because the
default interactive mode, better known as the REPL, was pretty bare
bones. You can't move left or right in the current line if wanted to
edit the line, and there is no history for repeating commands easily.
With laco you can actually do that, and I also believe that that regular
lua REPL can as well.

## Features

* Printing of tables instead of just the table address.

```lua
> {foo=true, bar=42}
{ foo = true
, bar = 42
}
> {1,2,3,4}
{1, 2, 3, 4}
```

* In memory history, so pressing up will go to the previous line.
* Command mode (use `:help` to see the list of commands)

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

**Note**: This is for regular lua, to enable luajit you need to replace.
`cmake ..` with `cmake -DLACO_USE_LUAJIT=on ..`. Also if you are using
anything lua 5.2+, I'm not sure if this will work since I've only tested
on luajit which is currently 5.1

```bash
git clone --recursive https://github.com/sourrust/laco.git
cd laco
mkdir build
cd build
cmake ..
make
```

The binary will be located in `build/bin` and it can be run from there.
