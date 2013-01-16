/*

  Basic.pde - example using ModbusMaster library
  
  This file is part of ModbusMaster.K
  
  ModbusMaster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ModbusMaster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with ModbusMaster.  If not, see <http://www.gnu.org/licenses/>.
  
  Written by Doc Walker (Rx)
  Copyright © 2009-2011 Doc Walker <dfwmountaineers at gmail dot com>
  
*/

#include <ModbusMaster.h>


// instantiate ModbusMaster object as slave ID 2
// defaults to serial port 0 since no port was specified
ModbusMaster node(1);


void setup()
{
  // initialize Modbus communication baud rate
  node.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}
int a;

void loop()
{
  static uint32_t i;
  uint8_t j, result;
  uint16_t data[6];

  
  i++;
  
  // set word 0 of TX buffer to least-significant word of counter (bits 15..0) mete en el buffer EL VALOR DE i al bit 0
  node.setTransmitBuffer(0, lowWord(i));
  
  // set word 1 of TX buffer to most-significant word of counter (bits 31..16) mete en el buffer el valor de i al bit 1
  node.setTransmitBuffer(1, lowWord(i));
  
  // slave: write TX buffer to (2) 16-bit registers starting at register 0   manda lo que hay en el buffer al esclavo :2 registros a partir del 100
  result = node.writeMultipleRegisters(100, 2);
  
  // slave: read (6) 16-bit registers starting at register 2 to RX buffer    lee del esclavo  2 regitros a partir del registro 100
  result = node.readHoldingRegisters(100, 2);

  
  
  // do something with data if read is successful .si esta bien echa la comunicacion
 if (result == node.ku8MBSuccess)
  {
      data[0] = node.getResponseBuffer(0);     // metenmos en data[0] el dato que lee del esclavo del bite 0
      data[1] = node.getResponseBuffer(1);     // metenmos en data[0] el dato que lee del esclavo del bite 0
  
  
      if (data[0]%2==0)
       {
          digitalWrite(12,HIGH);
       }
      else
       {
          digitalWrite(12,LOW);
       }
       if (data[1]%2==0)
       {
          digitalWrite(13,LOW);
       }
      else
       {
          digitalWrite(13,HIGH);
       }
  }
}

