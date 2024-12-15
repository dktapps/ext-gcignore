# ext-gcignore

This extension provides functions that make the PHP GC ignore a particular object's dependencies.

## Why?

In recent PocketMine-MP development, I discovered that, as a heavily used object, `Server` frequently landed in the GC root buffer, despite being a long-lived object that can't be garbage-collected anyway.
This is because objects in PHP get marked for GC scanning when their refcount decreases to some value above 0.

This happens in basically every interaction with an object, meaning that frequently-used objects will basically always get scanned for GC cycles, even though they can't be deleted anyway.

This gets even worse when complex objects are indirectly referenced by other frequently-used objects, as the costs merge together.

For example, PocketMine-MP `World` is, by itself, somewhat less costly to examine than `Server`. However, since `World` contains a reference to `Server`, all of `Server`'s dependencies will get recursively scanned whenever a `World` is unref'd, which _also_ happens frequently.

## How to use

I recommend using `gc_ignore()` on any object that has:
- Lots of descendent objects
- References any object that has lots of descendents
- Singletons

## How does it work?

`gc_ignore()` overrides `zend_object->handlers` for the provided object with a custom `get_gc` handler that returns dummy data for the GC to look at.

**Out of an abundance of caution, the extension currently only permits this modification for objects which have standard Zend object handlers.**
This means that many extensions' classes can't be altered, but extension classes are usually simple anyway, and so aren't expected to benefit from this treatment anyway.

## API
- `gc_ignore(object $object) : bool` - marks an object to prevent GC from looking at its properties; returns `false` and emits a warning if the object can't be ignored
- `gc_unignore(object $object) : void` - reverses changes made by `gc_ignore()` on an object; does nothing if the object was not ignored
- `gc_is_ignored(object $object) : bool` - returns whether `gc_ignore()` made changes to the object
