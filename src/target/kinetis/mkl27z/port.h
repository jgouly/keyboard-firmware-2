#define PORTC_PCR0 p_addr32(0x4004B000) // Pin Control Register n

#define PORTB_PCR19 p_addr32(0x4004A04C) // Pin Control Register n

#define GPIOB_PDDR p_addr32(0x400FF054) // Port Data Direction Register
#define GPIOC_PDDR p_addr32(0x400FF094) // Port Data Direction Register

#define GPIOB_PSOR p_addr32(0x400FF044) // Port Set Output Register
#define GPIOC_PSOR p_addr32(0x400FF084) // Port Set Output Register

#define PORT_PCR_MUX(n) ((uint32_t)(((n)&7) << 8)) // Pin Mux Control
#define PORT_PCR_DSE ((uint32_t)0x00000040)        // Drive Strength Enable
