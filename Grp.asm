option casemap:none
public ClearScreen
public DrawRectFunc
public DrawCircleFunc
public DrawLHCircleFunc
public DrawRHCircleFunc
.data
	extern WRect : xmmword;
.code

ClearScreen PROC
;void ClearScreenFunc(RCX: DWORD* Buf, RDX: DWORD Col, R8: unsigned int BufSize)
	MOVD xmm0, edx;
	SHUFPS xmm0, xmm0, 00000000b;
	SHR r8, 2;
	CLR:
		MOVNTPS [rcx], xmm0;
		ADD rcx, 16;
		DEC r8;
		JNZ CLR;
	RET;
ClearScreen ENDP

DrawRectFunc PROC
;void DrawRectFunc(RCX: unsigned int XSx, RDX: unsigned int YSy, R8: DWORD* Buf, R9: DWORD Col)
	PUSH rax
	PUSH rbx
	PUSH r10
	XOR rax, rax;
	XOR rbx, rbx;
	XOR r10, r10;
	MOV ax, dx;
	MOV ebx, edx;
	SHR ebx, 16;
	MOV r10w, cx;
	SHR ecx, 16;
	MOV edi, DWORD PTR [WRect + 8]
	MUL edi;
	ADD rax, r10;
	SHL rax, 2
	ADD r8, rax;
	CYC:
		MOV eax, ecx;
		C1:
			MOV [r8], r9d;
			ADD r8, 4;
			DEC eax;
			JNZ C1;
		MOV eax, edi;
		SUB eax, ecx;
		SHL rax, 2;
		ADD r8, rax;
		DEC ebx;
		JNZ CYC;
	POP r10
	POP rbx
	POP rax
	RET;
DrawRectFunc ENDP

DrawCircleFunc PROC
;void DrawCircleFunc(RCX: unsigned int XY, RDX: unsigned int Rad, R8: DWORD* Buf, R9: DWORD Col)
	PUSH rax;
	PUSH rbx;
	PUSH r10;
	XOR rax, rax;
	XOR rbx, rbx;
	XOR r10, r10;
	MOV ax, cx;
	CVTSI2SS xmm0, eax;
	SHR ecx, 16;
	MOV r10d, edx;
	CVTSI2SS xmm1, edx;
	MULSS xmm1, xmm1;
	SUB eax, r10d;
	MOV ebx, eax;
	MOV edi, DWORD PTR [WRect + 8]
	MUL edi;
	ADD eax, ecx;
	SHL rax, 2;
	ADD r8, rax;
	SHL r10d, 1;
	CYC:
		CVTSI2SS xmm2, ebx;
		SUBSS xmm2, xmm0;
		MULSS xmm2, xmm2;
		MOVSS xmm3, xmm1;
		SUBSS xmm3, xmm2;
		SQRTSS xmm3, xmm3;
		CVTSS2SI ecx, xmm3;
		CMP ecx, 0;
		JLE CNT;
		MOV eax, ecx;
		SHL rax, 2;
		SUB r8, rax;
		SHR rax, 1;
		C1:
			MOV [r8], r9d;
			ADD r8, 4;
			DEC eax;
			JNZ C1;
		MOV eax, edi;
		SUB eax, ecx;
		SHL rax, 2;
		ADD r8, rax;
		CNT: INC ebx;
		DEC r10d;
		JNZ CYC
	POP r10;
	POP rbx;
	POP rax;
	RET;
DrawCircleFunc ENDP

DrawLHCircleFunc PROC
	PUSH rax;
	PUSH rbx;
	PUSH r10;
	XOR rax, rax;
	XOR rbx, rbx;
	XOR r10, r10;
	MOV ax, cx;
	CVTSI2SS xmm0, eax;
	SHR ecx, 16;
	MOV r10d, edx;
	CVTSI2SS xmm1, edx;
	MULSS xmm1, xmm1;
	SUB eax, r10d;
	MOV ebx, eax;
	MOV edi, DWORD PTR [WRect + 8]
	MUL edi;
	ADD eax, ecx;
	SHL rax, 2;
	ADD r8, rax;
	SHL r10d, 1;
	CYC:
		CVTSI2SS xmm2, ebx;
		SUBSS xmm2, xmm0;
		MULSS xmm2, xmm2;
		MOVSS xmm3, xmm1;
		SUBSS xmm3, xmm2;
		SQRTSS xmm3, xmm3;
		CVTSS2SI ecx, xmm3;
		CMP ecx, 0;
		JLE CNT;
		MOV eax, ecx;
		SHL rax, 2;
		SUB r8, rax;
		C1:
			MOV [r8], r9d;
			ADD r8, 4;
			DEC ecx;
			JNZ C1;
		MOV eax, edi;
		SHL rax, 2;
		ADD r8, rax;
		CNT: INC ebx;
		DEC r10d;
		JNZ CYC
	POP r10;
	POP rbx;
	POP rax;
	RET;
DrawLHCircleFunc ENDP

DrawRHCircleFunc PROC
	PUSH rax;
	PUSH rbx;
	PUSH r10;
	XOR rax, rax;
	XOR rbx, rbx;
	XOR r10, r10;
	MOV ax, cx;
	CVTSI2SS xmm0, eax;
	SHR ecx, 16;
	MOV r10d, edx;
	CVTSI2SS xmm1, edx;
	MULSS xmm1, xmm1;
	SUB eax, r10d;
	MOV ebx, eax;
	MOV edi, DWORD PTR [WRect + 8]
	MUL edi;
	ADD eax, ecx;
	SHL rax, 2;
	ADD r8, rax;
	SHL r10d, 1;
	CYC:
		CVTSI2SS xmm2, ebx;
		SUBSS xmm2, xmm0;
		MULSS xmm2, xmm2;
		MOVSS xmm3, xmm1;
		SUBSS xmm3, xmm2;
		SQRTSS xmm3, xmm3;
		CVTSS2SI ecx, xmm3;
		CMP ecx, 0;
		JLE CNT;
		MOV eax, ecx;
		C1:
			MOV [r8], r9d;
			ADD r8, 4;
			DEC eax;
			JNZ C1;
		MOV eax, edi;
		SUB eax, ecx;
		SHL rax, 2;
		ADD r8, rax;
		CNT: INC ebx;
		DEC r10d;
		JNZ CYC
	POP r10;
	POP rbx;
	POP rax;
	RET;
DrawRHCircleFunc ENDP

end