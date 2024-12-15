<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

/**
 * Tells PHP's GC to ignore the given object's dependencies when
 * scanning for reference cycles.
 * This is useful to avoid the performance impact of long-lived complex objects
 * getting scanned for cycles for no good reason.
 *
 * WARNING: If the given object is a member of any cycles, you'll need to
 * destroy the cycles yourself, or the object may not be destroyed.
 *
 * @return bool Returns true if the object has been successfully marked to be ignored by the GC.
 */
function gc_ignore(object $object) : bool{}

/**
 * Reverses the effect of gc_ignore() on an object.
 * If gc_ignore() was never called on the object, this function has no effect.
 */
function gc_unignore(object $object) : void{}

/**
 * Returns whether gc_ignore() has been called with this object.
 */
function gc_is_ignored(object $object) : bool{}
