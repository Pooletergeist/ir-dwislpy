#
# HW. 5 submission. JMP - Dec 12
#

TODO: get expn's the right types for the MIPS-translation.
- literals get typed on parse
- everything else gets typed on check?
- change to everything typed on check. !!! will-solve!

Hi Jim,
This Zip has my current work on HW5. I'm still working on it — trying to get
the new starter code to play nice with my HW4 submission. In the meatnime, I've
written translation code for all the exercise but have yet to test it. 
I'm feeling shaky on my return code for Func calls (step 6) but feeling
pretty confident in the earlier exercises.

CHANGELOG:
 - implemented TMES, MNUS
 - implemented Equl, LsEq
 - added trans to all ast-nodes in .hh, added trans\_cdn to potential boolean 
    conditionals, conj/disj, not, func
 - added conditional translations
 - added logical translations
 - brought dwislpyc into makefile
 - changed dwislpy-main.hh to set program = prgm instead of main = prgm
 - started using dwislpy-main.hh from the HW5 starter code. 
 - defined SymT pointer in dwislpy-check.hh
 - defining other SymT methods in dwislpy-check.hh
 - Func Trans\_cndn
 - change defs in prgm::trans to a vector of defn\_ptrs instead of pair
 - copy dwislpy-mips into directory
 - finish making the SymT look like the starter code's
 - dwislpy-mips. change 120 my "defs" is a vector of Defn\_ptrs instead of pair
 - define trans methods for Proc, IDiv, IMod, IntC, StrC? (bogus 4 now)
 - copy spim and exceptions.s into my dir. make spim

dec 13: 3:07pm. hurray! hello, world is printable.

 - hmm. syntax error. * is unexpected. only expecting +, and, <

 - my executable is called dwislpy not dwislpyc.
 - it seems to get print(3\*4) right but not print("hello, world!"). why?
     - "Hello, World" gets assigned type Int during parse.

 - I really can't find out where expressions get their types in parsing, and 
    what I did to screw it up. I might have to restart.
 - there's no missing vtable for ast methods in the starter code but if you 
  add a partial AST.cc file it recognizes that there are, even if you remove it

