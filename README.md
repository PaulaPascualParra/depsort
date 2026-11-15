# depsort

Sorts a list of software packages so every package appears after the packages it depends on,
detects circular dependencies, and explains who requires what.

> Inspired by real dependency-management problems in a large Rez-based software environment.

## Example

```
$ depsort examples/packages.json
D
B
A
C
```

## Build

```bash
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
./build/depsort examples/packages.json
```

## Features

- [ ] Load package definitions from JSON
- [ ] Topological sort (requirements outside the input list are ignored)
- [ ] Cycle detection with the cycle path reported
- [ ] "required by" report

## Design decisions

_Write these as you go: what you chose, the alternatives, and why._

- Library + thin CLI split: ...
- Error handling strategy: ...
- Sorting algorithm (Kahn vs DFS): ...

## Possible extensions

- Version ranges and a backtracking resolver
- `--why <package>` to explain a dependency chain
