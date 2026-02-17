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
	subq	$80, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -36(%rbp)
	movq	L___const.main.msg(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	L___const.main.msg+8(%rip), %rax
	movq	%rax, -24(%rbp)
	movw	L___const.main.msg+16(%rip), %ax
	movw	%ax, -16(%rbp)
	movb	L___const.main.msg+18(%rip), %al
	movb	%al, -14(%rbp)
	movq	$19, -48(%rbp)
	movq	-48(%rbp), %rax
	subq	$1, %rax
	movb	$10, -32(%rbp,%rax)
	leaq	-32(%rbp), %rsi
	movq	-48(%rbp), %rdx
	movl	$1, %edi
	callq	_write
	leaq	L_.str(%rip), %rax
	movq	%rax, -56(%rbp)
	movl	$0, -60(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -72(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-72(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$0, %eax
	je	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-60(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -60(%rbp)
	movq	-72(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -72(%rbp)
	jmp	LBB0_1
LBB0_3:
	movq	-56(%rbp), %rsi
	movslq	-60(%rbp), %rdx
	movl	$1, %edi
	callq	_write
	movl	$42, -76(%rbp)
	movl	$67, -80(%rbp)
	movl	-76(%rbp), %esi
	movl	-80(%rbp), %edx
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB0_5
## %bb.4:
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	retq
LBB0_5:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
	.p2align	4, 0x0                          ## @__const.main.msg
L___const.main.msg:
	.asciz	"Greetings, Planet?"

L_.str:                                 ## @.str
	.asciz	"\360\237\230\200\n"

L_.str.1:                               ## @.str.1
	.asciz	"The number is: %d\t%d\n"

.subsections_via_symbols
