.p2align 2,,3
.syntax unified
.text
wpad:
	.word 935519
	.word 3270578671
	.word 4178049256
    .word 4229564656
    .word 4145154150
    .word 120453728
    .word 68549511
    .word 116918269
    .word 4191091008
    .word 4174248584

.global Good17x9_Rader17
.type Good17x9_Rader17, %function
Good17x9_Rader17:
    push {r2-r12, lr}
	adr lr, wpad
    vmov s0, r0
    vmov s1, r1
	vldm lr, {s2-s11}
    mov.w r12, #0
	add.w lr, r0, #20
Good_Rader_part1_0:
	ldr.w r2, [r1, #900]
	ldr.w r3, [r1, #1440]
	ldr.w r4, [r1, #1260]
	ldr.w r5, [r1, #720]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	ssub16 r6, r12, r3
	ssub16 r7, r12, r4
	ssub16 r8, r12, r5
	pkhbt r9, r3, r4, lsl #16
	pkhtb r3, r4, r3, asr #16
	pkhbt r10, r6, r7, lsl #16
	pkhtb r6, r7, r6, asr #16
	pkhbt r4, r5, r2, lsl #16
	pkhtb r5, r2, r5, asr #16
	pkhbt r7, r8, r2, lsl #16
	pkhtb r8, r2, r8, asr #16
	str.w r10, [r0, #1260]
	str.w r7, [r0, #1440]
	str.w r6, [r0, #2700]
	str.w r8, [r0, #2880]
	ldr.w r2, [r1, #180]
	ldr.w r10, [r1, #540]
	sadd16 r11, r11, r2
	sadd16 r11, r11, r10
	pkhbt r6, r2, r10, lsl #16
	pkhtb r7, r10, r2, asr #16
	sadd16 r8, r6, r4
	ssub16 r2, r6, r4
	sadd16 r10, r7, r5
	ssub16 r4, r7, r5
	str.w r2, [r0, #720]
	str.w r4, [r0, #2160]
	str.w r6, [r0, #1080]
	str.w r7, [r0, #2520]
	ldr.w r5, [r1, #360]
	ldr.w r2, [r1, #1080]
	sadd16 r11, r11, r5
	sadd16 r11, r11, r2
	pkhbt r4, r5, r2, lsl #16
	pkhtb r6, r2, r5, asr #16
	sadd16 r7, r4, r9
	ssub16 r5, r4, r9
	sadd16 r2, r6, r3
	ssub16 r9, r6, r3
	sadd16 r3, r7, r8
	ssub16 r7, r7, r8
	sadd16 r8, r2, r10
	ssub16 r2, r2, r10
	str.w r3, [r0, #180]
	str.w r7, [r0, #360]
	str.w r5, [r0, #540]
	str.w r4, [r0, #900]
	str.w r8, [r0, #1620]
	str.w r2, [r0, #1800]
	str.w r9, [r0, #1980]
	str.w r6, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_0
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_1:
	ldr.w r2, [r1, #1280]
	ldr.w r3, [r1, #1460]
	ldr.w r4, [r1, #560]
	ldr.w r5, [r1, #1100]
	ldr.w r6, [r1, #920]
	ldr.w r7, [r1, #380]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r11, r11, r6
	sadd16 r11, r11, r7
	sadd16 r8, r2, r5
	ssub16 r2, r2, r5
	sadd16 r9, r3, r6
	ssub16 r3, r3, r6
	ssub16 r10, r12, r7
	pkhbt r5, r8, r9, lsl #16
	pkhtb r8, r9, r8, asr #16
	pkhbt r6, r2, r3, lsl #16
	pkhtb r2, r3, r2, asr #16
	pkhbt r9, r7, r4, lsl #16
	pkhtb r7, r4, r7, asr #16
	pkhbt r3, r10, r4, lsl #16
	pkhtb r10, r4, r10, asr #16
	str.w r6, [r0, #1260]
	str.w r3, [r0, #1440]
	str.w r2, [r0, #2700]
	str.w r10, [r0, #2880]
	ldr.w r4, [r1, #200]
	sadd16 r11, r11, r4
	pkhbt r6, r12, r4, lsl #16
	pkhtb r2, r4, r12, asr #16
	sadd16 r3, r6, r9
	ssub16 r10, r6, r9
	sadd16 r4, r2, r7
	ssub16 r9, r2, r7
	str.w r10, [r0, #720]
	str.w r9, [r0, #2160]
	str.w r6, [r0, #1080]
	str.w r2, [r0, #2520]
	ldr.w r7, [r1, #20]
	ldr.w r10, [r1, #740]
	sadd16 r11, r11, r7
	sadd16 r11, r11, r10
	pkhbt r9, r7, r10, lsl #16
	pkhtb r6, r10, r7, asr #16
	sadd16 r2, r9, r5
	ssub16 r7, r9, r5
	sadd16 r10, r6, r8
	ssub16 r5, r6, r8
	sadd16 r8, r2, r3
	ssub16 r2, r2, r3
	sadd16 r3, r10, r4
	ssub16 r10, r10, r4
	str.w r8, [r0, #180]
	str.w r2, [r0, #360]
	str.w r7, [r0, #540]
	str.w r9, [r0, #900]
	str.w r3, [r0, #1620]
	str.w r10, [r0, #1800]
	str.w r5, [r0, #1980]
	str.w r6, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_1
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_2:
	ldr.w r2, [r1, #940]
	ldr.w r3, [r1, #1120]
	ldr.w r4, [r1, #220]
	ldr.w r5, [r1, #760]
	ldr.w r6, [r1, #580]
	ldr.w r7, [r1, #40]
	ldr.w r8, [r1, #1480]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r11, r11, r6
	sadd16 r11, r11, r7
	sadd16 r11, r11, r8
	sadd16 r9, r2, r5
	ssub16 r2, r2, r5
	sadd16 r10, r3, r6
	ssub16 r3, r3, r6
	ssub16 r5, r12, r7
	sadd16 r6, r4, r8
	ssub16 r4, r4, r8
	pkhbt r8, r9, r10, lsl #16
	pkhtb r9, r10, r9, asr #16
	pkhbt r10, r2, r3, lsl #16
	pkhtb r2, r3, r2, asr #16
	pkhbt r3, r7, r6, lsl #16
	pkhtb r7, r6, r7, asr #16
	pkhbt r6, r5, r4, lsl #16
	pkhtb r5, r4, r5, asr #16
	str.w r10, [r0, #1260]
	str.w r6, [r0, #1440]
	str.w r2, [r0, #2700]
	str.w r5, [r0, #2880]
	ssub16 r4, r12, r3
	ssub16 r10, r12, r7
	str.w r4, [r0, #720]
	str.w r10, [r0, #2160]
	str.w r12, [r0, #1080]
	str.w r12, [r0, #2520]
	ldr.w r2, [r1, #400]
	ldr.w r6, [r1, #1300]
	sadd16 r11, r11, r2
	sadd16 r11, r11, r6
	sadd16 r5, r2, r6
	ssub16 r2, r2, r6
	pkhbt r4, r12, r5, lsl #16
	pkhtb r10, r5, r12, asr #16
	pkhbt r6, r12, r2, lsl #16
	pkhtb r5, r2, r12, asr #16
	sadd16 r2, r4, r8
	ssub16 r4, r4, r8
	sadd16 r8, r10, r9
	ssub16 r10, r10, r9
	sadd16 r9, r2, r3
	ssub16 r2, r2, r3
	sadd16 r3, r8, r7
	ssub16 r8, r8, r7
	str.w r9, [r0, #180]
	str.w r2, [r0, #360]
	str.w r4, [r0, #540]
	str.w r6, [r0, #900]
	str.w r3, [r0, #1620]
	str.w r8, [r0, #1800]
	str.w r10, [r0, #1980]
	str.w r5, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_2
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_3:
	ldr.w r2, [r1, #600]
	ldr.w r3, [r1, #780]
	ldr.w r4, [r1, #1320]
	ldr.w r5, [r1, #420]
	ldr.w r6, [r1, #240]
	ldr.w r7, [r1, #1140]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r11, r11, r6
	sadd16 r11, r11, r7
	sadd16 r8, r2, r5
	ssub16 r2, r2, r5
	sadd16 r9, r3, r6
	ssub16 r3, r3, r6
	ssub16 r10, r12, r7
	pkhbt r5, r8, r9, lsl #16
	pkhtb r8, r9, r8, asr #16
	pkhbt r6, r2, r3, lsl #16
	pkhtb r2, r3, r2, asr #16
	pkhbt r9, r4, r7, lsl #16
	pkhtb r3, r7, r4, asr #16
	pkhbt r7, r4, r10, lsl #16
	pkhtb r4, r10, r4, asr #16
	str.w r6, [r0, #1260]
	str.w r7, [r0, #1440]
	str.w r2, [r0, #2700]
	str.w r4, [r0, #2880]
	ldr.w r10, [r1, #1500]
	sadd16 r11, r11, r10
	ssub16 r6, r12, r10
	pkhbt r2, r12, r10, lsl #16
	pkhtb r7, r10, r12, asr #16
	pkhbt r4, r12, r6, lsl #16
	pkhtb r10, r6, r12, asr #16
	sadd16 r6, r2, r9
	ssub16 r2, r2, r9
	sadd16 r9, r7, r3
	ssub16 r7, r7, r3
	str.w r2, [r0, #720]
	str.w r7, [r0, #2160]
	str.w r4, [r0, #1080]
	str.w r10, [r0, #2520]
	ldr.w r3, [r1, #60]
	ldr.w r2, [r1, #960]
	sadd16 r11, r11, r3
	sadd16 r11, r11, r2
	sadd16 r7, r3, r2
	ssub16 r3, r3, r2
	pkhbt r4, r12, r7, lsl #16
	pkhtb r10, r7, r12, asr #16
	pkhbt r2, r12, r3, lsl #16
	pkhtb r7, r3, r12, asr #16
	sadd16 r3, r4, r5
	ssub16 r4, r4, r5
	sadd16 r5, r10, r8
	ssub16 r10, r10, r8
	sadd16 r8, r3, r6
	ssub16 r3, r3, r6
	sadd16 r6, r5, r9
	ssub16 r5, r5, r9
	str.w r8, [r0, #180]
	str.w r3, [r0, #360]
	str.w r4, [r0, #540]
	str.w r2, [r0, #900]
	str.w r6, [r0, #1620]
	str.w r5, [r0, #1800]
	str.w r10, [r0, #1980]
	str.w r7, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_3
	sub.w r1, r1, #20
	add.w lr, r0, #20

    ldr.w r2, [r1, #260]
	ldr.w r3, [r1, #440]
	ldr.w r4, [r1, #980]
	ldr.w r5, [r1, #80]
	ldr.w r6, [r1, #800]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r11, r11, r6
	sadd16 r7, r2, r5
	ssub16 r2, r2, r5
	ssub16 r8, r12, r6
	pkhbt r9, r7, r3, lsl #16
	pkhtb r7, r3, r7, asr #16
	pkhbt r10, r2, r3, lsl #16
	pkhtb r2, r3, r2, asr #16
	pkhbt r5, r4, r6, lsl #16
	pkhtb r3, r6, r4, asr #16
	pkhbt r6, r4, r8, lsl #16
	pkhtb r4, r8, r4, asr #16
	str.w r10, [r0, #1260]
	str.w r6, [r0, #1440]
	str.w r2, [r0, #2700]
	str.w r4, [r0, #2880]
	ldrh.w r8, [r1, #1520]
	ldr.w r10, [r1, #1160]
	sadd16 r11, r11, r8
	sadd16 r11, r11, r10
	ssub16 r2, r12, r8
	ssub16 r6, r12, r10
	pkhbt r4, r8, r10, lsl #16
	pkhtb r8, r10, r8, asr #16
	pkhbt r10, r2, r6, lsl #16
	pkhtb r2, r6, r2, asr #16
	sadd16 r6, r4, r5
	ssub16 r4, r4, r5
	sadd16 r5, r8, r3
	ssub16 r8, r8, r3
	str.w r4, [r0, #720]
	str.w r8, [r0, #2160]
	str.w r10, [r0, #1080]
	str.w r2, [r0, #2520]
	ldr.w r3, [r1, #1340]
	ldr.w r4, [r1, #620]
	sadd16 r11, r11, r3
	sadd16 r11, r11, r4
	ssub16 r8, r12, r3
	ssub16 r10, r12, r4
	pkhbt r2, r3, r4, lsl #16
	pkhtb r3, r4, r3, asr #16
	pkhbt r4, r8, r10, lsl #16
	pkhtb r8, r10, r8, asr #16
	sadd16 r10, r2, r9
	ssub16 r2, r2, r9
	sadd16 r9, r3, r7
	ssub16 r3, r3, r7
	sadd16 r7, r10, r6
	ssub16 r10, r10, r6
	sadd16 r6, r9, r5
	ssub16 r9, r9, r5
	str.w r7, [r0, #180]
	str.w r10, [r0, #360]
	str.w r2, [r0, #540]
	str.w r4, [r0, #900]
	str.w r6, [r0, #1620]
	str.w r9, [r0, #1800]
	str.w r3, [r0, #1980]
	str.w r8, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4

Good_Rader_part1_4:
	ldr.w r2, [r1, #260]
	ldr.w r3, [r1, #440]
	ldr.w r4, [r1, #980]
	ldr.w r5, [r1, #80]
	ldr.w r6, [r1, #800]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r11, r11, r6
	sadd16 r7, r2, r5
	ssub16 r2, r2, r5
	ssub16 r8, r12, r6
	pkhbt r9, r7, r3, lsl #16
	pkhtb r7, r3, r7, asr #16
	pkhbt r10, r2, r3, lsl #16
	pkhtb r2, r3, r2, asr #16
	pkhbt r5, r4, r6, lsl #16
	pkhtb r3, r6, r4, asr #16
	pkhbt r6, r4, r8, lsl #16
	pkhtb r4, r8, r4, asr #16
	str.w r10, [r0, #1260]
	str.w r6, [r0, #1440]
	str.w r2, [r0, #2700]
	str.w r4, [r0, #2880]
	@ ldr.w r8, [r1, #1520]
    mov.w r8, #0
	ldr.w r10, [r1, #1160]
	@ sadd16 r11, r11, r8
	sadd16 r11, r11, r10
	ssub16 r2, r12, r8
	ssub16 r6, r12, r10
	pkhbt r4, r8, r10, lsl #16
	pkhtb r8, r10, r8, asr #16
	pkhbt r10, r2, r6, lsl #16
	pkhtb r2, r6, r2, asr #16
	sadd16 r6, r4, r5
	ssub16 r4, r4, r5
	sadd16 r5, r8, r3
	ssub16 r8, r8, r3
	str.w r4, [r0, #720]
	str.w r8, [r0, #2160]
	str.w r10, [r0, #1080]
	str.w r2, [r0, #2520]
	ldr.w r3, [r1, #1340]
	ldr.w r4, [r1, #620]
	sadd16 r11, r11, r3
	sadd16 r11, r11, r4
	ssub16 r8, r12, r3
	ssub16 r10, r12, r4
	pkhbt r2, r3, r4, lsl #16
	pkhtb r3, r4, r3, asr #16
	pkhbt r4, r8, r10, lsl #16
	pkhtb r8, r10, r8, asr #16
	sadd16 r10, r2, r9
	ssub16 r2, r2, r9
	sadd16 r9, r3, r7
	ssub16 r3, r3, r7
	sadd16 r7, r10, r6
	ssub16 r10, r10, r6
	sadd16 r6, r9, r5
	ssub16 r9, r9, r5
	str.w r7, [r0, #180]
	str.w r10, [r0, #360]
	str.w r2, [r0, #540]
	str.w r4, [r0, #900]
	str.w r6, [r0, #1620]
	str.w r9, [r0, #1800]
	str.w r3, [r0, #1980]
	str.w r8, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_4
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_5:
	ldr.w r2, [r1, #100]
	ldr.w r3, [r1, #640]
	ldr.w r4, [r1, #460]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	sadd16 r11, r11, r4
	ssub16 r5, r12, r4
	pkhbt r6, r12, r2, lsl #16
	pkhtb r7, r2, r12, asr #16
	pkhbt r8, r3, r4, lsl #16
	pkhtb r9, r4, r3, asr #16
	pkhbt r10, r3, r5, lsl #16
	pkhtb r3, r5, r3, asr #16
	str.w r6, [r0, #1260]
	str.w r10, [r0, #1440]
	str.w r7, [r0, #2700]
	str.w r3, [r0, #2880]
	ldr.w r2, [r1, #1180]
	ldr.w r4, [r1, #820]
	sadd16 r11, r11, r2
	sadd16 r11, r11, r4
	ssub16 r5, r12, r2
	ssub16 r10, r12, r4
	pkhbt r3, r2, r4, lsl #16
	pkhtb r2, r4, r2, asr #16
	pkhbt r4, r5, r10, lsl #16
	pkhtb r5, r10, r5, asr #16
	sadd16 r10, r3, r8
	ssub16 r3, r3, r8
	sadd16 r8, r2, r9
	ssub16 r2, r2, r9
	str.w r3, [r0, #720]
	str.w r2, [r0, #2160]
	str.w r4, [r0, #1080]
	str.w r5, [r0, #2520]
	ldr.w r9, [r1, #1000]
	ldr.w r3, [r1, #280]
	sadd16 r11, r11, r9
	sadd16 r11, r11, r3
	ssub16 r2, r12, r9
	ssub16 r4, r12, r3
	pkhbt r5, r9, r3, lsl #16
	pkhtb r9, r3, r9, asr #16
	pkhbt r3, r2, r4, lsl #16
	pkhtb r2, r4, r2, asr #16
	sadd16 r4, r5, r6
	ssub16 r5, r5, r6
	sadd16 r6, r9, r7
	ssub16 r9, r9, r7
	sadd16 r7, r4, r10
	ssub16 r4, r4, r10
	sadd16 r10, r6, r8
	ssub16 r6, r6, r8
	str.w r7, [r0, #180]
	str.w r4, [r0, #360]
	str.w r5, [r0, #540]
	str.w r3, [r0, #900]
	str.w r10, [r0, #1620]
	str.w r6, [r0, #1800]
	str.w r9, [r0, #1980]
	str.w r2, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_5
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_6:
	ldr.w r2, [r1, #300]
	ldr.w r3, [r1, #120]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	ssub16 r4, r12, r3
	pkhbt r5, r2, r3, lsl #16
	pkhtb r6, r3, r2, asr #16
	pkhbt r7, r2, r4, lsl #16
	pkhtb r2, r4, r2, asr #16
	str.w r12, [r0, #1260]
	str.w r7, [r0, #1440]
	str.w r12, [r0, #2700]
	str.w r2, [r0, #2880]
	ldr.w r8, [r1, #1200]
	ldr.w r9, [r1, #840]
	ldr.w r10, [r1, #480]
	sadd16 r11, r11, r8
	sadd16 r11, r11, r9
	sadd16 r11, r11, r10
	sadd16 r3, r8, r9
	ssub16 r8, r8, r9
	ssub16 r4, r12, r10
	pkhbt r7, r3, r10, lsl #16
	pkhtb r3, r10, r3, asr #16
	pkhbt r2, r8, r4, lsl #16
	pkhtb r8, r4, r8, asr #16
	sadd16 r9, r7, r5
	ssub16 r7, r7, r5
	sadd16 r10, r3, r6
	ssub16 r3, r3, r6
	str.w r7, [r0, #720]
	str.w r3, [r0, #2160]
	str.w r2, [r0, #1080]
	str.w r8, [r0, #2520]
	ldr.w r4, [r1, #1380]
	ldr.w r5, [r1, #660]
	sadd16 r11, r11, r4
	sadd16 r11, r11, r5
	sadd16 r6, r4, r5
	ssub16 r4, r4, r5
	pkhbt r7, r6, r12, lsl #16
	pkhtb r6, r12, r6, asr #16
	pkhbt r3, r4, r12, lsl #16
	pkhtb r4, r12, r4, asr #16
	sadd16 r2, r7, r9
	ssub16 r8, r7, r9
	sadd16 r5, r6, r10
	ssub16 r9, r6, r10
	str.w r2, [r0, #180]
	str.w r8, [r0, #360]
	str.w r7, [r0, #540]
	str.w r3, [r0, #900]
	str.w r5, [r0, #1620]
	str.w r9, [r0, #1800]
	str.w r6, [r0, #1980]
	str.w r4, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_6
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_7:
	ldr.w r2, [r1, #1400]
@ handle it
	mov.w r11, r2
	ssub16 r3, r12, r2
	pkhbt r4, r2, r12, lsl #16
	pkhtb r2, r12, r2, asr #16
	pkhbt r5, r3, r12, lsl #16
	pkhtb r3, r12, r3, asr #16
	str.w r12, [r0, #1260]
	str.w r5, [r0, #1440]
	str.w r12, [r0, #2700]
	str.w r3, [r0, #2880]
	ldr.w r6, [r1, #860]
	ldr.w r7, [r1, #1220]
	ldr.w r8, [r1, #500]
	ldr.w r9, [r1, #140]
	sadd16 r11, r11, r6
	sadd16 r11, r11, r7
	sadd16 r11, r11, r8
	sadd16 r11, r11, r9
	sadd16 r10, r6, r8
	ssub16 r6, r6, r8
	sadd16 r5, r7, r9
	ssub16 r7, r7, r9
	pkhbt r3, r10, r5, lsl #16
	pkhtb r10, r5, r10, asr #16
	pkhbt r8, r6, r7, lsl #16
	pkhtb r6, r7, r6, asr #16
	sadd16 r9, r3, r4
	ssub16 r3, r3, r4
	sadd16 r5, r10, r2
	ssub16 r10, r10, r2
	str.w r3, [r0, #720]
	str.w r10, [r0, #2160]
	str.w r8, [r0, #1080]
	str.w r6, [r0, #2520]
	ldr.w r7, [r1, #1040]
	ldr.w r4, [r1, #320]
	sadd16 r11, r11, r7
	sadd16 r11, r11, r4
	sadd16 r2, r7, r4
	ssub16 r7, r7, r4
	pkhbt r3, r2, r12, lsl #16
	pkhtb r2, r12, r2, asr #16
	pkhbt r10, r7, r12, lsl #16
	pkhtb r7, r12, r7, asr #16
	sadd16 r8, r3, r9
	ssub16 r6, r3, r9
	sadd16 r4, r2, r5
	ssub16 r9, r2, r5
	str.w r8, [r0, #180]
	str.w r6, [r0, #360]
	str.w r3, [r0, #540]
	str.w r10, [r0, #900]
	str.w r4, [r0, #1620]
	str.w r9, [r0, #1800]
	str.w r2, [r0, #1980]
	str.w r7, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_7
	sub.w r1, r1, #20
	add.w lr, r0, #20
Good_Rader_part1_8:
	ldr.w r2, [r1, #1240]
	ldr.w r3, [r1, #1060]
	@ sadd16 r11, r11, r2
	sadd16 r11, r2, r3
	ssub16 r4, r12, r3
	pkhbt r5, r3, r2, lsl #16
	pkhtb r3, r2, r3, asr #16
	pkhbt r6, r4, r2, lsl #16
	pkhtb r4, r2, r4, asr #16
	str.w r12, [r0, #1260]
	str.w r6, [r0, #1440]
	str.w r12, [r0, #2700]
	str.w r4, [r0, #2880]
	ldr.w r7, [r1, #520]
	ldr.w r8, [r1, #880]
	ldr.w r9, [r1, #160]
	sadd16 r11, r11, r7
	sadd16 r11, r11, r8
	sadd16 r11, r11, r9
	sadd16 r10, r7, r9
	ssub16 r7, r7, r9
	pkhbt r2, r10, r8, lsl #16
	pkhtb r10, r8, r10, asr #16
	pkhbt r6, r7, r8, lsl #16
	pkhtb r7, r8, r7, asr #16
	sadd16 r4, r2, r5
	ssub16 r2, r2, r5
	sadd16 r9, r10, r3
	ssub16 r10, r10, r3
	str.w r2, [r0, #720]
	str.w r10, [r0, #2160]
	str.w r6, [r0, #1080]
	str.w r7, [r0, #2520]
	ldr.w r8, [r1, #700]
	ldr.w r5, [r1, #1420]
	sadd16 r11, r11, r8
	sadd16 r11, r11, r5
	pkhbt r3, r8, r5, lsl #16
	pkhtb r2, r5, r8, asr #16
	sadd16 r10, r3, r4
	ssub16 r6, r3, r4
	sadd16 r7, r2, r9
	ssub16 r8, r2, r9
	str.w r10, [r0, #180]
	str.w r6, [r0, #360]
	str.w r3, [r0, #540]
	str.w r3, [r0, #900]
	str.w r7, [r0, #1620]
	str.w r8, [r0, #1800]
	str.w r2, [r0, #1980]
	str.w r2, [r0, #2340]
	str.w r11, [r0], #4
	add.w r1, r1, #4
	cmp.w r0, lr
	bne.w Good_Rader_part1_8

    vmov r0, s0
    vmov r12, s3
    add.w lr, r0, #180
    vmov r1, s4
    vmov r2, s5
    vmov r3, s6
    vmov r4, s7
Good_Rader_part2:
	ldr.w r5, [r0, #180]
	ldr.w r6, [r0, #360]
	ldr.w r7, [r0, #540]
	ldr.w r8, [r0, #720]
	smuad r9, r1, r5
	smuadx r10, r1, r5
	smulbt r5, r9, r12
	smlabb r9, r5, r12, r9
	smulbt r5, r10, r12
	smlabb r10, r5, r12, r10
	pkhtb r5, r10, r9, asr #16
	smusd r9, r2, r6
	smuadx r10, r2, r6
	smulbt r6, r9, r12
	smlabb r9, r6, r12, r9
	smulbt r6, r10, r12
	smlabb r10, r6, r12, r10
	pkhtb r6, r10, r9, asr #16
	sadd16 r9, r5, r6
	ssub16 r10, r5, r6
	smuadx r11, r3, r7
	smuadx r5, r4, r8
	sub.w r11, r11, r5
	smuadx r5, r3, r8
	smladx r5, r4, r7, r5
	smulbt r6, r11, r12
	smlabb r11, r6, r12, r11
	smulbt r6, r5, r12
	smlabb r5, r6, r12, r5
	pkhtb r6, r5, r11, asr #16
	pkhbt r11, r7, r8
	pkhtb r5, r7, r8
	smusd r7, r3, r11
	smuad r8, r4, r5
	sub.w r7, r7, r8
	smuad r8, r3, r5
	smlsd r8, r4, r11, r8
	smulbt r11, r7, r12
	smlabb r7, r11, r12, r7
	smulbt r11, r8, r12
	smlabb r8, r11, r12, r8
	pkhtb r7, r8, r7, asr #16
	pkhbt r8, r7, r6, lsl #16
	pkhtb r7, r6, r7, asr #16
	sadd16 r11, r9, r8
	ssub16 r5, r9, r8
	sadd16 r6, r10, r7
	ssub16 r9, r10, r7
	str.w r11, [r0, #180]
	str.w r6, [r0, #360]
	str.w r5, [r0, #540]
	str.w r9, [r0, #720]
	ldr.w r5, [r0, #1620]
	ldr.w r6, [r0, #1800]
	ldr.w r7, [r0, #1980]
	ldr.w r8, [r0, #2160]
	smuad r9, r1, r5
	smuadx r10, r1, r5
	smulbt r5, r9, r12
	smlabb r9, r5, r12, r9
	smulbt r5, r10, r12
	smlabb r10, r5, r12, r10
	pkhtb r5, r10, r9, asr #16
	smusd r9, r2, r6
	smuadx r10, r2, r6
	smulbt r6, r9, r12
	smlabb r9, r6, r12, r9
	smulbt r6, r10, r12
	smlabb r10, r6, r12, r10
	pkhtb r6, r10, r9, asr #16
	sadd16 r9, r5, r6
	ssub16 r10, r5, r6
	smuadx r11, r3, r7
	smuadx r5, r4, r8
	sub.w r11, r11, r5
	smuadx r5, r3, r8
	smladx r5, r4, r7, r5
	smulbt r6, r11, r12
	smlabb r11, r6, r12, r11
	smulbt r6, r5, r12
	smlabb r5, r6, r12, r5
	pkhtb r6, r5, r11, asr #16
	pkhbt r11, r7, r8
	pkhtb r5, r7, r8
	smusd r7, r3, r11
	smuad r8, r4, r5
	sub.w r7, r7, r8
	smuad r8, r3, r5
	smlsd r8, r4, r11, r8
	smulbt r11, r7, r12
	smlabb r7, r11, r12, r7
	smulbt r11, r8, r12
	smlabb r8, r11, r12, r8
	pkhtb r7, r8, r7, asr #16
	pkhbt r8, r7, r6, lsl #16
	pkhtb r7, r6, r7, asr #16
	sadd16 r11, r9, r8
	ssub16 r5, r9, r8
	sadd16 r6, r10, r7
	ssub16 r9, r10, r7
	str.w r11, [r0, #1620]
	str.w r6, [r0, #1800]
	str.w r5, [r0, #1980]
	str.w r9, [r0, #2160]
    add.w r0, r0, #4
    cmp.w r0, lr
    bne.w Good_Rader_part2

    vmov r0, s0
    vmov r1, s8
    vmov r2, s9
    vmov r3, s10
    vmov r4, s11
Good_Rader_part3:
    ldr.w r5, [r0, #900]
	ldr.w r6, [r0, #1080]
	ldr.w r7, [r0, #1260]
	ldr.w r8, [r0, #1440]
	smuadx r9, r1, r5
	smuadx r10, r2, r8
	smladx r10, r3, r7, r10
	smladx r10, r4, r6, r10
	sub.w r9, r9, r10
	smuadx r10, r1, r6
	smladx r10, r2, r5, r10
	smuadx r11, r3, r8
	smladx r11, r4, r7, r11
	sub.w r10, r10, r11
	smulbt r11, r9, r12
	smlabb r9, r11, r12, r9
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r9, r10, r9, asr #16
	vmov s12, r9
	smuadx r9, r1, r7
	smladx r9, r2, r6, r9
	smladx r9, r3, r5, r9
	smuadx r10, r4, r8
	sub.w r9, r9, r10
	smuadx r10, r1, r8
	smladx r10, r2, r7, r10
	smladx r10, r3, r6, r10
	smladx r10, r4, r5, r10
	smulbt r11, r9, r12
	smlabb r9, r11, r12, r9
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r9, r10, r9, asr #16
	vmov s13, r9
	pkhbt r9, r5, r8
	pkhtb r5, r5, r6
	pkhtb r6, r6, r7
	pkhtb r7, r7, r8
	smusd r8, r1, r9
	smuad r10, r2, r7
	smlad r10, r3, r6, r10
	smlad r10, r4, r5, r10
	sub.w r8, r8, r10
	smuad r10, r1, r5
	smlsd r10, r2, r9, r10
	smuad r11, r3, r7
	smlad r11, r4, r6, r11
	sub.w r10, r10, r11
	smulbt r11, r8, r12
	smlabb r8, r11, r12, r8
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r11, r10, r8, asr #16
	smuad r8, r1, r6
	smlad r8, r2, r5, r8
	smlsd r8, r3, r9, r8
	smuad r10, r4, r7
	sub.w r8, r8, r10
	smuad r10, r1, r7
	smlad r10, r2, r6, r10
	smlad r10, r3, r5, r10
	smlsd r10, r4, r9, r10
	smulbt r9, r8, r12
	smlabb r8, r9, r12, r8
	smulbt r9, r10, r12
	smlabb r10, r9, r12, r10
	pkhtb r8, r10, r8, asr #16
	vmov r10, s12
	vmov r9, s13
	pkhbt r5, r11, r10, lsl #16
	pkhtb r10, r10, r11, asr #16
	pkhbt r11, r8, r9, lsl #16
	pkhtb r8, r9, r8, asr #16
	str.w r5, [r0, #900]
	str.w r10, [r0, #1080]
	str.w r11, [r0, #1260]
	str.w r8, [r0, #1440]
	ldr.w r5, [r0, #2340]
	ldr.w r6, [r0, #2520]
	ldr.w r7, [r0, #2700]
	ldr.w r8, [r0, #2880]
	smuadx r9, r1, r5
	smuadx r10, r2, r8
	smladx r10, r3, r7, r10
	smladx r10, r4, r6, r10
	sub.w r9, r9, r10
	smuadx r10, r1, r6
	smladx r10, r2, r5, r10
	smuadx r11, r3, r8
	smladx r11, r4, r7, r11
	sub.w r10, r10, r11
	smulbt r11, r9, r12
	smlabb r9, r11, r12, r9
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r9, r10, r9, asr #16
	vmov s12, r9
	smuadx r9, r1, r7
	smladx r9, r2, r6, r9
	smladx r9, r3, r5, r9
	smuadx r10, r4, r8
	sub.w r9, r9, r10
	smuadx r10, r1, r8
	smladx r10, r2, r7, r10
	smladx r10, r3, r6, r10
	smladx r10, r4, r5, r10
	smulbt r11, r9, r12
	smlabb r9, r11, r12, r9
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r9, r10, r9, asr #16
	vmov s13, r9
	pkhbt r9, r5, r8
	pkhtb r5, r5, r6
	pkhtb r6, r6, r7
	pkhtb r7, r7, r8
	smusd r8, r1, r9
	smuad r10, r2, r7
	smlad r10, r3, r6, r10
	smlad r10, r4, r5, r10
	sub.w r8, r8, r10
	smuad r10, r1, r5
	smlsd r10, r2, r9, r10
	smuad r11, r3, r7
	smlad r11, r4, r6, r11
	sub.w r10, r10, r11
	smulbt r11, r8, r12
	smlabb r8, r11, r12, r8
	smulbt r11, r10, r12
	smlabb r10, r11, r12, r10
	pkhtb r11, r10, r8, asr #16
	smuad r8, r1, r6
	smlad r8, r2, r5, r8
	smlsd r8, r3, r9, r8
	smuad r10, r4, r7
	sub.w r8, r8, r10
	smuad r10, r1, r7
	smlad r10, r2, r6, r10
	smlad r10, r3, r5, r10
	smlsd r10, r4, r9, r10
	smulbt r9, r8, r12
	smlabb r8, r9, r12, r8
	smulbt r9, r10, r12
	smlabb r10, r9, r12, r10
	pkhtb r8, r10, r8, asr #16
	vmov r10, s12
	vmov r9, s13
	pkhbt r5, r11, r10, lsl #16
	pkhtb r10, r10, r11, asr #16
	pkhbt r11, r8, r9, lsl #16
	pkhtb r8, r9, r8, asr #16
	str.w r5, [r0, #2340]
	str.w r10, [r0, #2520]
	str.w r11, [r0, #2700]
	str.w r8, [r0, #2880]
    add.w r0, r0, #4
    cmp.w r0, lr
    bne.w Good_Rader_part3

    vmov r0, s0
    vmov r1, s1
    add.w lr, r0, #20
Good_Rader_part4_0:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r7, r7, r12
	sadd16 r8, r8, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r6, r6, r12
	sadd16 r7, r7, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12
	sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    str.w r11, [r0], #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_0

    @ vmov r0, s0
    @ vmov r1, s1
    add.w lr, r0, #80
Good_Rader_part4_1to4:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    @ ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	@ sadd16 r2, r2, r12
	@ sadd16 r3, r3, r12
	@ sadd16 r4, r4, r12
	@ sadd16 r5, r5, r12
	@ sadd16 r7, r7, r12
	@ sadd16 r8, r8, r12
	@ sadd16 r9, r9, r12
	@ sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	@ ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	@ sadd16 r2, r2, r12
	@ sadd16 r3, r3, r12
	@ sadd16 r4, r4, r12
	@ sadd16 r5, r5, r12
	@ sadd16 r6, r6, r12
	@ sadd16 r7, r7, r12
	@ sadd16 r9, r9, r12
	@ sadd16 r10, r10, r12
	@ sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    @ str.w r11, [r0], #4
	add.w r0, r0, #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_1to4

    @ vmov r0, s0
    vmov r1, s1
    add.w r1, r1, #1360
    add.w lr, r0, #20
Good_Rader_part4_5:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r7, r7, r12
	sadd16 r8, r8, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r6, r6, r12
	sadd16 r7, r7, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12
	sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    str.w r11, [r0], #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_5

    @ vmov r0, s0
    vmov r1, s1
    add.w r1, r1, #1020
    add.w lr, r0, #20
Good_Rader_part4_6:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r7, r7, r12
	sadd16 r8, r8, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r6, r6, r12
	sadd16 r7, r7, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12
	sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    str.w r11, [r0], #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_6

    @ vmov r0, s0
    vmov r1, s1
    add.w r1, r1, #680
    add.w lr, r0, #20
Good_Rader_part4_7:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r7, r7, r12
	sadd16 r8, r8, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r6, r6, r12
	sadd16 r7, r7, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12
	sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    str.w r11, [r0], #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_7

    vmov r1, s1
    add.w r1, r1, #340
    add.w lr, r0, #20
Good_Rader_part4_8:
    ldr.w r3, [r0, #180] 
    ldr.w r4, [r0, #900]
    ldr.w r5, [r0, #360]
    ldr.w r6, [r0, #1080]

    ldr.w r7, [r0, #1620]
    ldr.w r8, [r0, #2340]
    ldr.w r9, [r0, #1800]
    ldr.w r10, [r0, #2520]

    ldr.w r12, [r1], #4
	
	sadd16 r2, r3, r4 @ 0, 1
	ssub16 r3, r3, r4 @ 8, 9
	sadd16 r4, r5, r6 @ 2, 3
	ssub16 r5, r5, r6 @ 10, 11

	sadd16 r6, r7, r8 @ 0, 1
	ssub16 r7, r7, r8 @ 8, 9
	sadd16 r8, r9, r10 @ 2, 3
	ssub16 r9, r9, r10 @ 10, 11

	pkhtb r10, r9, r5, asr #16 @ 11, str #720
	pkhbt r5, r5, r9, lsl #16 @ 10, str #2160
	pkhtb r9, r8, r4, asr #16 @ 3, str #2340
	pkhbt r4, r4, r8, lsl #16 @ 2, str #900
	pkhtb r8, r7, r3, asr #16 @ 9, str #360
	pkhbt r3, r3, r7, lsl #16 @ 8, str #1080
	pkhtb r7, r6, r2, asr #16 @ 1, str #2700
	pkhbt r2, r2, r6, lsl #16 @ 0, str #1980

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r7, r7, r12
	sadd16 r8, r8, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12

	str.w r9, [r0, #2340]
	str.w r4, [r0, #900]
	str.w r8, [r0, #360]
	str.w r3, [r0, #1080]

    ldr.w r3, [r0, #720]
    ldr.w r4, [r0, #1980]
    ldr.w r8, [r0, #2160]
    ldr.w r9, [r0, #2700]

	str.w r10, [r0, #720]
	str.w r5, [r0, #2160]
	str.w r7, [r0, #2700]
	str.w r2, [r0, #1980]

	ldr.w r2, [r0, #540] 
    ldr.w r5, [r0, #1260]
    ldr.w r7, [r0, #1440]
    ldr.w r10, [r0, #2880]

	ldr.w r11, [r0]

	sadd16 r6, r2, r5 @ 4, 5
	ssub16 r2, r2, r5 @ 12, 13
	sadd16 r5, r3, r7 @ 6, 7
	ssub16 r3, r3, r7 @ 14, 15

	sadd16 r7, r4, r9 @ 4, 5
	ssub16 r4, r4, r9 @ 12, 13
	sadd16 r9, r8, r10 @ 6, 7
	ssub16 r8, r8, r10 @ 14, 15
	
	pkhbt r10, r6, r7, lsl #16 @ 4, str #1800
	pkhtb r6, r7, r6, asr #16 @ 5, str #1620
	pkhbt r7, r5, r9, lsl #16 @ 6, str #540
	pkhtb r5, r9, r5, asr #16 @ 7, str #180
	pkhbt r9, r2, r4, lsl #16 @ 12, str #1260
	pkhtb r2, r4, r2, asr #16 @ 13, str #1440
	pkhbt r4, r3, r8, lsl #16 @ 14, str #2520
	pkhtb r3, r8, r3, asr #16 @ 15, str #2880

	sadd16 r2, r2, r12
	sadd16 r3, r3, r12
	sadd16 r4, r4, r12
	sadd16 r5, r5, r12
	sadd16 r6, r6, r12
	sadd16 r7, r7, r12
	sadd16 r9, r9, r12
	sadd16 r10, r10, r12
	sadd16 r11, r11, r12

    str.w r10, [r0, #1800]
    str.w r6, [r0, #1620]
    str.w r7, [r0, #540]
    str.w r5, [r0, #180]
    str.w r9, [r0, #1260]
    str.w r2, [r0, #1440]
    str.w r4, [r0, #2520]
    str.w r3, [r0, #2880]

    str.w r11, [r0], #4
    cmp.w r0, lr
    bne.w Good_Rader_part4_8
    pop {r2-r12, pc}


