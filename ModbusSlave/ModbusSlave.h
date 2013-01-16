/*  Modbus over serial line - RTU Slave for Arduino
 *  
 *  See Modbus_slave.cpp for more info and arduino sketch example code
 */ 

#ifndef MODBUS_SLAVE_h
#define MODBUS_SLAVE_h

/* Modbus RTU common parameters, the Master MUST use the same parameters */
enum {
        MB_SLAVE = 1,   /* modbus slave id */
};

/* Slave registers enumeration for referencing regs[] datamap array */
enum {        
        MB_REG0,      
        MB_REG1,       
        MB_REGS     /* total number of registers on slave */
};

/* 
 *This is the slave's modbus holding register data map. Use this array
 *to get or set data from/to the holding registers. This array has size
 *MB_REGS.
 */
extern int regs[];

/* 
 *When the master changes (a) register(s), use this struct to check
 *which one(s). Set written.num_regs back to zero after having checked.
 */
typedef struct lastwrite {  
        int start_addr;     
        int num_regs;
} lastwrite;
extern lastwrite written; 

/* 
 * init_mb_slave(baud, parity, tx_en_pin)
 *
 * sets the communication parameters for of the serial line.
 *
 * baud: baudrate in bps (typical values 9600, 19200... 115200)
 * parity: a single character sets the parity mode: 
 *         'n' for no parity; 'e' for even parity, 'o' for odd parity.
 * tx_en_pin: arduino pin number that controls transmision/reception
 *        of an external half-duplex device (e.g. a RS485 interface chip).
 *        0 or 1 disables this function (for a two-device network)
 *        >2 for point-to-multipoint topology (e.g. several arduinos)
 */
void init_mb_slave(long baud, char parity, char txenpin);

/*
 * start_mb_slave(slave_id, holding_regs_array, number_of_regs)
 * 
 * checks if there is any valid request from the modbus master. If there is,
 * performs the action requested
 * 
 * slave: slave id (1 to 127)
 * regs: an array with the holding registers. They start at address 1 (master point of view)
 * regs_size: total number of holding registers, i.e. the size of the array regs.
 * returns: 0 if no request from master,
 * NO_REPLY (-1) if no reply is sent to the master
 * an exception code (1 to 4) in case of a modbus exceptions
 * the number of bytes sent as reply ( > 4) if OK.
 */
int start_mb_slave(unsigned char slave, int *regs, unsigned int regs_size);

#endif
