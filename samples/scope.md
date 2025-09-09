# Table Variable Trace

This document tracks the state of all variables in the Table class during the execution of the provided code.

## Execution Trace Table

| Step | Operation | symbols HashMap | top | marks | Notes |
|------|-----------|----------------|-----|-------|-------|
| Initial | `Table t = new Table()` | `{}` | `null` | `null` | Empty table created |
| 1 | `t.beginScope()` | `{}` | `null` | `Binder(null, null, null)` | First scope marker pushed |
| 2 | `t.put(s, "top-level a")` | `{a₁ → Binder("top-level a", null, null)}` | `a₁` | `Binder(null, null, null)` | Added symbol a with value |
| 3 | `t.put(s1, "top-level b")` | `{a₁ → Binder("top-level a", b₂, null)`<br/>`b₂ → Binder("top-level b", null, null)}` | `b₂` | `Binder(null, null, null)` | Added symbol b, linked to a |
| 4 | `t.beginScope()` | `{a₁ → Binder("top-level a", b₂, null)`<br/>`b₂ → Binder("top-level b", null, null)}` | `null` | `Binder(null, b₂, prev_mark)` | Started nested scope |
| 5 | `t.put(s2, "second-level c")` | `{a₁ → Binder("top-level a", b₂, null)`<br/>`b₂ → Binder("top-level b", null, null)`<br/>`c₃ → Binder("second-level c", null, null)}` | `c₃` | `Binder(null, b₂, prev_mark)` | Added symbol c in nested scope |
| 6 | `t.put(s, "second-level a")` | `{a₁ → Binder("second-level a", c₃, old_a_binder)`<br/>`b₂ → Binder("top-level b", null, null)`<br/>`c₃ → Binder("second-level c", null, null)}` | `a₁` | `Binder(null, b₂, prev_mark)` | Symbol a shadows previous binding |
| 7 | `t.endScope()` | `{a₁ → Binder("top-level a", b₂, null)`<br/>`b₂ → Binder("top-level b", null, null)}` | `b₂` | `Binder(null, null, null)` | Restored to outer scope |
| 8 | `t.put(s2, "top-level c")` | `{a₁ → Binder("top-level a", c₃, null)`<br/>`b₂ → Binder("top-level b", null, null)`<br/>`c₃ → Binder("top-level c", null, null)}` | `c₃` | `Binder(null, null, null)` | Added symbol c to outer scope |
| 9 | `t.endScope()` | `{}` | `null` | `null` | All symbols removed, table empty |

## Symbol Key
- `a₁` = Symbol("a", 1) 
- `b₂` = Symbol("b", 2)
- `c₃` = Symbol("c", 3)
- `old_a_binder` = `Binder("top-level a", b₂, null)`
- `prev_mark` = `Binder(null, null, null)`

## Detailed Binder Chain Analysis

### After Step 6 (Maximum Complexity)
```
Symbol a₁: Binder("second-level a", prevtop=c₃, tail=Binder("top-level a", prevtop=b₂, tail=null))
Symbol b₂: Binder("top-level b", prevtop=null, tail=null)  
Symbol c₃: Binder("second-level c", prevtop=null, tail=null)
```

### Scope Chain Visualization
```
Outer Scope: [a₁="top-level a"] → [b₂="top-level b"]
   ↓ beginScope()
Inner Scope: [c₃="second-level c"] → [a₁="second-level a"] (shadows outer a₁)
   ↓ endScope()
Outer Scope: [a₁="top-level a"] → [b₂="top-level b"] (restored)
```

## Key Implementation Details

1. **Binder Structure**: `Binder(value, prevtop, tail)`
   - `value`: The stored object
   - `prevtop`: Previous symbol in current scope (for scope restoration)
   - `tail`: Previous binding of same symbol (for shadowing)

2. **Scope Management**: 
   - `marks` stack stores scope boundaries
   - Each mark remembers the `top` symbol when scope began
   - `endScope()` walks backward through `top` chain to restore state

3. **Symbol Shadowing**:
   - New bindings for existing symbols create a chain via `tail`
   - `get()` always returns current (head) binding
   - `endScope()` restores previous binding from `tail`
