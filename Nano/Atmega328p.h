#ifndef ATMEGA328P_H
#define ATMEGA328P_H
#include <inttypes.h>
namespace Atmega328p {
    enum Registers:uint16_t{
        R_UDR0 = 0xC6,

        R_UBRR0H=0xC5,
        R_UBRR0L=0xC4,

        R_UCSR0C=0xC2,
        R_UCSR0B=0xC1,
        R_UCSR0A=0xC0,

        R_TWAMR=0xBD,
        R_TWCR=0xBC,
        R_TWDR=0xBB,
        R_TWAR=0xBA,
        R_TWSR=0xB9,
        R_TWBR=0xB8,

        R_ASSR=0xB6,
        R_OCR2RB=0xB4,
        R_OCR2RA=0xB3,
        R_TCNT2=0xB2,
        R_TCCR2B=0xB1,
        R_TCCR2A=0xB0,

        R_OCR1BH=0x8B,
        R_OCR1BL=0x8A,
        R_OCR1AH=0x89,
        R_OCR1AL=0x88,

        R_ICR1H=0x87,
        R_ICR1L=0x86,

        R_TCNT1H=0x85,
        R_TCNT1L=0x84,

        R_TCCR1C=0x82,
        R_TCCR1B=0x81,
        R_TCCR1A=0x80,

        R_DIDR1=0x7F,
        R_DIDR0=0x7E,

        R_ADCSRB=0x7B,
        R_ADCSRA=0x7A,
        R_ADCH=0x79,
        R_ADCL=0x78,

        //TIMSK
        R_TIMSK2=0x70,
        R_TIMSK1=0x6F,
        R_TIMSK0=0x6E,

        R_PCMSK2=0x6D,
        R_PCMSK1=0x6C,
        R_PCMSK0=0x6B,

        R_EICRA=0x69,
        R_PCICR=0x68,

        R_OSCCAL=0x66,

        R_PRR=0x64,

        R_CLKPR=0x61,
        R_WDTCSR=0x60,

        R_SREG=0x5F,
        R_SPH=0x5E,
        R_SPL=0x5D,

        R_SPMCSR=0x57,

        R_MCUCR=0x55,
        R_MCUSR=0x54,
        R_SMCR=0x53,

        R_ACSR=0x50,

        R_SPDR=0x4E,
        R_SPSR=0x4D,
        R_SPCR=0x4C,
        R_GPIOR2=0x4B,
        R_GPIOR1=0x4A,

        R_OCR0B=0x48,
        R_OCR0A=0x47,

        R_TCNT0=0x46,
        //Timer Counter Controll Register #B
        R_TCCR0B=0x45,
        //Timer Counter Controll Register #A
        R_TCCR0A=0x44,
        R_GTCCR=0x43,
        R_EEARH=0x42,
        R_EEARL=0x41,
        R_EEDR=0x40,
        R_EECR=0x3F,

        R_GPIOR0=0x3E,

        R_EIMSK=0x3D,
        R_EIFR=0x3C,
        R_PCIFR=0x3B,

        //TIFR
        R_TIFR2=0x37,
        R_TIFR1=0x36,
        R_TIFR0=0x35,

        R_PORTD=0x2B,
        R_DDRD=0x2A,
        R_PIND=0x29,

        R_PORTC=0x28,
        R_DDRC=0x27,
        R_PINC=0x26,

        R_PORTB=0x25,
        R_DDRB=0x24,
        R_PINB=0x23
    };
    namespace Bits {
        enum{
            CS00 = 0,
            CS01 = 1,
            CS02 = 2
        };
    }
}
#endif // ATMEGA328P_H
