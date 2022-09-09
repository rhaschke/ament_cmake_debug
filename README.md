## Dependency tree

`package_d` -> `package_c`

`package_c` -> `package_a`, `package_b`

## Reproduction steps

To reproduce the dependency issue, build an underlay workspace with `--merge-install` (That's the default for `/opt/ros`):

        cd underlay
        colcon build --merge-install

Source the underlay and build the overlay

        source install/setup.bash
        cd ../overlay
        colcon build

Expect a compiler error due to an undeclared function `package_a_foo_renamed`.

## Explanation

`package_a` exists in both the underlay and overlay, with a modified version in the overlay.
`package_c` depends on the modified version of `package_a` (in the overlay) and `package_b` in the underlay.
`package_d` depends on `package_c` and transitively on `package_a` and `package_b`.

When building `package_c`, its interface dependencies are [explicitly sorted](https://github.com/ament/ament_cmake/blob/ca8c26ea3c89e69c0c636b7cd0c088674c689f5f/ament_cmake_target_dependencies/cmake/ament_target_dependencies.cmake#L130-L143).

However, when building `package_d`, it doesn't report `INTERFACE_INCLUDE_DIRECTORIES` of _transitive_ dependencies. Thus, the include directories of `a` and `b` are not considered for sorting in above-mentioned code, but are used according to the order given in ament_target_dependencies(`package_c` ...).
Indeed, changing the order there would fix the issue.

## Solution Proposal

Obviously, sorting of include directories should consider _all_ dependencies.
Actually, https://github.com/ament/ament_cmake/pull/259 already implemented a function to recursively retrieve all include dirs. However, https://github.com/ament/ament_cmake/pull/260, which introduced the code above,
didn't consider that?!

I was really surprised to hit such a fundamental issue.