#
# HW. 5 submission. JMP - Dec 12
#

FNC broken. other stuff works?
cond.slpy is an example of arithmetic, assignment, comparisons, loops & conditionals, and logic.

I haven't gotten functions working yet.

Hi Jim,
This Zip has my current work on HW5. I'm still working on it — trying to get
the new starter code to play nice with my HW4 submission. In the meatnime, I've
written translation code for all the exercise but have yet to test it. 
I'm feeling shaky on my return code for Func calls (step 6) but feeling
pretty confident in the earlier exercises.


NOTES:
- my old hw4, fixing block exposed an error where I had ASGN's return type as
 None instead of Void
- whil-goodtest says mismatch return types. in Defn::chck. procedures must
return, because def is expecting a type and void isn't a type we could feed it
    if i made rety a Rtns, and extracted type from it everywhere else i could
    fix this.


FIXED:
- empty print segfaults. fixed by loop xpns!
- weird error at the end of ifif. traced to individual calls to toMips.
Can't trace further in time. the spim file ends abruptly one label after the function. when called, there's an attempt to execute a non-instruction.
similarly, after whil. The file ends when beginning to set up the stack for 
the call?

tracing using the mips file, RTN is broken? the procedure setting temp to 0 is 
tranlated, but the RTN to temp doesn't get translated.

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

fixed!
