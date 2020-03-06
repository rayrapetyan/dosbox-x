include super.inc
BGM_STAT_PLAY	equ	1	;���^�[���R�[�h
BGM_STAT_MUTE	equ	0
BGM_STAT_REPT	equ	1
BGM_STAT_1TIM	equ	0
BGM_STAT_ON	equ	1
BGM_STAT_OFF	equ	0
BGM_MES_ON	equ	1	;�p�����[�^
BGM_MES_OFF	equ	0
BGM_MUSIC	equ	1
BGM_SOUND_	equ	2
; ��'BGM_SOUND'���ύX
BGM_COMPLETE	equ	NoError ; �G���[�i���o�[
BGM_FILE_ERR	equ	FileNotFound
BGM_FORMAT_ERR	equ	InvalidFormat
BGM_OVERFLOW	equ	InsufficientMemory
BGM_TOOMANY	equ	InvalidData
BGM_NO_MUSIC	equ	InvalidData
BGM_NOT_PLAY	equ	GeneralFailure
BGM_NOT_STOP	equ	GeneralFailure
BGM_EXTENT_ERR	equ	InvalidData

ON		equ	1
OFF		equ	0
TRUE		equ	1
FALSE		equ	0
FINISH		equ	1
NOTFIN		equ	0
SEND		equ	0
VEND		equ	0
BEEP_SW		equ	37h	;�|�[�g�A�h���X�E�ݒ�l
BEEP_ON		equ	06h
BEEP_OFF	equ	07h
BEEP_CNT	equ	3fdbh
BEEP_MODE	equ	3fdfh
BEEP_CNT_AT	equ	42h
BEEP_MODE_AT	equ	43h
INTCTRL		equ	00h
EOI		equ	20h
IMR		equ	02h
TIMERMASK	equ	01h
TIMER_CNT	equ	71h
TIMER_SET	equ	77h
CLOCK_CHK	equ	42h
PMAX		equ	3	;�p�[�g��
ALL_PART	equ	7	;���t�I���`�F�b�N�p
BUFMAX		equ	4096	;�P�p�[�g�̃o�b�t�@��
SBUFMAX		equ	256	;���ʉ��P���̃o�b�t�@��
MINNOTE		equ	32	;�ŏ�����
MINLCNT		equ	1	;�ŏ��J�E���g�f�[�^
DEFTEMPO	equ	120	;�f�t�H���g�e���|
TEMPOMAX	equ	240	;�ő�e���|
TEMPOMIN	equ	30	;�ŏ��e���|
DEFOCT		equ	4	;�f�t�H���g�I�N�^�[�u
DEFLEN		equ	4	;�f�t�H���g����
DEFLCNT		equ	8	;�f�t�H���g�����J�E���g�l
DIVNUM		equ	8	;1�I�N�^�[�u�̉���
REST		equ	'H'	;�x��
UNDF		equ	100	;����`����
MMAX		equ	16	;�ő�Ȑ�
SMAX		equ	16	;�ő���ʉ���
TIMER		equ	1	;�^�C�}	=	1ms
TVAL8ORG	equ	1997	;�^�C�}�ݒ�l	8MHz(1msec)
TVAL10ORG	equ	2458	;�^�C�}�ݒ�l	10MHz(1msec)
TVALATORG_RTC	equ	16	;�^�C�}�ݒ�l   8192Hz*2(AT�݊��@) (1msec)
TVALATORG	equ	1193	;�^�C�}�ݒ�l  1193.18K(AT�݊��@) (1msec)
TVAL8ORG2	equ	19968	;�^�C�}�ݒ�l	8MHz(10msec)
TVAL10ORG2	equ	24576	;�^�C�}�ݒ�l	10MHz(10msec)
;TVALATORG2	equ	41	;�^�C�}�ݒ�l   4096Hz(AT�݊��@) (10msec)
;TVALATORG2	equ	11931	;�^�C�}�ݒ�l  1193.18K(AT�݊��@) (10msec)
TCNTMAX		equ	20	;���荞�݉����	1�񏈗����邩

;
;�X�e�[�^�X�\����
;
SBSTAT		struc
bmusic		dw	?	;���t���� ON/OFF
bsound		dw	?	;���ʉ����� ON/OFF
bplay		dw	?	;���t�����ۂ�
beffect		dw	?	;���ʉ��o�͒����ۂ�
brepeat		dw	?	;���s�[�g���t���ۂ�
bmnum		dw	?	;�o�^�Ȑ�
brnum		dw	?	;�Z���N�g���Ȕԍ�
btempo		dw	?	;���݂̃e���|
bsnum		dw	?	;�o�^���ʉ���
bfnum		dw	?	;�Z���N�g�����ʉ��ԍ�
SBSTAT		ends

;
;�O���[�o���f�[�^�\����
;
SGLB		struc
simr		dw	?	;interrupt mask register
; ��'imr'���ύX
tval		dw	?	;�^�C�}�ݒ�l
tp		dw	?	;�e���|
rflg		dw	?	;BGM ON/OFF
pnum		dw	?	;�p�[�g��
pcnt		dw	?	;�p�[�g�J�E���^
fin		dw	?	;�p�[�g�I���t���O
repsw		dw	?	;���s�[�g ON/OFF
; ��'rep'���ύX
tcnt		dw	?	;�����J�E���^(4��� 1�񏈗�)
bufsiz		dw	?	;�y���o�b�t�@�̃T�C�Y
buflast		dw	?	;�y���o�b�t�@�̃��X�g
mnum		dw	?	;�o�^�Ȑ�
mcnt		dw	?	;�Z���N�g���Ȕԍ�
track		dw	MMAX dup(?)	;�Ȃ̃g���b�N�i���o�[
pmask		dw	?	;�p�[�g�}�X�N���
; ��'mask'���ύX
mtp		dw	MMAX dup(?)	;�Ȃ��Ƃ̃e���|���
effect		dw	?	;���ʉ� ON/OFF
snum		dw	?	;�o�^���ʉ���
scnt		dw	?	;�Z���N�g�����ʉ��ԍ�
music		dw	?	;���t���� ON/OFF
sound		dw	?	;���ʉ����� ON/OFF
init		dw	?	;�C�j�V�����C�Y���s�t���O
clockbase	dd	?	;tempo120���̃^�C�}�J�E���g
SGLB		ends

;
;�p�[�g�\����
;
SPART struc
pptr		dd	?	;�y���o�b�t�@�|�C���^
; ��'ptr'���ύX
mbuf		dd	?	;�y���o�b�t�@
note		dw	?	;���݂̉���
oct		dw	?	;���݂̃I�N�^�[�u
len		dw	?	;���݂̉���
dflen		dw	?	;�f�t�H���g�̉���
lcnt		dw	?	;�����J�E���^
msk		dw	?	;�p�[�g�}�X�N ON/OFF
; ��'mask'���ύX
tnt		dw	?	;�e�k�[�g ON/OFF
SPART ends

;
;���ʉ��\����
;
SESOUND struc
sptr		dd	?	;���ʉ��f�[�^�|�C���^
sbuf		dd	?	;���ʉ��f�[�^�o�b�t�@
SESOUND ends