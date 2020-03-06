.xlist
; Description
;	NEAR�ł�FAR�ł��A�Z���u�����ɑI��ݒ肷�邽�߂�include�t�@�C��
;
; Usage:
;	include���� NEARMODEL ����`����Ă���� near�ł𐶐����A
;	��`����Ă��Ȃ���� FAR��(Pascal�łƋ��p)�𐶐�����B
;	����ɁACOMPACTMODEL, MEDIUMMODEL���g����B
;	�@�A�Z���u���I�v�V����/D���g�p����ƃ\�[�X�̕ύX�Ȃ��ɗ�����
;	�������ł���B
;
; Author:
;	���ˏ��F
;
; History:
;	92/ 6/19 Initial
;	92/11/16 _push�Ȃǂ̃}�N���ǉ�
;	93/ 2/12 COMPACTMODEL, MEDIUMMODEL

.list
IFDEF NEARMODEL
  CALLMODEL equ NEAR
  RETSIZE EQU 1
  DATASIZE EQU 1
ENDIF
IFDEF COMPACTMODEL
  CALLMODEL equ NEAR
  RETSIZE EQU 1
  DATASIZE EQU 2
ENDIF
IFDEF MEDIUMMODEL
  CALLMODEL equ FAR
  RETSIZE EQU 2
  DATASIZE EQU 1
ENDIF
IFDEF FARMODEL
  CALLMODEL equ FAR
  RETSIZE EQU 2
  DATASIZE EQU 2
ENDIF

.xlist

; FUNC:
; �֐��̓�������w������}�N��
; <���s����ƃ}�N��ENDFUNC�����������B�����p���Ċ֐��̏I����w������>
func	macro	name
	public name
	EVEN
	name proc CALLMODEL
	endfunc macro
		EVEN
		name endp
	endm
endm

; RETFUNC:
; func�̊O�ɁA���A����������PROC��u���Ƃ��ɁA���̐擪���w������}�N��
; <���s����ƃ}�N��ENDFUNC�����������B�����p���Ċ֐��̏I����w������>
retfunc	macro name
	name proc CALLMODEL
	EVEN
	endfunc macro
		EVEN
		name endp
	endm
endm

; �����O�o�b�t�@�̃|�C���^�����ɐi�߂�
; �������e:
;	if ( ++reg == bufsize )
;		reg = 0 ;
; �j�󃌃W�X�^:
;	wreg
; ����:
;	wreg��reg�͓����T�C�Y�ł��邱��
RING_INC macro reg,bufsize,wreg
	inc	reg
	cmp	reg,bufsize
	sbb	wreg,wreg
	and	reg,wreg
	endm


; dest��cmpreg�𖳕����Ŕ�r���A���������̒l��dest�Ɋi�[����B
; �t���O:
;	���ʂ� 0 �Ȃ� zflag = 1
;	dest�̂ق���cmpreg��菬���������Ȃ� cy=1
; �j�󃌃W�X�^:
;	wreg
min2	macro dest,cmpreg,wreg
	sub	dest,cmpreg
	sbb	wreg,wreg
	and	dest,wreg
	add	dest,cmpreg
	endm

; �׈���mov (�I�y�����h�����ȏ����������x���Ƃ���̂�)
; word size��p
JMOV	MACRO	reg,lab
	mov	reg,1234h
	org	$-2
lab	dw	?
	ENDM


IF DATASIZE EQ 2
_push	MACRO reg
	push reg
	ENDM
_pop	MACRO reg
	pop reg
	ENDM
_lds	MACRO reg,mem
	lds reg,mem
	ENDM
_les	MACRO reg,mem
	les reg,mem
	ENDM
_mov	MACRO a,b
	mov a,b
	ENDM
_inc	MACRO a
	inc a
	ENDM
_add	MACRO a,b
	add a,b
	ENDM
s_inc	MACRO a
	ENDM
s_mov	MACRO a,b
	ENDM
s_push	MACRO a
	ENDM
s_pop	MACRO a
	ENDM
s_	MACRO a
	ENDM
l_	MACRO a
	a
	ENDM
ELSE
_push	MACRO reg
	ENDM
_pop	MACRO reg
	ENDM
_lds	MACRO reg,mem
	mov reg,mem
	ENDM
_les	MACRO reg,mem
	mov reg,mem
	ENDM
_mov	MACRO a,b
	ENDM
_inc	MACRO a
	ENDM
_add	MACRO a,b
	ENDM
s_inc	MACRO a
	inc a
	ENDM
s_mov	MACRO a,b
	mov a,b
	ENDM
s_push	MACRO a
	push a
	ENDM
s_pop	MACRO a
	pop a
	ENDM
s_	MACRO a
	a
	ENDM
l_	MACRO a
	ENDM
ENDIF

	; _call: ���Ȃ炸����Z�O�����g�ɂ���Ɣ����Ă��郋�[�`����call����
	; �Ƃ��Ɏg�p����}�N�� (94/1/1�ǉ�)
IF RETSIZE EQ 2
_call	MACRO place
	push	CS
	call	near ptr place
	ENDM
ELSE
_call	MACRO place
	call	near ptr place
	ENDM
ENDIF

.list