#ifndef __SYSTEM_H
#define __SYSTEM_H

#define size_t int

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
	

/* MAIN.C */
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void putnum(unsigned int num);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, 
	unsigned char access, unsigned char gran);
extern void gdt_install();

extern void idt_set_gate(unsigned char num, unsigned long base, 
	unsigned short sel, unsigned char flags);
extern void idt_install();

extern void isrs_install();

extern void irq_install();
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));

extern void timer_install();

extern void keyboard_install();

#endif
