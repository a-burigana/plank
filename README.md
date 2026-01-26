# The `plank` toolkit for DEL-based epistemic planning

### [===] Planning, with Knowledge. [===]


---

`plank` is a C++17 toolkit for building, maintaining, visualizing, and testing **DEL-based epistemic planning benchmarks** written in **EPDDL** (*Epistemic Planning Domain Definition Language*).

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
   1. [Navigation & Session Management](#navigation--session-management)
   2. [Task Management (`task`)](#task-management-task)
   3. [Loading EPDDL Files (`load`)](#loading-epddl-files-load)
   4. [Parsing and Grounding](#parsing-and-grounding)
   5. [Showing Task Data (`show`)](#showing-task-data-show)
   6. [Formulas (`formula`)](#formulas-formula)
   7. [Epistemic States (`state`)](#epistemic-states-state)
   8. [Exporting (`export`)](#exporting-export)
   9. [Validation (`validate`)](#validation)
   10. [Scripts (`script`)](#scripts-script)
   11. [Meta Commands](#meta-commands)
7. [Example Workflow (Interactive)](#example-workflow-interactive)
8. [License](#license)

---

## Main Features

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

### Build

```bash
git clone https://github.com/a-burigana/plank.git
cd plank
mkdir build && cd build
cmake ..
make
````

The resulting `plank` executable can be used directly.

---

## EPDDL

For details on the **EPDDL language**, JSON export format, and modeling guidelines,
please refer to the **EPDDL Official Guideline**.

---

## Usage Overview

`plank` supports **two complementary modalities**:

1. **Non-interactive command-line interface**:
   for single-shot operations, like parsing, task exportation and plan validation.

2. **Interactive command-line interface**:
   for exploratory modeling, debugging, visualization, and incremental development of EPDDL specifications.

Running `plank` **without arguments** starts the interactive CLI:

```bash
plank
```

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

* an EPDDL **domain**
* an EPDDL **problem**
* zero or more **action-type libraries**

#### 2. Specification file

Provide a single **EPDDL specification file** (`.json`) with the following structure:

```json
{
    "domain": "<path to domain>",
    "problem": "<path to problem>",
    "action-type-libraries": [
        "<path to library>",
        "...",
        "<path to library>"
    ]
}
```

Specification files can be automatically generated from the interactive CLI using:

```text
task save-spec <path>
```

---

### Command Synopsis

#### Parsing and Type-Checking

```bash
plank parse -d <domain path> -p <problem path> [-l <libraries paths>...]
plank parse -s <specification path>
```

---

#### Grounding

```bash
plank ground -d <domain path> -p <problem path> [-l <libraries paths>...]
plank ground -s <specification path>
```

---

#### Exporting

Export a ground epistemic planning task to **JSON** (EPDDL official format):

```bash
plank export -d <domain path> -p <problem path> [-l <libraries paths>...] \
             -o <path to directory>

plank export -s <specification path> -o <path to directory>
```

---

#### Validation

Validate an action sequence on the given EPDDL specification:

```bash
plank validate -d <domain path> -p <problem path> [-l <libraries paths>...] \
               -a <actions>...

plank validate -s <specification path> -a <actions>...
```

If no actions are provided, the goal formula is checked on the initial epistemic state.

---

#### Help

```bash
plank help
```

Prints the complete non-interactive CLI man page.

---

## Interactive Command-Line Interface

Running `plank` without arguments starts an **interactive session** that maintains state
across commands.

The interactive CLI allows users to:

* Manage multiple epistemic planning tasks
* Load and modify EPDDL specifications
* Define formulas and epistemic states
* Apply actions, check formulas, and validate plans
* Export states, actions, and tasks
* Run user-defined scripts

---

For detailed documentation of any command, use:

```text
man <command>
```

---

### Navigation & Session Management

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

```text
task add <task>
task remove <task>
task rename <task> <new-task>
task copy <task> <new-task>
task open <task>
task close
task switch <task>
task save-spec <path>
```

---

### Loading EPDDL Files (`load`)

```text
load domain <file>
load problem <file>
load library <file>
load spec <file>
```

---

### Parsing and Grounding

| Command  | Description                                    |
| -------- | ---------------------------------------------- |
| `parse`  | Parse and type-check the current specification |
| `ground` | Compute the ground epistemic planning task     |

Grounding may invalidate existing states and formulas if the logical language changes.
When this happens, `plank` interactively asks how to proceed.

---

### Showing Task Data (`show`)

```text
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

---

### Formulas (`formula`)

```text
formula add <name> <formula>
formula add-goal <name>
formula remove <name>
formula rename <name> <new-name>
formula copy <name> <new-name>
```

Formulas can reference existing ones using `$name` (recursively).

---

### Epistemic States (`state`)

Create, update, and analyze epistemic states:

```text
state add-init <name> [-g]
state remove <name>
state rename <name> <new-name>
state copy <name> <new-name>
state check <state> <formula>
state applicable <state> <actions>... [-g]
state update <state> <actions>... [options]
state contract <state> [options]
```

Features include:

* Action application
* Applicability checking
* Formula satisfaction
* Bisimulation contraction
* Optional export to Graphviz formats

---

### Exporting (`export`)

```text
export task <task> [-g] [dir]
export state <state>|--all [dir] [format]
export action <action>|--all [-g] [dir] [format]
```

---

### Validation (`validate`)

```text
validate [<actions>...] [-g]
```

---

### Scripts (`script`)

```text
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

```text
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

MIT
