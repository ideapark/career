LLVM Language Reference Manual
==============================

#Abstract
#Introductoin
  -Well-Formedness
#Identifiers
#High Level Structure
  -Module Structure
  -Linkage Types
  -Calling Conventions
  -Visibility Styles
  -DLL Storage Classes
  -Thread Local Storage Models
  -Structure Types
  -Global Variables
  -Functions
  -Aliases
  -Comdats
  -Named Metadata
  -Parameter Attributes
  -Garbage Collector Strategy Names
  -Prefix Data
  -Prologue Data
  -Personality Function
  -Attribute Groups
  -Function Attributes
  -Operand Bundles
    +Deoptimization Operand Bundles
  -Module-Level Inline Assembly
  -Data Layout
  -Target Triple
  -Pointer Aliasing Rules
  -Volatile Memory Accesses
  -Memory Model for Concurrent Operations
  -Atomic Memory Ordering Constraints
  -Fast-Math Flags
  -Use-list Order Directives
#Type System
  -Void Type
  -Function Type
  -First Class Types
    +Single Value Types
      *Integer Type
      *Floating Point Types
      *X86_mmx Type
      *Pointer Type
      *Vector Type
    +Label Type
    +Token Type
    +Metadata Type
    +Aggregate Types
      *Array Type
      *Structure Type
      *Opaque Structure Types
#Constants
  -Simple Constants
  -Complex Constants
  -Global Variable and Function Addresses
  -Undefined Values
  -Posion Values
  -Addresses of Basic Blocks
  -Constant Expressions
#Other Values
  -Inline Assembler Expressions
    +Inline Asm Constraint String
      *Output constraints
      *Input constraints
      *Indirect inputs and outputs
      *Clobber constraints
      *Constraint Codes
      *Supported Constraint Code List
    +Asm template argument modifiers
    +Inline Asm Metadata
#Metadata
  -Metadata Nodes and Metadata Strings
    +Specialized Metadata Nodes
      *DLCompileUnit
      *DLFile
      *DLBasicType
      *DLSubroutineType
      *DLDerivedType
      *DLCompositeType
      *DLSubrange
      *DLEnumerator
      *DLTemplateTypeParameter
      *DLTemplateValueParameter
      *DLNamespace
      *DLGlobalVariable
      *DLSubprogram
      *DLLexicalBlock
      *DLLexicalBlockFile
      *DLLocation
      *DLLocalVariable
      *DLExpression
      *DLObjCProperty
      *DLImportedEntity
    +`tbaa` Metadata
    +`tbaa.struct` Metadata
    +`noalias` and `alias.scope` Metadata
    +`fpmath` Metadata
    +`range` Metadata
    +`unpredictable` Metadata
    +`llvm.loop`
    +`llvm.loop.vectorize` and `llvm.loop.interleave`
    +`llvm.loop.interleave.count` Metadata
    +`llvm.loop.vectorize.enable` Metadata
    +`llvm.loop.vectorize.width` Metadata
    +`llvm.loop.unroll`
    +`llvm.loop.unroll.count` Metadata
    +`llvm.loop.unroll.disable` Metadata
    +`llvm.loop.unroll.runtime.disable` Metadata
    +`llvm.loop.unroll.enable` Metadata
    +`llvm.loop.unroll.full` Metadata
    +`llvm.mem`
    +`llvm.mem.parallel_loop_access` Metadata
    +`llvm.bitsets`
    +`invariant.group` Metadata
#Module Flags Metadata
  -Objective-C Garbage Collection Module Flags Metadata
  -Automatic Linker Flags Module Flags Metadata
  -C type width Module Flags Metadata
#Intrinsic Global Variables
  -The `llvm.used` Global Variable
  -The `llvm.compiler.used` Global Variable
  -The `llvm.global_ctors` Global Variable
  -The `llvm.global_dtors` Global Variable
#Instruction Reference
  -Terminator Instructions
    +`ret` Instruction
    +`br` Instruction
    +`switch` Instruction
    +`indirectbr` Instruction
    +`invoke` Instruction
    +`resume` Instruction
    +`catchpad` Instruction
    +`catchendpad` Instruction
    +`catchret` Instruction
    +`cleanupendpad` Instruction
    +`cleanupret` Instruction
    +`terminatepad` Instruction
    +`unreachable` Instruction
  -Binary Operations
    +`add` Instruction
    +`fadd` Instruction
    +`sub` Instruction
    +`fsub` Instruction
    +`mul` Instruction
    +`fmul` Instruction
    +`udiv` Instruction
    +`sdiv` Instruction
    +`fdiv` Instruction
    +`urem` Instruction
    +`srem` Instruction
    +`frem` Instruction
  -Bitwise Binary Operations
    +`shl` Instruction
    +`lshr` Instruction
    +`ashr` Instruction
    +`and` Instruction
    +`or` Instruction
    +`xor` Instruction
  -Vector Operations
    +`extractelement` Instruction
    +`insertelement` Instruction
    +`shufflevector` Instruction
  -Aggregate Operations
    +`extractvalue` Instruction
    +`insertvalue` Instruction
  -Memory Access and Addressing Operations
    +`alloca` Instruction
    +`load` Instruction
    +`store` Instruction
    +`fence` Instruction
    +`cmpxchg` Instruction
    +`atomicrmw` Instruction
    +`getelementptr` Instruction
  -Conversion Operations
    +`trunc .. to` Instruction
    +`zext .. to` Instruction
    +`sext .. to` Instruction
    +`fptrunc .. to` Instruction
    +`fpext .. to` Instruction
    +`fptoui .. to` Instruction
    +`fptosi .. to` Instruction
    +`uitofp .. to` Instruction
    +`sitofp .. to` Instruction
    +`ptrtoint .. to` Instruction
    +`inttoptr .. to` Instruction
    +`bitcast .. to` Instruction
    +`addrspacecast .. to` Instruction
  -Other Operations
    +`icmp` Instruction
    +`fcmp` Instruction
    +`phi` Instruction
    +`select` Instruction
    +`call` Instruction
    +`va_arg` Instruction
    +`landingpad` Instruction
    +`cleanuppad` Instruction
#Intrinsic Functions
  -Variable Argument Handling Intrinsics
    +`llvm.va_start` Intrinsic
    +`llvm.va_end` Intrinsic
    +`llvm.va_copy` Intrinsic
  -Accurate Garbage Collectoin Intrinsics
    +Experimental Statepoint Intrinsics
    +`llvm.gcroot` Intrinsic
    +`llvm.gcread` Intrinsic
    +`llvm.gcwrite` Intrinsic
  -Code Generator Intrinsic
    +`llvm.returnaddress` Intrinsic
    +`llvm.frameaddress` Intrinsic
    +`llvm.localscape` and `llvm.localrecover` Intrinsics
    +`llvm.read_register` and `llvm.write_register` Intrinsics
    +`llvm.stacksave` Intrinsic
    +`llvm.stackrestore` Intrinsic
    +`llvm.prefetch` Intrinsic
    +`llvm.pcmarker` Intrinsic
    +`llvm.readcyclecounter` Intrinsic
    +`llvm.clear_cache` Intrinsic
    +`llvm.instrprof_increment` Intrinsic
    +`llvm.instrprof_value_profile` Intrinsic
  -Standard C Library Intrinsic
    +`llvm.memcpy` Intrinsic
    +`llvm.memmove` Intrinsic
    +`llvm.memset.*` Intrinsic
    +`llvm.sqrt.*` Intrinsic
    +`llvm.powi.*` Intrinsic
    +`llvm.sin.*` Intrinsic
    +`llvm.cos.*` Intrinsic
    +`llvm.pow.*` Intrinsic
    +`llvm.exp.*` Intrinsic
    +`llvm.exp2.*` Intrinsic
    +`llvm.log.*` Intrinsic
    *`llvm.log10.*` Intrinsic
    +`llvm.log2.*` Intrinsic
    +`llvm.fma.*` Intrinsic
    +`llvm.fabs.*` Intrinsic
    +`llvm.minnum.*` Intrinsic
    +`llvm.maxnum.*` Intrinsic
    +`llvm.copysign.*` Intrinsic
    +`llvm.floor.*` Intrinsic
    +`llvm.ceil.*` Intrinsic
    +`llvm.trunc.*` Intrinsic
    +`llvm.rint.*` Intrinsic
    +`llvm.nearbyint.*` Intrinsic
    +`llvm.round.*` Intrinsic
  -Bit Manipulation Intrinsic
    +`llvm.bitreverse.*` Intrinsic
    +`llvm.bswap.*` Intrinsic
    +`llvm.ctpop.*` Intrinsic
    +`llvm.ctlz.*` Intrinsic
    +`llvm.cttz.*` Intrinsic
  -Arthmetic with Overflow Intrinsic
    +`llvm.sadd.with.overflow.*` Intrinsic
    +`llvm.uadd.with.overflow.*` Intrinsic
    +`llvm.ssub.with.overflow.*` Intrinsic
    +`llvm.usub.with.overflow.*` Intrinsic
    +`llvm.smul.with.overflow.*` Intrinsic
    +`llvm.umul.with.overflow.*` Intrinsic
  -Specialised Arithmetic Intrinsic
    +`llvm.canoicalize.*` Intrinsic
    +`llvm.fmuladd.*` Intrinsic
    +`llvm.uabsdiff.*` and `llvm.sabsdiff.*` Intrinsic
  -Half Precision Floating Point Intrinsic
    +`llvm.convert.to.fp16` Intrinsic
    +`llvm.convert.from.fp16` Intrinsic
  -Debugger Intrinsics
  -Exception Handling Intrinsics
  -Trampoline Intrinsics
    +`llvm.init.trampoline` Intrinsic
    +`llvm.adjust.trampoline` Intrinsic
  -Masked Vector Load and Store Intrinsics
    +`llvm.masked.load.*` Intrinsics
    +`llvm.masked.store.*` Intrinsics
  -Masked Vector Gather and Scatter Intrinsics
    +`llvm.masked.gather.*` Intrinsics
    +`llvm.masked.scatter.*` Intrinsics
  -Memory Use Markers
    +`llvm.lifetime.start` Intrinsic
    +`llvm.lifetime.end` Intrinsic
    +`llvm.invariant.start` Intrinsic
    +`llvm.invariant.end` Intrinsic
    +`llvm.invariant.group.barrier` Intrinsic
  -General Intrinsics
    +`llvm.var.annotation` Intrinsic
    +`llvm.ptr.annotation` Intrinsic
    +`llvm.annotation.*` Intrinsic
    +`llvm.trap` Intrinsic
    +`llvm.debugtrap` Intrinsic
    +`llvm.stackprotector` Intrinsic
    +`llvm.stackprotectorcheck` Intrinsic
    +`llvm.objectsize` Intrinsic
    +`llvm.expect` Intrinsic
    +`llvm.assume` Intrinsic
    +`llvm.bitset.test` Intrinsic
    +`llvm.donothing` Intrinsic
  -Stack Map Intrinsics
