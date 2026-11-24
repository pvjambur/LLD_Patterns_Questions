# UML and LLD: basic rules, notation and build order

General notes for any low-level design problem (parking lot, library, booking system, food delivery, splitwise, elevator and so on).

Part A covers how to read and draw UML. Part B covers how to turn a finished UML diagram into the exact order to write the code.

---

# Part A: UML and LLD notation

## A1. Requirements first

### Functional requirements: what the system does

Write each one as `<actor> can <verb> <object>`.

- User can search, browse or filter items
- User can add, update or remove things they own (cart, booking, list)
- System creates objects of different types or modes (delivery vs pickup, car vs bike, now vs scheduled)
- System supports several ways to do one job (payment modes, pricing rules, matching rules)
- System notifies actors when something happens
- Admin can manage the catalogue (add, update, remove)
- Anyone can look up a record by id

How to collect them:

1. List the actors (user, admin, system, external service).
2. List the use cases for each actor.
3. Keep the 5 to 8 core ones and write an "Out of scope" list.

### Non-functional requirements: how well it does it

Name the quality, then the design choice that delivers it.

| Quality | Design choice |
|---|---|
| Extensibility | interfaces plus Strategy / Factory (Open/Closed: add new classes, don't edit old ones) |
| Maintainability | one responsibility per class, folders by role |
| Loose coupling | the client talks only to a Facade |
| Single source of truth | one Manager per collection (Singleton) |
| Consistency | change state only after the step succeeds |
| Scalability | managers can later sit on a database or service |
| Thread safety | lock singletons, id generators and shared maps |
| Testability | depend on interfaces so fakes can be swapped in |

In an LLD round, 4 or 5 of these are enough. Latency and availability belong mostly to HLD.

## A2. Common LLD design patterns

| Pattern | Use it when | Typical classes |
|---|---|---|
| Singleton | exactly one shared instance is needed | managers, registries, config, logger |
| Strategy | an algorithm must be swappable at runtime | payment modes, pricing, sorting, matching |
| Factory | the caller shouldn't know which subclass gets created | order, vehicle, notification types |
| Facade | the client needs one simple entry point | the App / Controller class main.cpp talks to |
| Observer | many listeners react to one event | notifications, UI updates, subscriptions |
| State | behaviour changes with the object's state | vending machine, elevator, order status |
| Decorator | features are added by wrapping | toppings, add-ons, logging wrappers |
| Builder | an object has many optional fields | complex configs, requests |
| Adapter | an outside API must fit your interface | third-party gateway |
| Command | a request must be stored as an object | undo/redo, job queues |

## A3. Visibility symbols

| Symbol | Meaning | Typical use |
|---|---|---|
| `+` | public | API methods, getters |
| `-` | private | data fields |
| `#` | protected | base-class fields a child class reads |
| `~` | package | same package / namespace (rare in C++) |
| underline | static | `getInstance()`, `nextId` |
| italic or `{abstract}` | abstract | abstract class, pure virtual method |

Syntax:

```
attribute:  - name: Type
method:     + name(param: Type): ReturnType
```

Rule of thumb: fields are `-`, behaviour is `+`, anything shared with children is `#`. Don't draw every getter, only the methods that matter.

Example class box:

```
┌──────────────────────────────┐
│           «model»            │
│             Book             │
├──────────────────────────────┤
│ - id: int                    │
│ - title: string              │
│ - price: double              │
├──────────────────────────────┤
│ + Book(id, title, price)     │
│ + getTitle(): string         │
│ + getPrice(): double         │
└──────────────────────────────┘
```

## A4. Stereotypes: the «labels» above class names

| Stereotype | Meaning | C++ shape | Examples |
|---|---|---|---|
| «model» | plain data entity, a noun from the requirements; state plus getters, little logic | plain class | Book, Item, Seat, Vehicle, User |
| «abstract» | cannot be instantiated; at least one pure virtual method; can hold fields and shared code | `virtual T f() = 0;` plus `virtual ~X() = default;` | Account, Vehicle, Order |
| «interface» | pure contract: only pure virtual methods, no data | class with only pure virtual methods | PaymentStrategy, Shape, Notifier |
| «singleton» | exactly one instance | private constructor, deleted copy, static `getInstance()` | Inventory, OrderManager, Logger |
| «enum» | fixed set of values | `enum class` | Status, Type, Mode |
| «service» | stateless behaviour | class with methods, no important state | NotificationService, PricingService |
| «facade» | one entry point that delegates | the App class | ParkingLotApp, LibraryApp |
| «utility» | static helpers | static methods | TimeUtils, IdGenerator |

Abstract vs interface: abstract means "is a kind of, and shares code". Interface means "can do this".

## A5. Relationships: arrows, phrases and code

| Relationship | How to draw it | Phrase | Meaning | C++ | Example |
|---|---|---|---|---|---|
| Inheritance (generalization) | solid line, hollow triangle at the parent `───▷` | is-a | child is a specialised parent; reuses and overrides | `class Dog : public Animal` | Dog ───▷ Animal |
| Realization (implementation) | dashed line, hollow triangle at the interface `┈┈┈▷` | implements, can-do | class fulfils an interface contract | `class Circle : public Shape { double area() const override; };` | Circle ┈┈┈▷ «interface» Shape |
| Association (simple) | solid line, open arrow toward the class it knows `───>` | has-a, knows-a | long-lived link; neither owns the other | `Car* car;` | Driver ───> Car |
| Aggregation (weak has-a) | solid line, hollow diamond at the whole `◇───` | weak has-a | whole holds parts, parts live on their own | `vector<Player*> players;` | Team ◇─── Player |
| Composition (strong has-a) | solid line, filled diamond at the whole `◆───` | strong has-a, part-of, strict composition | part cannot exist without the whole | `vector<Room> rooms;` (by value) | House ◆─── Room |
| Dependency | dashed line, open arrow `┈┈┈>` | uses temporarily, creates | appears only as a parameter, local variable or return value | `void print(const Document& d);` | Printer ┈┈┈> Document |

Strength, weakest to strongest coupling: Dependency < Association < Aggregation < Composition.

## A6. Multiplicity

| Notation | Meaning |
|---|---|
| `1` | exactly one |
| `0..1` | zero or one (optional) |
| `*` | many (same as `0..*`) |
| `0..*` | zero or more |
| `1..*` | one or more |

Write it with two dots: `1..*`, not `1...*`. Put it at the end being counted: `House 1 ◆──── 1..* Room` reads "one House has one or more Rooms".

## A7. Picking the right arrow

Ask in order and stop at the first yes:

1. Is A a kind of B? Then inheritance (dashed realization if B is an «interface»).
2. Does A not store B as a member at all (only a parameter, local, return value, or something it creates)? Then dependency.
3. Does A own B's lifetime (created with A, dies with A, never shared)? Then composition ◆.
4. Is A a container of Bs that live elsewhere (B survives without A, can be shared)? Then aggregation ◇.
5. Otherwise A just keeps a pointer to B. That is association ───>.

## A8. Common UML mistakes

- Multiplicity written `1...*` instead of `1..*`.
- Solid triangle line to an «interface». It should be dashed (realization).
- Diamond on the wrong end. It always sits on the whole.
- Storing something you don't own by value. Use a pointer (association).
- Abstract type stored by value (`Strategy s`). Use a pointer or reference, otherwise it won't compile or will slice.
- "Creates" drawn as association. It is a dependency.
- Members without `+` / `-`, arrows without labels or multiplicity.
- Type mismatches (`int total` while `price` is `double`).
- Inheritance used only to reuse code. Prefer composition.
- One god class that does everything.

## A9. How to approach any LLD

1. Clarify requirements: ask questions, then write the functional and non-functional lists.
2. Underline the nouns. They are your candidate classes.
3. Underline the verbs. They are your methods.
4. Find relationships: is-a or has-a? weak or strong? what multiplicity?
5. Find what varies (modes, types, rules, timing). That is where patterns go.
6. Add managers for collections and a facade for the client.
7. Draw the UML: stereotypes, `+` / `-` members, arrows, multiplicities, has-a / is-a labels.
8. Turn the UML into a build order (Part B) and code bottom-up, compiling after each file.
9. Walk one full flow end to end to validate.

## A10. UML and LLD tips

- Every class box has 3 parts: stereotype plus name, attributes, methods.
- Label every arrow with has-a / is-a and a multiplicity.
- Arrow direction shows who knows whom (navigability).
- Prefer composition over inheritance.
- Program to interfaces (`Strategy*`, `Factory*`).
- Keep models dumb (data plus getters). Logic lives in managers and services.
- One class, one reason to change (SRP).
- No god class: the facade delegates, it doesn't do the work itself.
- No include cycles: forward-declare when you only hold a pointer.
- Abstract base classes need a virtual destructor.
- Finish by naming the extensions you would add next.

## A11. Folder structure (by role)

```
project/
├── utils/        helpers: TimeUtils, IdGenerator
├── enums/        Status, Type, Mode
├── models/       entities (nouns): leaf models, composite models,
│                 abstract bases and their subclasses
├── strategies/   interfaces + interchangeable implementations
├── factories/    factory interface + concrete factories
├── services/     stateless behaviour (notify, log)
├── managers/     singletons that own collections
├── <App>.h       facade / orchestrator
└── main.cpp      client: runs one demo flow
```

Header-only build: `g++ -std=c++17 -I. main.cpp -o app`

## A12. How one request flows through the classes

```
Client (main.cpp) → App «facade» → Manager «singleton» → Factory «factory»
                  → Model «model»/«abstract» → Strategy «interface» → Service «service»
```

1. main calls one method on the Facade (`app.placeOrder(...)`, `app.parkVehicle(...)`, `app.bookSeat(...)`).
2. The Facade asks a Manager to find or validate existing objects (lookup by id, search, availability).
3. The Facade asks a Factory to create the right subclass for this request.
4. The new Model object is registered with its Manager, so there is one source of truth.
5. The part that varies is delegated to a Strategy (payment, pricing, matching, routing).
6. Side effects go to a Service (notify, log), then state is updated or cleaned up.

Rule: every call goes one layer down. Nothing low in the stack ever calls upward.

---

# Part B: from UML to build order (topological sort of classes)

## B1. The core idea

- Every class box in the UML is a node.
- Every relationship arrow means one class needs another to exist first. That is a directed edge `prerequisite → dependent`.
- The classes plus these edges form a DAG (directed acyclic graph). Any topological order of that DAG is a valid order to write the files.
- The indegree of a class is how many classes it needs first. Indegree 0 classes are the basic units, and you write them first.

## B2. Which relationship creates which edge

| Relationship | UML | Example | Build edge (first → then) | Hard edge? |
|---|---|---|---|---|
| Inheritance | `───▷` | Dog ───▷ Animal | Animal → Dog | always: base class must be complete |
| Realization | `┈┈┈▷` | Circle ┈┈┈▷ Shape | Shape → Circle | always |
| Composition (strong has-a) | `◆───` | House ◆─── Room | Room → House | always: stored by value, size needed |
| Aggregation (weak has-a) | `◇───` | Team ◇─── Player | Player → Team | only if the header calls its methods |
| Association (knows-a) | `───>` | Driver ───> Car | Car → Driver | only if the header calls its methods |
| Dependency | `┈┈┈>` | Printer ┈┈┈> Document | Document → Printer | if it calls methods or does `new X` |

## B3. Reading arrow direction

The UML arrow points at the class you need first.

- Triangle end (parent or interface): build first.
- Open arrowhead end (the class being used): build first.
- Diamond lines: the diamond sits on the whole. The whole needs its parts, so the end without the diamond is built first.

So the build edge is the UML arrow reversed:

```
UML  Child  ───▷ Parent    becomes   Parent → Child
UML  Holder ───> Target    becomes   Target → Holder
UML  Whole  ◆─── Part      becomes   Part → Whole
```

Hard vs soft edges:

- Hard edge: the dependent's header needs the full class (base class, member stored by value, calls a method, does `new X`). You must `#include` it, so it has to be written already.
- Soft edge: the dependent only stores or passes `X*` / `X&`. A forward declaration `class X;` is enough.
- In header-only code most edges are hard, because the method bodies live inside the header.

## B4. Indegree, outdegree, level

- indegree(X): number of classes X needs before it can be written (arrows coming into X in the build graph).
- outdegree(X): number of classes that need X. This is its blast radius: if X changes, all of those may break.
- Indegree 0: a basic unit. It includes nothing from the project, so write it first. In almost every design these are utils, enums, constants, pure interfaces and leaf models.
- High outdegree: design its interface carefully up front and avoid changing it later.
- level(X) = 0 if its indegree is 0, else 1 + the highest level among the classes it needs. Classes on the same level don't depend on each other.

## B5. The generic build graph

Most LLD designs have the same shape. The roles below stand in for real classes (examples in the last column).

```
L0: Utils, Enum, Interface, LeafModel
L1: CompositeModel, ConcreteStrategy
L2: AbstractBase
L3: ConcreteChild, Service, FactoryInterface, Manager
L4: ConcreteFactory
L5: Facade
L6: main

LeafModel          → CompositeModel     composition
Interface          → ConcreteStrategy   realization
Interface          → AbstractBase       association
Enum               → AbstractBase       association
CompositeModel     → AbstractBase       association
CompositeModel     → Facade             association
ConcreteStrategy   → main               dependency
AbstractBase       → ConcreteChild      inheritance
AbstractBase       → Service            dependency
AbstractBase       → FactoryInterface   dependency  (soft: forward declaration is enough)
AbstractBase       → Manager            aggregation
ConcreteChild      → ConcreteFactory    dependency
FactoryInterface   → ConcreteFactory    realization
Utils              → ConcreteFactory    dependency
Service            → Facade             association
Manager            → Facade             association
ConcreteFactory    → Facade             association
Facade             → main               dependency
```

| Role | Folder | Stereotype | In | Needs | Out | Level | Real examples |
|---|---|---|---|---|---|---|---|
| Utils | utils | «utility» | 0 | none (basic unit) | 1 | 0 | TimeUtils, IdGenerator |
| Enum | enums | «enum» | 0 | none (basic unit) | 1 | 0 | Status, Type, Mode |
| Interface | strategies | «interface» | 0 | none (basic unit) | 2 | 0 | PaymentStrategy, Shape, Notifier |
| LeafModel | models | «model» | 0 | none (basic unit) | 1 | 0 | Item, Seat, Book, Spot |
| CompositeModel | models | «model» | 1 | LeafModel | 2 | 1 | Cart, Show, Library, Floor |
| ConcreteStrategy | strategies | «strategy» | 1 | Interface | 1 | 1 | UpiPayment, Circle, EmailNotifier |
| AbstractBase | models | «abstract» | 3 | Interface, Enum, CompositeModel | 4 | 2 | Order, Account, Vehicle, Booking |
| ConcreteChild | models | «concrete» | 1 | AbstractBase | 1 | 3 | SavingsAccount, Car, OnlineBooking |
| Service | services | «service» | 1 | AbstractBase | 1 | 3 | NotificationService, PricingService |
| FactoryInterface | factories | «interface» | 1 | AbstractBase | 1 | 3 | VehicleFactory, OrderFactory |
| Manager | managers | «singleton» | 1 | AbstractBase | 1 | 3 | Inventory, BookingManager, Registry |
| ConcreteFactory | factories | «factory» | 3 | ConcreteChild, FactoryInterface, Utils | 1 | 4 | CarFactory, InstantOrderFactory |
| Facade | (root) | «facade» | 4 | CompositeModel, Service, Manager, ConcreteFactory | 1 | 5 | ParkingLotApp, LibraryApp, BankApp |
| main | (root) | «client» | 2 | ConcreteStrategy, Facade | 0 | 6 | main.cpp |

## B6. Algorithm A: Kahn's algorithm (BFS with indegree)

Start from the basic units and peel the graph layer by layer.

```
1. One node per class box in the UML
2. For every UML arrow add an edge  prerequisite → dependent
   (use the reversal rules: arrowhead end / part end first)
3. indeg[X] = number of edges coming into X
4. queue ← every class with indeg 0
5. while queue is not empty:
       X ← queue.pop_front()
       write X.h, compile, test it from main.cpp
       for each D that depends on X:
           indeg[D] -= 1
           if indeg[D] == 0: queue.push_back(D)
6. if written < total classes:
       a cycle exists → break it (see Cycles), rerun
```

## B7. Algorithm B: DFS (post-order)

Start from `main` and keep asking what each class needs.

```
visit(X):
    if state[X] == DONE:     return
    if state[X] == VISITING: CYCLE FOUND
    state[X] = VISITING
    for each P that X needs:      # its #includes
        visit(P)
    state[X] = DONE
    order.append(X)               # post-order

visit(main); then visit any class not reached
```

The resulting order has the leaves first and main last.

Kahn gives natural waves (all basic units together). DFS matches top-down thinking: to write the Facade I need the Manager, to write the Manager I need the AbstractBase, to write that I need the models. Both give a valid order, and a topological order is not unique.

DFS order on the generic graph: Interface → ConcreteStrategy → LeafModel → CompositeModel → Enum → AbstractBase → Service → Manager → ConcreteChild → FactoryInterface → Utils → ConcreteFactory → Facade → main

## B8. Kahn's algorithm run on the generic graph

Initial queue (indegree 0): Utils, Enum, Interface, LeafModel

| Step | Write (pop) | Indegree drops | Became 0 (enqueue) | Queue after |
|---|---|---|---|---|
| 1 | Utils | ConcreteFactory 3→2 | - | Enum, Interface, LeafModel |
| 2 | Enum | AbstractBase 3→2 | - | Interface, LeafModel |
| 3 | Interface | ConcreteStrategy 1→0, AbstractBase 2→1 | ConcreteStrategy | LeafModel, ConcreteStrategy |
| 4 | LeafModel | CompositeModel 1→0 | CompositeModel | ConcreteStrategy, CompositeModel |
| 5 | ConcreteStrategy | main 2→1 | - | CompositeModel |
| 6 | CompositeModel | AbstractBase 1→0, Facade 4→3 | AbstractBase | AbstractBase |
| 7 | AbstractBase | ConcreteChild 1→0, Service 1→0, FactoryInterface 1→0, Manager 1→0 | ConcreteChild, Service, FactoryInterface, Manager | ConcreteChild, Service, FactoryInterface, Manager |
| 8 | ConcreteChild | ConcreteFactory 2→1 | - | Service, FactoryInterface, Manager |
| 9 | Service | Facade 3→2 | - | FactoryInterface, Manager |
| 10 | FactoryInterface | ConcreteFactory 1→0 | ConcreteFactory | Manager, ConcreteFactory |
| 11 | Manager | Facade 2→1 | - | ConcreteFactory |
| 12 | ConcreteFactory | Facade 1→0 | Facade | Facade |
| 13 | Facade | main 1→0 | main | main |
| 14 | main | - | - | empty |

Result: Utils → Enum → Interface → LeafModel → ConcreteStrategy → CompositeModel → AbstractBase → ConcreteChild → Service → FactoryInterface → Manager → ConcreteFactory → Facade → main

All 14 classes were written, so there is no cycle.

## B9. Cycles and how to break them

A cycle means A needs B and B needs A. Kahn's algorithm gets stuck because both keep indegree above 0.

Example: Author keeps `vector<Book*> books` and Book keeps `Author* author`.

Fixes, best first:

1. Make one side soft: in `Author.h` write `class Book;` and only store `Book*`, with no Book method calls inside `Author.h`.
2. Move the logic that needs both into a higher layer, so a Manager, Service or Facade does it.
3. Depend on an interface instead of the concrete class (dependency inversion).
4. Header-only last resort: put that one method body after both class definitions, or split that class into `.h` + `.cpp`.

## B10. Layer hierarchy

Includes only ever point down. The top row is built last.

| Layer | Role | Generic classes |
|---|---|---|
| L10 | client | main.cpp |
| L9 | facade / controller / orchestrator | Facade (the App class) |
| L8 | managers / repositories (singletons) | Manager |
| L7 | concrete factories | ConcreteFactory |
| L6 | services + creator interfaces | Service, FactoryInterface |
| L5 | concrete subclasses | ConcreteChild |
| L4 | abstract bases that use models + interfaces | AbstractBase |
| L3 | concrete strategies (implement L0 interfaces) | ConcreteStrategy |
| L2 | composite models (hold other models) | CompositeModel |
| L1 | leaf models (only primitives, std types, enums) | LeafModel |
| L0 | utils, enums, constants, dependency-free interfaces | Utils, Enum, Interface |

Rules:

- A file may `#include` only from its own layer or a lower one.
- Never include upward: a model must never include a manager.
- Inside a layer, follow the topological order.
- Layer means role, which decides the direction includes may point. Level means the earliest a class can be written, from the graph. A Manager has role L8 but may be level 3: you can write it early, it just must never be included by anything below L8.
- Folders group files by role, and the build order can cross folders. An abstract base in `models/` may need an interface from `strategies/`, so that interface is written first.
- Memory hooks: interface before implementation, part before whole, parent before child, product before its factory, item before its manager, everything before the facade, facade before main.

## B11. File order for the generic graph

This is the Kahn result. Write one file, compile, test it from `main.cpp`, then move on.

| # | File | In | Test before moving on |
|---|---|---|---|
| 1 | `utils/Utils.h` | 0 | call each helper, print the result |
| 2 | `enums/Enum.h` | 0 | print a value through a toString() helper |
| 3 | `strategies/Interface.h` | 0 | interface only: just make sure it compiles |
| 4 | `models/LeafModel.h` | 0 | create one, print its fields |
| 5 | `strategies/ConcreteStrategy.h` | 1 | call its method, print a line |
| 6 | `models/CompositeModel.h` | 1 | add a few leaf models, print list / total |
| 7 | `models/AbstractBase.h` | 3 | abstract: compiles, cannot be instantiated |
| 8 | `models/ConcreteChild.h` | 1 | create via a base pointer, call getType() |
| 9 | `services/Service.h` | 1 | pass an object in, see the side effect |
| 10 | `factories/FactoryInterface.h` | 1 | interface only: just make sure it compiles |
| 11 | `managers/Manager.h` | 1 | add, find by id, list all |
| 12 | `factories/ConcreteFactory.h` | 3 | returns the right subclass for each type |
| 13 | `<App>.h` | 4 | each public method works for one happy path |
| 14 | `main.cpp` | 2 | one full end-to-end flow |

Compile after every file:

```
g++ -std=c++17 -I. main.cpp -o app && ./app
```

## B12. Per-file checklist

Inside every header, write in this order:

1. `#pragma once`
2. `#include` only the hard prerequisites (already written)
3. `class X;` for the soft ones
4. `// «stereotype»` comment
5. private fields (UML attributes, the `-` ones)
6. constructor
7. getters
8. behaviour methods (the `+` ones)
9. `virtual ~X() = default;` if it has virtual methods
10. compile and test from `main.cpp` before the next file

## B13. Tips

- Never start a file whose prerequisites are unfinished.
- Interfaces usually have indegree 0, so write them early.
- Same level means independent, so the order between them is free.
- Changing a high-outdegree class means rebuilding everything that depends on it.
- Every new arrow in the UML is a new edge: update the graph.
- Keep models dumb. Logic goes up into services and managers, which keeps the low layers small and stable.
- The class with the biggest indegree is usually the facade. It should only delegate, never do the work.

## B14. Recipe for any new UML

1. List every class box. Each is a node.
2. For every arrow, add a build edge with the reversal rule (arrowhead end first; for diamonds, the part end first).
3. Mark each edge hard or soft: does the header need the full class, or only a pointer?
4. Count the indegree of each class.
5. Run Kahn: queue the indegree 0 classes, write them, decrement their dependents, queue the new zeros.
6. If classes are left over, find the cycle and break it (soft edge, move logic up, interface, or `.cpp`).
7. Group the result by layer and check that no include points upward.
8. Write the files in that order, compiling and testing after each one.
