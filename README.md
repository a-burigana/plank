# The `plank` toolkit for DEL-based epistemic planning

### [===] Planning, with Knowledge. [===]


---

`plank` is a C++17 toolkit for building, maintaining, visualizing, and testing **DEL-based epistemic planning
benchmarks** written in **EPDDL** (*Epistemic Planning Domain Definition Language*).

It is designed to assist researchers and practitioners in epistemic planning by providing
both **batch-style tools** and an **interactive shell** for working with EPDDL specifications, and
to create, manipulate and test epistemic states, formulas, and action sequences.

Both `plank` and **EPDDL** are developed by the authors of this repository.

---

# Table of contents

1. [Main Features](#main-features)
2. [Installation](#installation)
3. [EPDDL](#epddl)
4. [Usage Overview](#usage-overview)
5. [Non-Interactive Command-Line Interface](#non-interactive-command-line-interface)
6. [Interactive Command-Line Interface](#interactive-command-line-interface)
   1. [Navigation and Session Management](#navigation-and-session-management)
   2. [Task Management (`task`)](#task-management-task)
   3. [Loading EPDDL Files (`load`)](#loading-epddl-files-load)
   4. [Parsing and Grounding](#parsing-and-grounding)
   5. [Showing Task Data (`show`)](#showing-task-data-show)
   6. [Epistemic States (`state`)](#epistemic-states-state)
   7. [Formulas (`formula`)](#formulas-formula)
   8. [Exporting (`export`)](#exporting-export)
   9. [Validation (`validate`)](#validation)
   10. [Scripts (`script`)](#scripts-script)
   11. [Meta Commands](#meta-commands)
7. [Example Workflow (Interactive)](#example-workflow-interactive)
8. [License](#license)

---

## Main Features

`plank` implements many utilities for working with EPDDL specifications: 
- Native support for **EPDDL domains, problems, and action-type libraries**.
- **Parsing, type-checking, and grounding** of EPDDL specifications.
- Creation, update, manipulation, and bisimulation contractions of **epistemic states**.
- Definition and reuse of **epistemic formulas**.
- Applicability checks and **plan validation**.
- Export of:
  - Ground planning tasks to **JSON** (EPDDL official format).
  - Epistemic states and actions to **Graphviz visualizations**.
- Scriptable workflows via **plank scripts**.
- Multi-task sessions with isolated scopes.

---

## Installation

### Requirements

- C++17 compatible compiler
- CMake
- (Optional) [Graphviz](https://graphviz.org/) — required for exporting states/actions as images

Warning: `plank` has been tested on Unix-based systems (Linux and macOS).
If you have a Windows machine, we suggest you use the
[Linux subsystem for Windows](https://learn.microsoft.com/en-us/windows/wsl/install).

### Build

To build `plank`, you can use the following commands:

```bash
git clone https://github.com/a-burigana/plank.git
cd plank
mkdir build && cd build
cmake ..
make
````

The resulting `plank` executable can be used directly.

We are currently working on a more user-friendly installation process via the [Homebrew](https://brew.sh/) package
manager. Stay tuned!

---

## EPDDL

One of the most well-known frameworks for epistemic planning is Dynamic Epistemic Logic (DEL), which offers a rich and
natural semantics for modelling problems in this setting. The high expressive power provided by DEL make DEL-based
epistemic planning a challenging problem to tackle both theoretically, and in practical implementations. As a result,
existing epistemic planners often target different DEL fragments (or formalisms equivalent to those fragments), and
typically rely on ad hoc languages to represent benchmarks, and sometimes no language at all. This fragmentation hampers
comparison, reuse, and systematic benchmark development. We addressed these issues by basing the semantics of the
Epistemic Planning Domain Definition Language (EPDDL) on the DEL framework. In this way, we obtain a language that is
able to represent a very wide range of epistemic planning benchmarks in a unique format.

Furthermore, we devised EPDDL with the goal of providing a clear way of defining fragments of DEL. In this way, instead
of having different languages to represent problem based on different (less expressive) formalisms, we obtain *one* rich
language to define many such formalisms under a unified syntax, enabling a meaningful comparison across different
epistemic planners based on different formalisms. This is achieved by adding to *domain* and *problem* a third component
of an EPDDL specification called *action type libraries* (see [EPDDL Official Guideline](#https://arxiv.org/abs/2601.20969)
for all details). A library defines a set of action types (e.g., public announcement, private ontic and semi-private
sensing), which can be used in a domain that includes that library to define epistemic actions. The DEL fragment
identified by the library is the one comprising all epistemic actions that have one of the types defined in the library
(e.g., the fragment made by all public announcements, private ontic actions and semi-private sensing actions).

Separating action types from actions also allows to greatly simplify the development of EPDDL benchmarks. In fact, many
benchmarks share the same action types, so once the fragment has been defined one can simply focus on writing the
actions definitions in the domain.

All details about syntax and semantics of EPDDL are provided in the [EPDDL Official Guideline](#https://arxiv.org/abs/2601.20969).
In this repo (under the ```benchmarks``` directory) are present several examples of EPDDL specifications.

---

## Usage Overview

`plank` supports **two complementary modalities**:

1. **Non-interactive command-line interface**:
   for single-shot operations, like parsing, task exportation and plan validation.

2. **Interactive command-line interface**:
   for exploratory modeling, debugging, visualization, and incremental development of EPDDL specifications.


---

## Non-Interactive Command-Line Interface

In non-interactive mode, `plank` operates directly on a given EPDDL specification and
performs a single operation before exiting.

### Supported Operations

* `parse`: parsing and type-checking.
* `ground`: grounding.
* `export`: export to ground JSON format.
* `validate`: validate an action sequence.
* `help`: print man page.

---

### Providing an EPDDL Specification

There are **two ways** to pass an EPDDL specification to `plank`:

#### 1. Explicit paths

Provide paths to:

* An EPDDL **domain**.
* An EPDDL **problem**.
* Zero or more **action-type libraries**.

#### 2. Specification file

Provide a single **EPDDL specification file** (`.json`) with the following structure:

```json
{
    "domain" : "path/to/domain.epddl",
    "problem": "path/to/problem.epddl",
    "action-type-libraries": [
        "path/to/library_1.epddl",
        "...",
        "path/to/library_n.epddl"
    ]
}
```

Specification files can be automatically generated from the interactive CLI using (see
[Task Management](#task-management-task) for more details):

```bash
task save-spec <path>
```

---

### Command Synopsis

#### Parsing, Type-Checking and Grounding

To **parse** and **type-check** an EPDDL specification, you can run one of the following commands from the build
directory:
```bash
./plank parse -d <domain path> -p <problem path> [-l <libraries paths>...]
./plank parse -s <specification path>
```

`plank` will perform a syntactic and semantic check on the specification, and print syntax/semantic errors to the
standard output, if any. During parsing, `plank` also keeps track of all the requirements that should be declared in the
specification (according to the EPDDL syntax definition). For instance, if user-defined types are declared, the
`:typing` requirement should be declared as well. If the specification makes use of some features, but does not specify
the relative requirement, `plank` outputs a warning message to signal the user about the missing requirement.

To **ground** an EPDDL specification, you can run one of the following commands:
```bash
./plank ground -d <domain path> -p <problem path> [-l <libraries paths>...]
./plank ground -s <specification path>
```

`plank` will perform a syntactic and semantic check on the specification followed by its grounding, and print
syntax/semantic/grounding errors to the standard output, if any.

Commands `parse` and `ground` can be used to test the correctness of a specification.

---

#### Exporting

An EPDDL specification can be exported to ground epistemic planning task in a **JSON** format (described in the
[EPDDL Official Guideline](#https://arxiv.org/abs/2601.20969)):

```bash
./plank export -d <domain path> -p <problem path> [-l <libraries paths>...] \
             -o <path to output directory>

./plank export -s <specification path> -o <path to output directory>
```

If grounding is successful, then `plank` will create a file in the output directory named `<task name>.json`, where is
the name of the EPDDL problem file. For instance, if the problem file is called `prob.epddl`, the exported file will be
named `prob.json`.

---

#### Validation

To validate an action sequence on the given EPDDL specification, use the command:

```bash
./plank validate -d <domain path> -p <problem path> [-l <libraries paths>...] \
               -a <actions>...

./plank validate -s <specification path> -a <actions>...
```

The command returns `true` if the plan is valid, and `false` otherwise.
If a plan is not valid, an explanation of the reason is also provided (e.g., some action is not applicable, or the final
state is not a goal state). If no actions are provided, the goal formula is checked on the initial epistemic state.

---

#### Help

You can consult the man page of `plank`'s non-interactive CLI by running:
```bash
./plank help
```


---

## Interactive Command-Line Interface

Running `plank` **without arguments** starts the interactive CLI:

```bash
./plank
```

This starts an **interactive session** that maintains state across commands.

The interactive CLI allows users to:

* Manage multiple epistemic planning tasks.
* Load EPDDL specifications.
* Define formulas and epistemic states.
* Apply actions, check formulas, and validate plans.
* Export states, actions, and tasks.
* Run user-defined scripts.

---

For detailed documentation of any command, use:

```bash
man <command>
```

---

### Navigation and Session Management

The following utility commands are provided to navigate the filesystem and handle the current session:

| Command   | Description                      |
| --------- | -------------------------------- |
| `cd`      | Change current working directory |
| `pwd`     | Print current working directory  |
| `ls`      | List directory contents          |
| `clear`   | Clear session data               |
| `history` | Show command history             |
| `! <n>`   | Execute command by history index |
| `quit`    | Quit current session             |

---

### Task Management (`task`)

Tasks define **isolated scopes** containing EPDDL specifications and derived data.

```bash
task add <task name>
task remove <task name>
task rename <task name> <new task name>
task copy <task name> <new task name>
task open <task name>
task close
task switch <task name>
task save-spec <path>
```

To create a new task, simply run `task add` followed by the name of the task.
Task can be renamed and copied.
To navigate between tasks you can use `open`, `close` and `switch`.
`open` can be used if no task is currently active.
If a task to be opened does not exist, then it is automatically created before opening it.
Otherwise, the command `switch` can be used (equivalent to `task close` followed by `task open <task name>`.

For instance, let's create and open a new task called `cb-1` (abbreviation for `Coin-in-the-Box-1`):
```bash
plank> task open cb-1
```

This will create and open the new task, and change the prompt string to indicate that the task has been opened:
```bash
plank/cb-1>
```

Once an EPDDL specification has been loaded into a task (see [Loading EPDDL Files](#loading-epddl-files-load)), the file
paths of the specification can be saved to a JSON file. To do so, you can use `task save-spec` followed by the name of
the file used to save the output. The output file will have the following structure:

```json
{
  "domain" : "path/to/domain.epddl",
  "problem": "path/to/problem.epddl",
  "action-type-libraries": [
    "path/to/library_1.epddl",
    "...",
    "path/to/library_n.epddl"
  ]
}
```


---

### Loading EPDDL Files (`load`)

To load an EPDDL domain, problem, action type library or specification, use the commands:
```bash
load domain <path to file>
load problem <path to file>
load library <path to file>
load spec <path to file>
```

You can load multiple libraries, but only one domain/problem.
If you reload a domain or a problem, this will overwrite the previous one.

For instance, let's load the files into our `cb-1` task.
Letting `path/to/plank-repo` denote the path to the `plank` repository, we can load the files as follows:
```bash
plank/cb-1> pwd
path/to/plank-repo/build
plank/cb-1> cd ../benchmarks/domains/Coin-in-the-Box
plank/cb-1> load domain cb.epddl
plank/cb-1> load problem instances/problem_1.epddl
plank/cb-1> load library ../../libraries/intermediate.epddl
```

We now have successfully loaded all components of our specification.
To save us some time in the future, we can save the specification paths to file:
```bash
plank/cb-1> task save-spec instances/cb-1-spec.json
```

This will create the required file in the `instances` directory.
The file will contain the following:
```json
{
   "domain" : "path/to/plank-repo/benchmarks/domains/Coin-in-the-Box/cb.epddl",
   "problem": "path/to/plank-repo/benchmarks/domains/Coin-in-the-Box/instances/problem_1.epddl",
   "action-type-libraries": [
      "path/to/plank-repo/benchmarks/libraries/intermediate.epddl"
   ]
}
```

In this way, instead of loading each file manually, we can now directly load the entire specification in one go and save
us some time in future sessions:
```bash
plank/cb-1> load spec instances/cb-1-spec.json
```

---

### Parsing, Type-Checking and Grounding

Once a specification is loaded in a task, you can perform parsing/type-checking and grounding with the commands:

| Command  | Description                                    |
| -------- | ---------------------------------------------- |
| `parse`  | Parse and type-check the current specification |
| `ground` | Compute the ground epistemic planning task     |

The behaviour of these commands is as described [above](#parsing-type-checking-and-grounding).
Note that these commands are **task-dependent**, *i.e.*, they can only be run if a task is opened.

<!---Grounding may invalidate existing states and formulas if the logical language changes.
When this happens, `plank` interactively asks how to proceed.
--->

---

### Showing Task Data (`show`)

To print the data of the current session and of the currently opened task, you can use the command: 

```bash
show tasks
show states
show actions [-g]
show formulas [-g]
show types [-t] [-g]
show predicates [-g]
show entities [-t] [-g]
show objects [-t] [-g]
show agents [-t] [-g]
show agent-groups [-t] [-g]
```

Option `-t` (`--types`) prints the type of the shown entities (when running `show entities`, `show objects`,
`show agents`, or `show agent-groups`), or the super-type of the shown types (when running `show types`).

Option `-g` (`--ground`) forces a (partial) grounding of the specification before printing, applying possible
modifications. If this option is used to print all actions names, then the entire specification is grounded, *i.e.*,
`show actions -g` is equivalent to:

```bash
ground
show actions
```

If option `-g` is used to print predicates, entities or types, then `plank` only grounds the logical language, which
requires less computation time.

Let's look at some examples:
```bash
plank/cb-1> show types -t
Parsing...done.
Grounding task language...done.
entity
object         - entity
agent          - entity
agent-group    - entity
world
event
obs-type
plank/cb-1> show actions
Parsing...done.
Grounding...done.
open_A           signal_A_B       signal_B_C       distract_A_B     distract_B_C     peek_A           shout-tails_A    
open_B           signal_A_C       signal_C_A       distract_A_C     distract_C_A     peek_B           shout-tails_B    
open_C           signal_B_A       signal_C_B       distract_B_A     distract_C_B     peek_C           shout-tails_C
plank/cb-1> show entities
A    B    C
plank/cb-1> show predicates
has-key_A    has-key_B    has-key_C    looking_A    looking_B    looking_C    opened       tails
```

---

### Formulas (`formula`)

To create and manage formulas, use the next command:

```bash
formula add <formula name> <EPDDL formula>
formula add-goal <formula name>
formula remove <formula name>
formula rename <formula name> <new formula name>
formula copy <formula name> <new formula name>
```

To add the goal formula, you can use `add-goal` as follows:
```bash
plank/cb-1> formula add-goal goal
Grounding goal formula...done.
plank/cb-1> show formulas
goal    = ([(A)] (tails))
```
User-defined EPDDL formulas can also be created using `add`.
It is possible to reference existing formulas by escaping their with a `$` symbol.
Nested names escaping is resolved recursively.
For instance:
```bash
plank/cb-1> formula add opened-and-goal "(and (opened) $goal)"
Grounding formula...done.
plank/cb-1> formula add ck-opened-and-goal '([C. All] $opened-and-goal)'
Grounding formula...done.
plank/cb-1> show formulas                                               
goal                  = ([(A)] (tails))
opened-and-goal       = (and (opened) ([(A)] (tails)))
ck-opened-and-goal    = ([C. (A B C)] (and (opened) ([(A)] (tails))))
```

Note that EPDDL formulas that contain spaces **must** be enclosed in either single or double quotes. 

---

### Epistemic States (`state`)

To create, update, and analyze epistemic states, use the next command:

```bash
state add-init <state name> [-g]
state remove <state name>
state rename <state name> <new state name>
state copy <state name> <new state name>
state check <state name> <formula (name)>
state applicable <state name> <action(s) name(s)>... [-g]
state update <state name> <action(s) name(s)>... [-c] [-g]
        [-a <new state name>]
        [-e <path to directory>
            [--all]
            [--pdf|--png|--jpg|--svg|--eps|--ps]]
state contract <state name>
        [-a <new state name>]
        [-e <path to directory>
            [--pdf|--png|--jpg|--svg|--eps|--ps]]
```

#### Adding the Initial State
To add the initial state to the task data, you may use `add-init` as follows:
```bash
plank/cb-1> state add-init s0
Grounding initial state...done.
plank/cb-1> show states
s0    ; Initial state of problem 'cb-1'
```

This will create a new state named `s0` in the scope of the task, as shown above.

#### Checking Formulas and Applicability
To check whether a formula holds in a state, you may use `check` as follows:
```bash
plank/cb-1> state check s0 goal
false
plank/cb-1> state check s0 '(not ([Kw. A] (tails)))'
Grounding formula...done.
true
```

The goal formula expresses that agent `A` knows/believes that the coin lies tails up, and this does not hold initially.
In fact, the second formula, expressing the fact that agent `A` *doesn't know whether* the coin lies tails up, is true
in state `s0`.

To have a better idea of why this is the case, you can export the initial state to an image file
(see [Exporting](#exporting-export) for more details on the command) and check the state yourself:

```bash
plank/cb-1> export state s0 instances/ --png
```

This will create the file `s0.png` in the `instances` directory, containing a [graphviz](https://graphviz.org/)-generated
representation of the state:

![](benchmarks/domains/Coin-in-the-Box/instances/s0.png "Graphviz representation of state `s0`")

The graph on the left-hand side of the figure represents the epistemic state. Each circle represents a world, with its
name shown inside. Doubled circles are designated worlds. The accessibility relations are represented by labelled edge.
Finally, the table on the right-hand side represents the labels of each world, with atoms that are contained in a label
colored in blue, and the remaining ones in red.

To check whether an action or an action sequence is applicable in a state, you may use `applicable` as follows:
```bash
plank/cb-1> state applicable s0 open_A
true
plank/cb-1> state applicable s0 open_A peek_A shout-tails_B
false (shout-tails_B is not applicable in s0 (X) open_A (X) peek_A)
```

In the initial state, agent `A` can open the box, as the agent has the key and the box is closed (see `cb.epddl` for all
details), but the agent can not peek into the box to see the value of the coin since the boxed has not been opened yet.

If this command is used with option `-g` (`--ground`), then the specification is grounded before checking for
applicability.

#### Updating a State
You can update a state with an action or an action sequence as follows:
```bash
plank/cb-1> state update s0 open_A --add s1
plank/cb-1> show states
s0    ; Initial state of problem 'cb-1'
s1    ; s0 (X) open_A
```

This creates a new state `s1` from the result of `s0` $\otimes$ `open_A`. If the `-add` option is not explicitly
provided, then no state is created. This is useful, for instance, if you want to update and export a state to an image
file, but you do not need to save the state in the session. To do so, you can proceed as follows:
```bash
plank/cb-1> state update s0 open_A signal_A_B signal_A_C --export instances/ --png
```

This command will update s0 with the provided action sequence and export the final result to the `instanes` directory
as a `.png` image. If option `--all` is added after `--export`, then **all** computed states will be exported.


---

### Exporting (`export`)

```bash
export task <task> [-g] [dir]
export state <state>|--all [dir] [format]
export action <action>|--all [-g] [dir] [format]
```

---

### Validation (`validate`)

```bash
validate [<actions>...] [-g]
```

---

### Scripts (`script`)

```bash
script add <name> <path>
script remove <name>
script rename <name> <new-name>
script run <name>
```

Scripts are executed line-by-line until completion or error.

---

### Meta Commands

| Command   | Description         |
| --------- | ------------------- |
| `man`     | Show command manual |
| `version` | Print plank version |

---

## Example Workflow (Interactive)

```bash
plank
task add demo
task open demo
load domain domain.epddl
load problem problem.epddl
parse
ground
state add-init s0
show actions
state update s0 a1 a2 -a s1 -e ./out --pdf
validate a1 a2
```

---

## License

MIT License
