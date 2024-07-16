# Embedded-Systems-Verification

Verification tool for Verilog that uses SAT solving as a backend:
- Parses Verilog Modules
- Unrolls the transition Relation
- Converts to dimacs formatted CNF
- Finally calls the SAT Solver () to check whether the formula is satisfiable
- The result reveals whether the target state is reachable in some number of transitions from the initial state

Program Takes three inputs:
1. Name of verilog file to read
2. Number of times to unroll the transition relation in the sy,bolic search
3. The target state

Intructions on how to run code:

Compile: 
gcc -o {Name your executable file here} joshsilva_b.c 

Run: 
./{executable file here} {design file w/extension here} {Number of unrolling’s} {Target State} 

Example:
gcc -o joshsilva_b joshsilva_b.c 
./joshsilva_b ex1.v 10 11 
