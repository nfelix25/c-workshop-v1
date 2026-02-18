	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$712, %rsp                      ## imm = 0x2C8
	.cfi_offset %rbx, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movl	$0, -548(%rbp)
	leaq	L_.str.1(%rip), %rdi
	xorl	%esi, %esi
	movb	$0, %al
	callq	_open
	movl	%eax, -552(%rbp)
	movq	_path(%rip), %rdi
	xorl	%esi, %esi
	movb	$0, %al
	callq	_open
	movl	%eax, -556(%rbp)
	cmpl	$-1, -552(%rbp)
	jne	LBB0_2
## %bb.1:
	movl	-552(%rbp), %eax
	movl	%eax, -652(%rbp)                ## 4-byte Spill
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	movl	-652(%rbp), %esi                ## 4-byte Reload
	movq	%rax, %rdx
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB0_2:
	movl	-556(%rbp), %esi
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	-544(%rbp), %rsi
	movl	$10, %edi
	movl	$500, %edx                      ## imm = 0x1F4
	callq	_read
	movq	%rax, -568(%rbp)
	cmpq	$-1, -568(%rbp)
	jne	LBB0_4
## %bb.3:
	movq	-568(%rbp), %rax
	movq	%rax, -664(%rbp)                ## 8-byte Spill
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	movq	-664(%rbp), %rsi                ## 8-byte Reload
	movq	%rax, %rdx
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB0_5
LBB0_4:
	movq	-568(%rbp), %rdx
	leaq	L_.str.5(%rip), %rdi
	movl	$500, %esi                      ## imm = 0x1F4
	movb	$0, %al
	callq	_printf
LBB0_5:
	movl	-556(%rbp), %edi
	leaq	-544(%rbp), %rsi
	movl	$500, %edx                      ## imm = 0x1F4
	callq	_read
	movq	%rax, -576(%rbp)
	cmpq	$-1, -576(%rbp)
	jne	LBB0_7
## %bb.6:
	movq	-576(%rbp), %rax
	movq	%rax, -672(%rbp)                ## 8-byte Spill
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	movq	-672(%rbp), %rsi                ## 8-byte Reload
	movq	%rax, %rdx
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB0_8
LBB0_7:
	movq	-576(%rbp), %rdx
	leaq	L_.str.5(%rip), %rdi
	movl	$500, %esi                      ## imm = 0x1F4
	movb	$0, %al
	callq	_printf
LBB0_8:
	movl	-556(%rbp), %edi
	leaq	-648(%rbp), %rsi
	callq	_fstat$INODE64
	cmpl	$-1, %eax
	jne	LBB0_10
## %bb.9:
	callq	___error
	movl	(%rax), %eax
	movl	%eax, -676(%rbp)                ## 4-byte Spill
	callq	___error
	movl	(%rax), %edi
	callq	_strerror
	movl	-676(%rbp), %esi                ## 4-byte Reload
	movq	%rax, %rdx
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB0_10:
	leaq	L_.str.6(%rip), %rdi
	movl	$72, %esi
	movb	$0, %al
	callq	_printf
	movl	-648(%rbp), %esi
	movq	-640(%rbp), %rdx
	movzwl	-632(%rbp), %ecx
	movzwl	-630(%rbp), %r8d
	movl	-628(%rbp), %r9d
	movl	-624(%rbp), %r15d
	movq	-616(%rbp), %r14
	movl	-608(%rbp), %ebx
	movq	-600(%rbp), %r11
	movq	-592(%rbp), %r10
	movq	-584(%rbp), %rax
	leaq	L_.str.7(%rip), %rdi
	movl	%r15d, (%rsp)
	movq	%r14, 8(%rsp)
	movl	%ebx, 16(%rsp)
	movq	%r11, 24(%rsp)
	movq	%r10, 32(%rsp)
	movq	%rax, 40(%rsp)
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-32(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB0_12
## %bb.11:
	xorl	%eax, %eax
	addq	$712, %rsp                      ## imm = 0x2C8
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB0_12:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"index.html"

	.section	__DATA,__data
	.globl	_path                           ## @path
	.p2align	3, 0x0
_path:
	.quad	L_.str

	.section	__TEXT,__cstring,cstring_literals
L_.str.1:                               ## @.str.1
	.asciz	"ERRRRR"

L_.str.2:                               ## @.str.2
	.asciz	"Error: %d\nCause: %s\n\n"

L_.str.3:                               ## @.str.3
	.asciz	"FD: %d\n\n"

L_.str.4:                               ## @.str.4
	.asciz	"Error: %zd bytes read.\nCause: %s\n\n"

L_.str.5:                               ## @.str.5
	.asciz	"Buffer size: %d\nActual size: %zd\n\n"

L_.str.6:                               ## @.str.6
	.asciz	"%zd"

L_.str.7:                               ## @.str.7
	.asciz	"Device ID: %d\nInode Number: %llu\nProtection: %d\nHard Links: %d\nUser ID: %d\nGroup ID: %d\nSize: %lld\nBlock Size: %d\nAccess Time: %ld\nModification Time: %ld\nStatus Change Time: %ld\n\n"

.subsections_via_symbols
