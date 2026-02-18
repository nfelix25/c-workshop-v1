	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_find_next_break                ## -- Begin function find_next_break
	.p2align	4, 0x90
_find_next_break:                       ## @find_next_break
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rax
	movsbl	(%rax), %ecx
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	cmpl	$32, %ecx
	movb	%al, -17(%rbp)                  ## 1-byte Spill
	je	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$0, %eax
	setne	%al
	movb	%al, -17(%rbp)                  ## 1-byte Spill
LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
	movb	-17(%rbp), %al                  ## 1-byte Reload
	testb	$1, %al
	jne	LBB0_4
	jmp	LBB0_5
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	LBB0_1
LBB0_5:
	movq	-16(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_my_first_attempted_to_path     ## -- Begin function my_first_attempted_to_path
	.p2align	4, 0x90
_my_first_attempted_to_path:            ## @my_first_attempted_to_path
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	callq	_find_next_break
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdi
	addq	$1, %rdi
	callq	_find_next_break
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$0, %eax
	jne	LBB1_2
## %bb.1:
	movq	$0, -8(%rbp)
	jmp	LBB1_7
LBB1_2:
	movq	-24(%rbp), %rax
	movsbl	1(%rax), %eax
	cmpl	$47, %eax
	jne	LBB1_4
## %bb.3:
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
LBB1_4:
	movq	-32(%rbp), %rax
	movsbl	-1(%rax), %eax
	cmpl	$47, %eax
	jne	LBB1_6
## %bb.5:
	movq	-32(%rbp), %rax
	addq	$-1, %rax
	movq	%rax, -32(%rbp)
LBB1_6:
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	subq	%rcx, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -88(%rbp)                 ## 8-byte Spill
	movq	_DEFAULT_FILE(%rip), %rdi
	callq	_strlen
	movq	%rax, %rcx
	movq	-88(%rbp), %rax                 ## 8-byte Reload
	addq	%rcx, %rax
	addq	$2, %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdi
	callq	_malloc
	movq	%rax, -56(%rbp)
	leaq	L_.str.1(%rip), %rax
	movq	%rax, -64(%rbp)
	movq	-56(%rbp), %rdi
	movq	-24(%rbp), %rsi
	movq	-40(%rbp), %rdx
	movq	$-1, %rcx
	callq	___memcpy_chk
	movq	-56(%rbp), %rdi
	addq	-40(%rbp), %rdi
	movq	-64(%rbp), %rsi
	movl	$1, %edx
	movq	$-1, %rcx
	callq	___memcpy_chk
	movq	-56(%rbp), %rax
	addq	-40(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -80(%rbp)                 ## 8-byte Spill
	movq	_DEFAULT_FILE(%rip), %rax
	movq	%rax, -72(%rbp)                 ## 8-byte Spill
	movq	_DEFAULT_FILE(%rip), %rdi
	callq	_strlen
	movq	-80(%rbp), %rdi                 ## 8-byte Reload
	movq	-72(%rbp), %rsi                 ## 8-byte Reload
	movq	%rax, %rdx
	movq	$-1, %rcx
	callq	___memcpy_chk
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rcx
	subq	$1, %rcx
	movb	$0, (%rax,%rcx)
	movq	-56(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -8(%rbp)
LBB1_7:
	movq	-8(%rbp), %rax
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_to_path                        ## -- Begin function to_path
	.p2align	4, 0x90
_to_path:                               ## @to_path
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	callq	_strlen
	movq	%rax, -40(%rbp)
	movq	_DEFAULT_FILE(%rip), %rdi
	callq	_strlen
	movq	%rax, -48(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$32, %eax
	je	LBB2_6
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movq	-24(%rbp), %rax
	cmpb	$0, (%rax)
	jne	LBB2_4
## %bb.3:
	movq	$0, -8(%rbp)
	jmp	LBB2_18
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_5
LBB2_5:                                 ##   in Loop: Header=BB2_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB2_1
LBB2_6:
	movq	-24(%rbp), %rax
	movsbl	1(%rax), %edx
	movl	$1, %eax
	movl	$2, %ecx
	cmpl	$47, %edx
	cmovel	%ecx, %eax
	movl	%eax, -52(%rbp)
	movl	-52(%rbp), %ecx
	movq	-24(%rbp), %rax
	movslq	%ecx, %rcx
	addq	%rcx, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -32(%rbp)
LBB2_7:                                 ## =>This Inner Loop Header: Depth=1
	movq	-32(%rbp), %rax
	movsbl	(%rax), %eax
	cmpl	$32, %eax
	je	LBB2_15
## %bb.8:                               ##   in Loop: Header=BB2_7 Depth=1
	movq	-32(%rbp), %rax
	cmpb	$0, (%rax)
	je	LBB2_10
## %bb.9:                               ##   in Loop: Header=BB2_7 Depth=1
	movq	-32(%rbp), %rax
	addq	-48(%rbp), %rax
	movq	-16(%rbp), %rcx
	addq	-40(%rbp), %rcx
	cmpq	%rcx, %rax
	jbe	LBB2_13
LBB2_10:
	movq	-32(%rbp), %rax
	cmpb	$0, (%rax)
	jne	LBB2_12
## %bb.11:
	movq	$0, -8(%rbp)
	jmp	LBB2_18
LBB2_12:
	movq	-16(%rbp), %rdi
	callq	_my_first_attempted_to_path
	movq	%rax, -8(%rbp)
	jmp	LBB2_18
LBB2_13:                                ##   in Loop: Header=BB2_7 Depth=1
	jmp	LBB2_14
LBB2_14:                                ##   in Loop: Header=BB2_7 Depth=1
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -32(%rbp)
	jmp	LBB2_7
LBB2_15:
	movq	-32(%rbp), %rax
	movsbl	-1(%rax), %eax
	cmpl	$47, %eax
	je	LBB2_17
## %bb.16:
	movq	-32(%rbp), %rax
	movb	$47, (%rax)
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -32(%rbp)
LBB2_17:
	movq	-32(%rbp), %rax
	movq	%rax, -72(%rbp)                 ## 8-byte Spill
	movq	_DEFAULT_FILE(%rip), %rax
	movq	%rax, -64(%rbp)                 ## 8-byte Spill
	movq	_DEFAULT_FILE(%rip), %rdi
	callq	_strlen
	movq	-72(%rbp), %rdi                 ## 8-byte Reload
	movq	-64(%rbp), %rsi                 ## 8-byte Reload
	movq	%rax, %rdx
	addq	$1, %rdx
	movq	$-1, %rcx
	callq	___memcpy_chk
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB2_18:
	movq	-8(%rbp), %rax
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
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
	subq	$160, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -160(%rbp)
	leaq	-48(%rbp), %rdi
	leaq	L___const.main.req1(%rip), %rsi
	movl	$37, %edx
	callq	_memcpy
	leaq	-48(%rbp), %rdi
	callq	_to_path
	movq	%rax, %rsi
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	-96(%rbp), %rdi
	leaq	L___const.main.req2(%rip), %rsi
	movl	$38, %edx
	callq	_memcpy
	leaq	-96(%rbp), %rdi
	callq	_to_path
	movq	%rax, %rsi
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	-144(%rbp), %rdi
	leaq	L___const.main.req3(%rip), %rsi
	movl	$33, %edx
	callq	_memcpy
	leaq	-144(%rbp), %rdi
	callq	_to_path
	movq	%rax, %rsi
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	L___const.main.req4(%rip), %rax
	movq	%rax, -155(%rbp)
	movw	L___const.main.req4+8(%rip), %ax
	movw	%ax, -147(%rbp)
	movb	L___const.main.req4+10(%rip), %al
	movb	%al, -145(%rbp)
	leaq	-155(%rbp), %rdi
	callq	_to_path
	movq	%rax, %rsi
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB3_2
## %bb.1:
	xorl	%eax, %eax
	addq	$160, %rsp
	popq	%rbp
	retq
LBB3_2:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"index.html"

	.section	__DATA,__data
	.globl	_DEFAULT_FILE                   ## @DEFAULT_FILE
	.p2align	3, 0x0
_DEFAULT_FILE:
	.quad	L_.str

	.section	__TEXT,__cstring,cstring_literals
L_.str.1:                               ## @.str.1
	.asciz	"/"

	.p2align	4, 0x0                          ## @__const.main.req1
L___const.main.req1:
	.asciz	"GET /blog HTTP/1.1\nHost: example.com"

L_.str.2:                               ## @.str.2
	.asciz	"Should be \"blog/index.html\": \"%s\"\n"

	.p2align	4, 0x0                          ## @__const.main.req2
L___const.main.req2:
	.asciz	"GET /blog/ HTTP/1.1\nHost: example.com"

	.p2align	4, 0x0                          ## @__const.main.req3
L___const.main.req3:
	.asciz	"GET / HTTP/1.1\nHost: example.com"

L_.str.3:                               ## @.str.3
	.asciz	"Should be \"index.html\": \"%s\"\n"

L___const.main.req4:                    ## @__const.main.req4
	.asciz	"GET /blog "

L_.str.4:                               ## @.str.4
	.asciz	"Should be \"(null)\": \"%s\"\n"

.subsections_via_symbols
