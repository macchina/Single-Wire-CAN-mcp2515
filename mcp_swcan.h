/*
  mcp_swcan.h
  2017 Copyright (c) Macchina LLC.  All right reserved.

  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)

  The MIT License (MIT)

  Copyright (c) 2017 Macchina LLC.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef _MCP2515_SW_CAN_H_
#define _MCP2515_SW_CAN_H_

#include <mcp_can.h>

class SWcan : public MCP_CAN
{
  public:
    SWcan(INT8U _CS) : MCP_CAN(_CS){};
    void setupSW(unsigned long addr);
    void mode(byte mode);

  private:
    unsigned long address;
};

#endif