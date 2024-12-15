--TEST--
Test basic usage
--FILE--
<?php

class Test{
    public Test $t2;
}

$test = new Test();
$test2 = new Test();
$test->t2 = $test2;
$test2->t2 = $test;
var_dump(gc_ignore($test));

$wr = WeakReference::create($test);

unset($test, $test2);
echo "no cycles can be collected: " . gc_collect_cycles() . "\n";

echo "weakref should still be alive\n";
$test = $wr->get();
var_dump($test !== null);
var_dump(gc_is_ignored($test)); //true

gc_unignore($test);

echo "object should no longer be ignored\n";
var_dump(gc_is_ignored($test)); //false
unset($test); //$test now goes into the GC root buffer
echo "cycles can now be collected: " . gc_collect_cycles() . "\n";

$test = $wr->get();
echo "weakref should now be dead\n";
var_dump($test === null); //true, both objects have been deleted
?>
--EXPECT--
bool(true)
no cycles can be collected: 0
weakref should still be alive
bool(true)
bool(true)
object should no longer be ignored
bool(false)
cycles can now be collected: 2
weakref should now be dead
bool(true)
