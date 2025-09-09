# Table Variable Trace

This document tracks the state of all variables in the Table class during the execution of the provided code.

## Initial Setup

```java
Symbol s = Symbol.symbol("a", 1)   // s points to Symbol("a", 1)
Symbol s1 = Symbol.symbol("b", 2)  // s1 points to Symbol("b", 2) 
Symbol s2 = Symbol.symbol("c", 3)  // s2 points to Symbol("c", 3)
Table t = new Table()              // Create new Table instance
```

**Initial Table State:**
- `symbols`: empty HashMap
- `top`: null
- `marks`: null

---

## Step 1: t.beginScope()

**Action:** Push new scope marker

**Table State After:**
- `symbols`: {} (empty)
- `top`: null
- `marks`: Binder(value=null, prevtop=null, tail=null)

---

## Step 2: t.put(s, "top-level a")

**Action:** Put Symbol("a", 1) → "top-level a"

**Table State After:**
- `symbols`: {Symbol("a",1) → Binder("top-level a", null, null)}
- `top`: Symbol("a", 1)
- `marks`: Binder(value=null, prevtop=null, tail=null)

**Symbol Chain for "a":**
- Symbol("a",1) → Binder("top-level a", prevtop=null, tail=null)

---

## Step 3: t.put(s1, "top-level b")

**Action:** Put Symbol("b", 2) → "top-level b"

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("top-level a", Symbol("b",2), null)
  - Symbol("b",2) → Binder("top-level b", null, null)
  }
- `top`: Symbol("b", 2)
- `marks`: Binder(value=null, prevtop=null, tail=null)

**Symbol Chains:**
- Symbol("a",1) → Binder("top-level a", prevtop=Symbol("b",2), tail=null)
- Symbol("b",2) → Binder("top-level b", prevtop=null, tail=null)

---

## Step 4: t.beginScope()

**Action:** Start new nested scope

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("top-level a", Symbol("b",2), null)
  - Symbol("b",2) → Binder("top-level b", null, null)
  }
- `top`: null
- `marks`: Binder(value=null, prevtop=Symbol("b",2), tail=Binder(null, null, null))

**Mark Stack:**
- Current mark: Binder(value=null, prevtop=Symbol("b",2), tail=previous_mark)
- Previous mark: Binder(value=null, prevtop=null, tail=null)

---

## Step 5: t.put(s2, "second-level c")

**Action:** Put Symbol("c", 3) → "second-level c"

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("top-level a", Symbol("b",2), null)
  - Symbol("b",2) → Binder("top-level b", null, null)
  - Symbol("c",3) → Binder("second-level c", null, null)
  }
- `top`: Symbol("c", 3)
- `marks`: Binder(value=null, prevtop=Symbol("b",2), tail=Binder(null, null, null))

**Symbol Chains:**
- Symbol("a",1) → Binder("top-level a", prevtop=Symbol("b",2), tail=null)
- Symbol("b",2) → Binder("top-level b", prevtop=null, tail=null)
- Symbol("c",3) → Binder("second-level c", prevtop=null, tail=null)

---

## Step 6: t.put(s, "second-level a")

**Action:** Put Symbol("a", 1) → "second-level a" (shadows existing "a")

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("second-level a", Symbol("c",3), Binder("top-level a", Symbol("b",2), null))
  - Symbol("b",2) → Binder("top-level b", null, null)
  - Symbol("c",3) → Binder("second-level c", null, null)
  }
- `top`: Symbol("a", 1)
- `marks`: Binder(value=null, prevtop=Symbol("b",2), tail=Binder(null, null, null))

**Symbol Chains:**
- Symbol("a",1) → Binder("second-level a", prevtop=Symbol("c",3), tail=Binder("top-level a", Symbol("b",2), null))
- Symbol("b",2) → Binder("top-level b", prevtop=null, tail=null)
- Symbol("c",3) → Binder("second-level c", prevtop=null, tail=null)

---

## Step 7: t.endScope()

**Action:** End nested scope, restore to previous scope state

**Processing:**
1. **top = Symbol("a",1)**: Remove second-level a, restore to tail
   - Remove: Binder("second-level a", Symbol("c",3), tail)
   - Restore: Binder("top-level a", Symbol("b",2), null)
   - **top becomes**: Symbol("c",3)

2. **top = Symbol("c",3)**: Remove second-level c completely
   - Remove: Binder("second-level c", null, null) 
   - No tail to restore, so remove from symbols
   - **top becomes**: null

3. **top = null**: End of scope restoration
   - Restore top from marks: Symbol("b",2)
   - Pop marks stack

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("top-level a", Symbol("b",2), null)
  - Symbol("b",2) → Binder("top-level b", null, null)
  }
- `top`: Symbol("b", 2)
- `marks`: Binder(value=null, prevtop=null, tail=null)

**Symbol Chains:**
- Symbol("a",1) → Binder("top-level a", prevtop=Symbol("b",2), tail=null)
- Symbol("b",2) → Binder("top-level b", prevtop=null, tail=null)

---

## Step 8: t.put(s2, "top-level c")

**Action:** Put Symbol("c", 3) → "top-level c"

**Table State After:**
- `symbols`: {
  - Symbol("a",1) → Binder("top-level a", Symbol("c",3), null)
  - Symbol("b",2) → Binder("top-level b", null, null)
  - Symbol("c",3) → Binder("top-level c", null, null)
  }
- `top`: Symbol("c", 3)
- `marks`: Binder(value=null, prevtop=null, tail=null)

**Symbol Chains:**
- Symbol("a",1) → Binder("top-level a", prevtop=Symbol("c",3), tail=null)
- Symbol("b",2) → Binder("top-level b", prevtop=null, tail=null)
- Symbol("c",3) → Binder("top-level c", prevtop=null, tail=null)

---

## Step 9: t.endScope()

**Action:** End outer scope

**Processing:**
1. **top = Symbol("c",3)**: Remove top-level c
   - Remove: Binder("top-level c", null, null)
   - **top becomes**: null

2. **top = Symbol("a",1)**: Remove top-level a  
   - Remove: Binder("top-level a", Symbol("c",3), null)
   - **top becomes**: Symbol("c",3) (but c was already removed, so this is stale)

3. **top = Symbol("b",2)**: Remove top-level b
   - Remove: Binder("top-level b", null, null)
   - **top becomes**: null

4. **top = null**: End of scope restoration
   - Restore top from marks: null
   - Pop marks stack to null

**Final Table State:**
- `symbols`: {} (empty)
- `top`: null
- `marks`: null

---

## Summary

The Table implementation uses a symbol table with scoped visibility:

- **Scopes** are managed via `beginScope()`/`endScope()` using a mark stack
- **Shadowing** is supported - inner scopes can hide outer scope bindings
- **Restoration** properly removes inner scope bindings and restores outer ones
- **Linking** maintains chains of bindings for the same symbol across scopes

The key insight is that each `put()` operation creates a new `Binder` that:
1. Points to the previous `top` symbol (for scope restoration)
2. Links to any previous binding of the same symbol (for shadowing)
3. Gets added to the current scope's symbol chain
