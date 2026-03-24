#ifndef ATMEGA328P_H
#define ATMEGA328P_H
#include <inttypes.h>
namespace Atmega328p {
    enum Registers:uint8_t{
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
        R_TCCR0B=0x45,
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
        enum : uint8_t{
            //PINB
            PINB0 = 0,
            PINB1 ,
            PINB2 ,
            PINB3 ,
            PINB4 ,
            PINB5 ,
            PINB6 ,
            PINB7 ,

            //DDRB
            DDB0 = 0,
            DDB1 ,
            DDB2 ,
            DDB3 ,
            DDB4 ,
            DDB5 ,
            DDB6 ,
            DDB7 ,

            //PORTB
            PORTB0 = 0,
            PORTB1 ,
            PORTB2 ,
            PORTB3 ,
            PORTB4 ,
            PORTB5 ,
            PORTB6 ,
            PORTB7 ,

            //PINC
            PINC0 = 0,
            PINC1 ,
            PINC2 ,
            PINC3 ,
            PINC4 ,
            PINC5 ,
            PINC6 ,
            PINC7 ,

            //DDRC
            DDC0 = 0,
            DDC1 ,
            DDC2 ,
            DDC3 ,
            DDC4 ,
            DDC5 ,
            DDC6 ,
            DDC7 ,

            //PORTC
            PORTC0 = 0,
            PORTC1 ,
            PORTC2 ,
            PORTC3 ,
            PORTC4 ,
            PORTC5 ,
            PORTC6 ,
            PORTC7 ,

            //PIND
            PIND0 = 0,
            PIND1 ,
            PIND2 ,
            PIND3 ,
            PIND4 ,
            PIND5 ,
            PIND6 ,
            PIND7 ,

            //DDRD
            DDD0 = 0,
            DDD1 ,
            DDD2 ,
            DDD3 ,
            DDD4 ,
            DDD5 ,
            DDD6 ,
            DDD7 ,

            //PORTD
            PORTD0 = 0,
            PORTD1 ,
            PORTD2 ,
            PORTD3 ,
            PORTD4 ,
            PORTD5 ,
            PORTD6 ,
            PORTD7 ,

            //TIFR0
            TOV0 = 0,
            OCF0A,
            OCF0B,

            //TIFR1
            TOV1 = 0,
            OCF1A,
            OCF1B,
            ICF1 = 5,

            //TIFR2
            TOV2 = 0,
            OCF2A,
            OCF2B,

            //PCIFR
            PCIF0 = 0,
            PCIF1 ,
            PCIF2 ,

            //EIFR
            INTF0 = 0,
            INTF1 ,

            //EIMSK
            INT0 = 0,
            INT1 ,

            //EECR
            EERE = 0,
            EEPE,
            EEMPE,
            EERIE,
            EEPM0,
            EEPM1,

            //GTCCR
            PSRSYNC = 0,
            PSRASY,
            TSM = 7,

            //TCCR0A
            WGM00 = 0,
            WGM01,
            COM0B0 = 4,
            COM0B1,
            COM0A0,
            COM0A1,

            //TCCR0B
            CS00 = 0,
            CS01,
            CS02,
            WGM02,
            FOC0B = 6,
            FOC0A,

            //SPCR
            SPR0 = 0,
            SPR1,
            CPHA,
            CPOL,
            MSTR,
            DORD,
            SPE,
            SPIE,

            //SPSR
            SPI2X = 0,
            WCOL  = 6,
            SPIF,

            //ACSR
            ACIS0 = 0,
            ACIS1,
            ACIC,
            ACIE,
            ACI,
            ACO,
            ACBG,
            ACD,

            //SMCR
            SE = 0,
            SM0,
            SM1,
            SM2,

            //MCUSR
            PORF = 0,
            EXTRF,
            BORF,
            WDRF,

            //MCUCR
            IVCE = 0,
            IVSEL,
            PUD = 4,
            BODSE,
            BODS,

            //SPMCSR
            SPMEN = 0,
            PGERS,
            PGWRT,
            BLBSET,
            RWWSRE,
            SIGRD,
            RWWSB,
            SPMIE,

            //SPL
            SP0,
            SP1,
            SP2,
            SP3,
            SP4,
            SP5,
            SP6,
            SP7,

            //SPH
            SP8,
            SP9,
            SP10,

            //SREG
            C = 0,
            Z,
            N,
            V,
            S,
            H,
            T,
            I,

            //WDTCSR
            WDP0 = 0,
            WDP1,
            WDP2,
            WDE,
            WDCE,
            WDP3,
            WDIE,
            WDIF,

            //CLKPR
            CLKPS0 = 0,
            CLKPS1,
            CLKPS2,
            CLKPS3,
            CLKPCE = 7,

            //PRR
            PRADC = 0,
            PRUSART0,
            PRSPI,
            PRTIM1,
            PRTIM0 = 5,
            PRTIM2,
            PRTWI,

            //PCICR
            PCIE0 = 0,
            PCIE1,
            PCIE2,

            //EICRA
            ISC00 = 0,
            ISC01,
            ISC10,
            ISC11,

            //PCMSK0
            PCINT0 = 0,
            PCINT1,
            PCINT2,
            PCINT3,
            PCINT4,
            PCINT5,
            PCINT6,
            PCINT7,

            //PCMSK1
            PCINT8 = PCINT0,
            PCINT9,
            PCINT10,
            PCINT11,
            PCINT12,
            PCINT13,
            PCINT14,

            //PCMSK2
            PCINT16 = PCINT0,
            PCINT17,
            PCINT18,
            PCINT19,
            PCINT20,
            PCINT21,
            PCINT22,
            PCINT23,

            //TIMSK0
            TOIE0 = 0,
            OCIE0A,
            OCIE0B,

            //TIMSK1
            TOIE1 = 0,
            OCIE1A,
            OCIE1B,
            ICIE1 = 5,

            //TIMSK2
            TOIE2 = 0,
            OCIE2A,
            OCIE2B,

            //ADCSRA
            ADPS0 = 0,
            ADPS1,
            ADPS2,
            ADIE,
            ADIF,
            ADATE,
            ADSC,
            ADEN,

            //ADCSRB
            ADTS0 = 0,
            ADTS1,
            ADTS2,
            ACME = 6,

            //ADMUX
            MUX0 = 0,
            MUX1,
            MUX2,
            MUX3,
            ADLAR = 5,
            REFS0,
            REFS1,

            //DIDR0
            ADC0D = 0,
            ADC1D,
            ADC2D,
            ADC3D,
            ADC4D,
            ADC5D,

            //DIDR1
            AIN0D=0,
            AIN1D,

            //TCCR1A
            WGM10 = 0,
            WGM11,
            COM1B0 = 4,
            COM1B1,
            COM1A0,
            COM1A1,

            //TCCR1B
            CS10=0,
            CS11,
            CS12,
            WGM12,
            WGM13,
            ICES1=6,
            ICNC1,

            //TCCR1C
            FOC1B = 6,
            FOC1A,

            //TCCR2A
            WGM20 = 0,
            WGM21,
            COM2B0 = 4,
            COM2B1,
            COM2A0,
            COM2A1,

            //TCCR2B
            CS20 = 0,
            CS21,
            CS22,
            WGM22,
            FOC2B=6,
            FOC2A,

            //ASSR
            TCR2BUB = 0,
            TCR2AUB,
            OCR2BUB,
            OCR2AUB,
            TCN2UB,
            AS2,
            EXCLK,

            //TWSR
            TWPS0 = 0,
            TWPS1,
            TWS3 = 4,
            TWS4,
            TWS5,
            TWS6,
            TWS7,

            //TWAR
            TWGCE = 0,
            TWA0,
            TWA1,
            TWA2,
            TWA3,
            TWA4,
            TWA5,
            TWA6,

            //TWCR
            TWIE = 0,
            TWEN = 2,
            TWWC,
            TWSTO,
            TWSTA,
            TWEA,
            TWINT,

            //TWAMR
            TWAM0 = 1,
            TWAM1,
            TWAM2,
            TWAM3,
            TWAM4,
            TWAM5,
            TWAM6,

            //UCSR0A
            MPCM0 = 0,
            U2X0,
            UPE0,
            DOR0,
            FE0,
            UDRE0,
            TXC0,
            RXC0,

            //UCSR0B
            TXB80 = 0,
            RXB80,
            UCSZ02,
            TXEN0,
            RXEN0,
            UDRIE0,
            TXCIE0,
            RXCIE0,

            //UCSR0C
            UCPOL0 = 0,
            UCSZ00,
            UCSZ01,
            USBS0,
            UPM00,
            UPM01,
            UMSEL00,
            UMSEL01
        };
    }
}
#endif // ATMEGA328P_H
