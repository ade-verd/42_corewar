Corewar
======

About
-----

>Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer.
These battle programs are written in an abstract assembly language called Redcode.

42 Version
----------

Here's how it looks like:

![Corewar](resources/screenshots/vm_sample.gif)

We don't use the same set of assembly instructions as the original Corewar and we have some modulo limitations for the read and write ranges.

Subjects: [corewar.fr.pdf](subject/corewar.fr.pdf) or [corewar.en.pdf](subject/corewar.en.pdf)

##### How to use it ?

* First you'll need to write a .s file with a set of assembly instructions
    * You can create your own champion with [this set below](#assembler-instructions)
    * Or you can just use one of the many warriors in the resources/champs directory
* Then you'll have to compile it using the `asm` binary
* Then just execute the `corewar` binary with your warrior(s) as arguments

>This was the final project of the Algorithm branch.

## Assembler instructions
--------

| OP | Effects | Charge | Changes the `carry` ? | Octal Coding | `DIR` Bytes |
|:-: | ------- | :----------------: | :--------------------: | :----------: | :----------------: |
| **`live`**<br /><br />`DIR` | `live` is followed by 4 bytes which represents the player's number as unsigned int. This instruction means the player is alive. | 10 | Non | Non | 4 |
| **`ld`**<br /><br />`DIR`&#124;`IND`, `REG` | `load`s a value from an address into a register.<br />*Example: `ld 34,r3` stores `REG_SIZE` octets from 34 bytes after the current address (`PC + (34 % IDX_MOD)`) into the register `r3`.*| 5 | Oui | Oui | 4 |
| **`st`**<br /><br />`REG`, `IND`&#124;`REG` | `st`ores the value of a register to an address or an other register.<br />*Example1: `st r4,34` stores the value of `r4` to the address `(PC + (34 % IDX_MOD))`*<br />*Example2: `st r3,r8` copies `r3` into `r8`* | 5 | Non | Oui | - |
| **`add`**<br /><br />`REG`, `REG`, `REG` | This instruction `add` takes 3 parameters: 3 registers. The third parameterc the result of the addition of the first and the second parameters. Example: `add r2,r3,r5` sums `r2` and `r3` and stores the result into `r5` | 10 | Oui | Oui | - |
| **`sub`**<br /><br />`REG`, `REG`, `REG` | Même que add mais soustraitOi | Oui | - |
| **`and`**<br /><br />`REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR`&#124;`IND`, `REG` | p1 & p2 -> p3 le paramètre 3 et toujours un registre. Cette opération modifie le carry. `and r2,%0,r3` met r2 & 0 dans r3 | 6 | Oui | Oui | 4 |
| **`or`**<br /><br />`REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR`&#124;`IND`, `REG` | Même que and mais avec le ou (&#124; binaire).| 6 | Oui | Oui | 4 |
| **`xor`**<br /><br />`REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR`&#124;`IND`, `REG` | Même que and mais avec le ou exclusif (^ binaire).| 6 | Oui | Oui | 4 |
| **`zjmp`**<br /><br />`DIR` | Cette instruction n’est pas suivie d’octet pour décrire les paramètres. Elle prend toujours un index (`IND_SIZE`) et fait un saut a cet index si le carry est à un. Si le carry est nul, zjmp ne fait rien mais consomme le même temps. `zjmp %23` met si carry == 1 met `(PC + (23 % IDX_MOD))` dans le PC. | 20 | Non | Non | 2 |
| **`ldi`**<br /><br />`REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR`, `REG` | Cette opération modifie le carry. `ldi 3,%4,r1` lit `IND_SIZE` octets à l’adresse : `(PC + (3 % IDX_MOD))` ajoute 4 à cette valeur. On nommera S cette somme. On lit `REG_SIZE` octets a l’adresse `(PC + (S % IDX_MOD))` qu’on copie dans r1. Les paramètre 1 et 2 sont des index.| 25 | Non | Oui | 2 |
| **`sti`**<br /><br />`REG`, `REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR` |`sti r2,%4,%5` sti copie `REG_SIZE` octets de r2 a l’adresse `(4 + 5)`. Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3 sont des registres, on utilisera leur contenu comme un index.| 25 | Non | Oui | 2 |
| **`fork`**<br /><br />`DIR` | Cette instruction n’est pas suivie d’octet pour décrire les paramètres. Elle prend toujours un index et crée un nouveau programme qui s’exécute a partir de l’adresse:`(PC + (premier paramètre % IDX_MOD))`<br>`fork %34` crée un nouveau programme. Le nouveau programme hérite des différents états du père.| 800 | Non | Non | 2 |
| **`lld`**<br /><br />`DIR`&#124;`IND`, `REG` | Comme ld sans le `%IDX_MOD` Cette opération modifie le carry.| 10 | Oui | Oui | 4 |
| **`lldi`**<br /><br />`REG`&#124;`DIR`&#124;`IND`, `REG`&#124;`DIR`, `REG` | Comme ldi sans le `%IDX_MOD` Cette opération modifie le carry.| 50 | Oui | Oui | 2 |
| **`lfork`**<br /><br />`DIR` | Comme fork sans le `%IDX_MOD` Cette opération modifie le carry.| 1000 | Non | Non | 2 |
| **`aff`**<br /><br />`REG` | Cette instruction est suivi d’un octet de paramétrage pour décrire les paramètres. Elle prend en paramètre un registre et affiche le caractère dont le code ascii est présent dans ce registre. (un modulo 256 est applique au code ascii, le caractère est affiché sur la sortie standard).<br>Ex :` ld %42,r3` puis `aff r3` affiche ’*’ sur la sortie standard. | 2 | Non | Oui | - |

Nota:
* `DIR`: Direct type: Number as unsigned int (4 bytes) or adress as unsigned short (2 bytes)
* `IND`: Indirect type: Relative address
* `REG`: Register type: Register which stores a numeric value

## Set up
------------

Just run `make`... then enjoy!

Works on OS X and Linux Debian / Ubuntu. The `nCurses` library is used for the viewer.

## Usage
-----

#### corewar - Virtual Machine
`./corewar [-hcvdD [cycle nb]] ([-n nb] file.cor) ...`

![usage_corewar](resources/screenshots/corewar_usage.jpg)

You can combine some flags. For example the flags -c (nCurses) and -v (Verbose)

![verbose](resources/screenshots/vm_sample_verbose.gif)

##### Keys
* <kbd>spacebar</kbd> Play / Pause
* <kbd>▲</kbd> or <kbd>▶</kbd> Speed up (respectively +1 or +10)
* <kbd>▼</kbd> or <kbd>◀</kbd> Speed down (respectively -1 or -10)
* <kbd>@</kbd> Go to cycle ... Then an integer superior than the current cycle is expected. Validate with <kbd>Enter</kbd>
* <kbd>end</kbd> Quit properly the program

#### asm - Assembler
`./asm [-adfh] file.s`

![usage_corewar](resources/screenshots/asm_usage.jpg)

#### rasm - Disassembler
`./rasm file.cor ...`

![usage_corewar](resources/screenshots/rasm_usage.jpg)
