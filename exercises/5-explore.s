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
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$2, %edi
	movl	$1, %esi
	xorl	%edx, %edx
	callq	_socket
	movl	%eax, -8(%rbp)
	movl	$1, -12(%rbp)
	movl	-8(%rbp), %edi
	movl	$65535, %esi                    ## imm = 0xFFFF
	movl	$4, %r8d
	leaq	-12(%rbp), %rcx
	movl	%r8d, %edx
	callq	_setsockopt
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
