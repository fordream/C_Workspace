#include <stdio.h>
#include <conio.h>
typedef unsigned char	byte;
typedef unsigned int	word;
typedef unsigned long	dwrd;

#define	MAXMEM	4096
#define	VMaddr	1024
#define	WIDTH	40
#define	HEIGHT	20

dwrd	PC;
dwrd	Rgf[32];
char	str[80];	//Debug
word	Memory[MAXMEM]={	//虚拟机显示只在MIPS
0x2010, 0x0400,	//li	$s0,VMaddr
0x2011, 0x0012,	//la	$s1,hi
0x8628, 0x0000,	//lh	$t0,0($s1)
0x1100, 0x0004,	//beqz	$t0,RR
0xA608, 0x005A,	//sh	$t0,90($s0)
0x2210, 0x0001,	//addi	$s0,$s0,1
0x2231, 0x0001,	//addi	$s1,$s1,1
0x0800, 0x0002,	//j	R0
0x0800, 0x0010,	//RR:j	R2
0x0048, 0x0065,	//hi	.2byte	"Hello World.",0
0x006C, 0x006C,
0x006F, 0x0020,
0x0057, 0x006F,
0x0072, 0x006C,
0x0064, 0x002E,
0x0000, 0x1234,
0x2010, 0x0400,	//R2: li	$s0, VMaddr
0x2008, 0x0048,	//: li	$t0, 'h'
0xA608, 0x01A4,	//: SH $t0, 420($s0)
0x2008, 0x0069,	//: li	$t0, 'i'
0xA608, 0x01A5,	//: SH $t0, 421($s0)
0};
void cpu_init()
{
int	i;
Rgf[0]	=0;	//$zero
PC	=0;
for(i=0; i<WIDTH*HEIGHT; i++)Memory[VMaddr+i]='.';
}
int exe_instru(dwrd IR)
{
int	op, rs, rt, rd, dat, sft, fun;
dwrd	adr;
op =(IR>>26)&63;	//IR{31..26}
rs =(IR>>21)&31;	//IR{25..21}
rt =(IR>>16)&31;	//IR{20..16}
rd =(IR>>11)&31;	//IR{15..11}
sft=(IR>>6)&31;	//IR{11..6}
fun=IR&63;	//IR{5..0}
dat=(int)(short)(IR&0xFFFF);	//IR{15..0}
adr=(IR&0x3FFFFFF)<<1;	//IR{25..0}<<2

printf("--> %lu, %lX, %lX\n", PC, IR, adr);
switch(op){
case 0:	//R-type
switch(fun){
case 32:	//ADD
Rgf[rd] = Rgf[rs]+Rgf[rt];
sprintf(str,"ADD\t$%u, $%u, $%u", rd, rs, rt);	//虚拟机可不用
break;
case 34:	//SUB
Rgf[rd] = Rgf[rs]-Rgf[rt];
sprintf(str,"SUB\t$%u, $%u, $%u", rd, rs, rt);
break;
}
break;
case 8:	//ADDi
Rgf[rt] =Rgf[rs]+(long)dat;
sprintf(str,"ADDi\t$%u, $%u, %u", rt, rs, dat);
break;
case 33:	//LH
Rgf[rt] =(long)Memory[Rgf[rs]+dat];
sprintf(str,"LH\t$%u, $%u(%u)", rt, dat, rs);
break;
case 35:	//LW
Rgf[rt] =((dwrd)Memory[Rgf[rs]+dat]<<16) | (dwrd)Memory[Rgf[rs]+dat+1];
sprintf(str,"LW\t$%u, $%u(%u)", rt, dat, rs);
break;
case 41:	//SH
Memory[Rgf[rs]+dat] =(word)(Rgf[rt]&0xFFFF);
sprintf(str,"SH\t$%u, %d($%u)", rt, dat, rs);
break;
case 43:	//SW
Memory[Rgf[rs]+dat] =(word)(Rgf[rt]>>16);
Memory[Rgf[rs]+dat+1]=(word)(Rgf[rt]&0xFFFF);
sprintf(str,"SW\t$%u, %d($%u)", rt, dat, rs);
break;
case 4:	//BEQ
if(Rgf[rs] == Rgf[rt])PC+=(dat<<1);
sprintf(str,"BEQ\t$%u, $%u, %u", rt, rs, dat);
break;
case 2:	//J
PC=PC&0xF0000000 | adr;
sprintf(str,"J\t%lu", PC);
break;
default:
printf("Instruction Error! %lx", IR);
return -1;	//break;
}
return 0;
}
int main(int argc, char *argv[])
{
char	ch;
int	row, col;
dwrd	IR;

clrscr();
cpu_init();
for(;;){
IR = ((dwrd)Memory[PC]<<16)|(dwrd)Memory[PC+1];	PC+=2;
exe_instru(IR);

if((ch=getch())==27)break;
clrscr();
for(row=0; row<HEIGHT; row++){
for(col=0; col<WIDTH; col++){
printf("%c",Memory[VMaddr+row*WIDTH+col]&255);
}	printf("\n");
}
printf("\n%s\n%lu, %lX", str, PC, IR);	//模拟器
if(ch==' ')PC=0;
}
printf("Hello, world\n");
}