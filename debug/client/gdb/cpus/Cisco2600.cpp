// Copyright 2011-2016 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Cisco2600.hpp"

#include <algorithm>

#include <zycon/src/zycon.h>

#include "../../defs.hpp"
#include "../../DebuggerOptions.hpp"

/**
 * Returns the address size of the target architecture.
 *
 * @return The address size of the target architecture.
 */
unsigned int Cisco2600::getAddressSize() const {
  return 32;
}

/**
 * Returns the index of the PC register in the GDB register set.
 */
unsigned int Cisco2600::getInstructionPointerIndex() const {
  return 33;
}

/**
 * Returns the greet message of the Cisco 2600 GDB server.
 */
std::string Cisco2600::getGreetMessage() const {
  return "||||";
}

/**
 * Determines whether a message is a breakpoint message.
 */
bool Cisco2600::isBreakpointMessage(const std::string& msg) const {
  // On Cisco 2600, breakpoint messages equal greet messages.

  return msg == getGreetMessage();
}

/**
 * Returns descriptions of the registers that can be accessed through gdbserver.
 *
 * @param List of register descriptions.
 */
std::vector<RegisterDescription> Cisco2600::getRegisterNames() const {
  std::vector < RegisterDescription > regNames;

  std::string gprname = "??";
  regNames.push_back(makeRegisterDescription(gprname, 4, true));

  for (unsigned int i = 0; i < 32; i++) {
    if (i == 1) {
      std::string gprname = "sp";
      regNames.push_back(makeRegisterDescription(gprname, 4, true));
    } else {
      std::string gprname = "r" + zylib::zycon::toString(i);
      regNames.push_back(makeRegisterDescription(gprname, 4, true));
    }
  }

  regNames.push_back(makeRegisterDescription("pc", 4, true));
  regNames.push_back(makeRegisterDescription("msr", 4, true));
  regNames.push_back(makeRegisterDescription("lr", 4, true));
  regNames.push_back(makeRegisterDescription("ctr", 4, true));

  for (unsigned int i = 39; i < 62; i++) {
    std::string fprname = "u_reg" + zylib::zycon::toString(i);
    regNames.push_back(makeRegisterDescription(fprname, 4, true));
  }

  RegisterDescription cr("cr", 4, true);
  RegisterDescription cr0("cr0", 4, true);
  RegisterDescription cr1("cr1", 4, true);
  RegisterDescription cr2("cr2", 4, true);
  RegisterDescription cr3("cr3", 4, true);
  RegisterDescription cr4("cr4", 4, true);
  RegisterDescription cr5("cr5", 4, true);
  RegisterDescription cr6("cr6", 4, true);
  RegisterDescription cr7("cr7", 4, true);

  RegisterDescription xer("xer", 4, true);
  RegisterDescription fpscr("fpscr", 4, true);

  regNames.push_back(cr);
  regNames.push_back(cr0);
  regNames.push_back(cr1);
  regNames.push_back(cr2);
  regNames.push_back(cr3);
  regNames.push_back(cr4);
  regNames.push_back(cr5);
  regNames.push_back(cr6);
  regNames.push_back(cr7);
  regNames.push_back(xer);
  regNames.push_back(fpscr);

  // XER register flags and fields
  regNames.push_back(makeRegisterDescription("xer_so", 0, true));
  regNames.push_back(makeRegisterDescription("xer_ov", 0, true));
  regNames.push_back(makeRegisterDescription("xer_ca", 0, true));
  regNames.push_back(makeRegisterDescription("xer_bytecount", 2, true));

  // Condition register flags
  regNames.push_back(makeRegisterDescription("cr0_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr0_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr0_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr0_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr1_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr1_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr1_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr1_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr2_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr2_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr2_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr2_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr3_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr3_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr3_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr3_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr4_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr4_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr4_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr4_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr5_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr5_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr5_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr5_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr6_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr6_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr6_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr6_SO", 0, true));

  regNames.push_back(makeRegisterDescription("cr7_LT", 0, true));
  regNames.push_back(makeRegisterDescription("cr7_GT", 0, true));
  regNames.push_back(makeRegisterDescription("cr7_EQ", 0, true));
  regNames.push_back(makeRegisterDescription("cr7_SO", 0, true));

  regNames.push_back(makeRegisterDescription("fpscr_FX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_FEX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_QX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_UX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_ZX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_XX", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXNAN", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXISI", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXIDI", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXZDZ", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXIMZ", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXVC", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_FR", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_FI", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_FPRF", 1, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXSOFT", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXSQRT", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VXCVI", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_VE", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_OE", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_UE", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_ZE", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_XE", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_NI", 0, true));
  regNames.push_back(makeRegisterDescription("fpscr_RN", 1, true));

  return regNames;
}

NaviError Cisco2600::parseRegistersString(std::vector<RegisterValue>& registers,
                                          const std::string& regString) const {
  std::string gprname = "??";
  registers.push_back(makeRegisterValue(gprname, regString.substr(0, 8)));

  for (unsigned int i = 0; i < 32; i++) {
    if (i == 1) {
      std::string gprname = "sp";
      registers.push_back(
          makeRegisterValue(gprname, regString.substr(i * 8 + 8, 8), false,
                            true));
    } else {
      std::string gprname = "r" + zylib::zycon::toString(i);
      registers.push_back(
          makeRegisterValue(gprname, regString.substr(i * 8 + 8, 8)));
    }
  }

  registers.push_back(
      makeRegisterValue("pc", regString.substr(33 * 8, 8), true));
  registers.push_back(makeRegisterValue("msr", regString.substr(34 * 8, 8)));
  registers.push_back(makeRegisterValue("cr", regString.substr(35 * 8, 8)));
  registers.push_back(makeRegisterValue("lr", regString.substr(36 * 8, 8)));
  registers.push_back(makeRegisterValue("ctr", regString.substr(37 * 8, 8)));
  registers.push_back(makeRegisterValue("xer", regString.substr(38 * 8, 8)));
  registers.push_back(makeRegisterValue("fpscr", regString.substr(39 * 8, 8)));

  for (unsigned int i = 39; i < 62; i++) {
    std::string fprname = "u_reg" + zylib::zycon::toString(i);
    registers.push_back(makeRegisterValue(fprname, regString.substr(i * 8, 8)));
  }

  // XER register flags and fields
  unsigned int xer = strtoul(regString.substr(38 * 8, 8).c_str(), 0, 16);

  registers.push_back(
      makeRegisterValue("xer_so", zylib::zycon::toHexString(xer & 1)));
  registers.push_back(
      makeRegisterValue("xer_ov", zylib::zycon::toHexString((xer >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("xer_ca", zylib::zycon::toHexString((xer >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("xer_bytecount",
                        zylib::zycon::toHexString((xer >> 24) & 0x3F)));

  // Condition register sub fields
  unsigned int cr = strtoul(regString.substr(35 * 8, 8).c_str(), 0, 16);
  unsigned int cr0 = (cr & 0xF);
  unsigned int cr1 = ((cr >> 4) & 0xF);
  ((cr >> 8) & 0xF);
  unsigned int cr2 = ((cr >> 8) & 0xF);
  unsigned int cr3 = ((cr >> 12) & 0xF);
  unsigned int cr4 = ((cr >> 16) & 0xF);
  unsigned int cr5 = ((cr >> 20) & 0xF);
  unsigned int cr6 = ((cr >> 24) & 0xF);
  unsigned int cr7 = ((cr >> 28) & 0xF);

  registers.push_back(makeRegisterValue("cr0", zylib::zycon::toHexString(cr0)));
  registers.push_back(makeRegisterValue("cr1", zylib::zycon::toHexString(cr1)));
  registers.push_back(makeRegisterValue("cr2", zylib::zycon::toHexString(cr2)));
  registers.push_back(makeRegisterValue("cr3", zylib::zycon::toHexString(cr3)));
  registers.push_back(makeRegisterValue("cr4", zylib::zycon::toHexString(cr4)));
  registers.push_back(makeRegisterValue("cr5", zylib::zycon::toHexString(cr5)));
  registers.push_back(makeRegisterValue("cr6", zylib::zycon::toHexString(cr6)));
  registers.push_back(makeRegisterValue("cr7", zylib::zycon::toHexString(cr7)));

  // Condition register flags
  registers.push_back(
      makeRegisterValue("cr0_LT", zylib::zycon::toHexString(cr0 & 1)));
  registers.push_back(
      makeRegisterValue("cr0_GT", zylib::zycon::toHexString((cr0 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr0_EQ", zylib::zycon::toHexString((cr0 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr0_SO", zylib::zycon::toHexString((cr0 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr1_LT", zylib::zycon::toHexString(cr1 & 1)));
  registers.push_back(
      makeRegisterValue("cr1_GT", zylib::zycon::toHexString((cr1 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr1_EQ", zylib::zycon::toHexString((cr1 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr1_SO", zylib::zycon::toHexString((cr1 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr2_LT", zylib::zycon::toHexString(cr2 & 1)));
  registers.push_back(
      makeRegisterValue("cr2_GT", zylib::zycon::toHexString((cr2 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr2_EQ", zylib::zycon::toHexString((cr2 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr2_SO", zylib::zycon::toHexString((cr2 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr3_LT", zylib::zycon::toHexString(cr3 & 1)));
  registers.push_back(
      makeRegisterValue("cr3_GT", zylib::zycon::toHexString((cr3 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr3_EQ", zylib::zycon::toHexString((cr3 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr3_SO", zylib::zycon::toHexString((cr3 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr4_LT", zylib::zycon::toHexString(cr4 & 1)));
  registers.push_back(
      makeRegisterValue("cr4_GT", zylib::zycon::toHexString((cr4 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr4_EQ", zylib::zycon::toHexString((cr4 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr4_SO", zylib::zycon::toHexString((cr4 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr5_LT", zylib::zycon::toHexString(cr5 & 1)));
  registers.push_back(
      makeRegisterValue("cr5_GT", zylib::zycon::toHexString((cr5 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr5_EQ", zylib::zycon::toHexString((cr5 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr5_SO", zylib::zycon::toHexString((cr5 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr6_LT", zylib::zycon::toHexString(cr6 & 1)));
  registers.push_back(
      makeRegisterValue("cr6_GT", zylib::zycon::toHexString((cr6 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr6_EQ", zylib::zycon::toHexString((cr6 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr6_SO", zylib::zycon::toHexString((cr6 >> 3) & 1)));

  registers.push_back(
      makeRegisterValue("cr7_LT", zylib::zycon::toHexString(cr7 & 1)));
  registers.push_back(
      makeRegisterValue("cr7_GT", zylib::zycon::toHexString((cr7 >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("cr7_EQ", zylib::zycon::toHexString((cr7 >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("cr7_SO", zylib::zycon::toHexString((cr7 >> 3) & 1)));

  // floating point flags
  unsigned int fpscr = strtoul(regString.substr(39 * 8, 8).c_str(), 0, 16);

  registers.push_back(
      makeRegisterValue("fpscr_FX", zylib::zycon::toHexString(fpscr & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_FEX",
                        zylib::zycon::toHexString((fpscr >> 1) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VX",
                        zylib::zycon::toHexString((fpscr >> 2) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_QX",
                        zylib::zycon::toHexString((fpscr >> 3) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_UX",
                        zylib::zycon::toHexString((fpscr >> 4) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_ZX",
                        zylib::zycon::toHexString((fpscr >> 5) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_XX",
                        zylib::zycon::toHexString((fpscr >> 6) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXNAN",
                        zylib::zycon::toHexString((fpscr >> 7) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXISI",
                        zylib::zycon::toHexString((fpscr >> 8) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXIDI",
                        zylib::zycon::toHexString((fpscr >> 9) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXZDZ",
                        zylib::zycon::toHexString((fpscr >> 10) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXIMZ",
                        zylib::zycon::toHexString((fpscr >> 11) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXVC",
                        zylib::zycon::toHexString((fpscr >> 12) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_FR",
                        zylib::zycon::toHexString((fpscr >> 13) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_FI",
                        zylib::zycon::toHexString((fpscr >> 14) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_FPRF",
                        zylib::zycon::toHexString((fpscr >> 15) & 0x1F)));
  registers.push_back(
      makeRegisterValue("fpscr_VXSOFT",
                        zylib::zycon::toHexString((fpscr >> 21) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXSQRT",
                        zylib::zycon::toHexString((fpscr >> 22) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VXCVI",
                        zylib::zycon::toHexString((fpscr >> 23) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_VE",
                        zylib::zycon::toHexString((fpscr >> 24) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_OE",
                        zylib::zycon::toHexString((fpscr >> 25) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_UE",
                        zylib::zycon::toHexString((fpscr >> 26) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_ZE",
                        zylib::zycon::toHexString((fpscr >> 27) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_XE",
                        zylib::zycon::toHexString((fpscr >> 28) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_NI",
                        zylib::zycon::toHexString((fpscr >> 29) & 1)));
  registers.push_back(
      makeRegisterValue("fpscr_RN",
                        zylib::zycon::toHexString((fpscr >> 30) & 3)));

  return NaviErrors::SUCCESS;
}

///
/// \brief Cisco's version of Run-length encoding
///
/// Cisco uses two instead of one character as the repeat count. This overload
/// deals with the situation. You must use the GdbProtoCisco version when
/// dealing with devices from this vendor, since they make heavy use of the
/// encoding when sending memory or register contents.
///
bool Cisco2600::RunlengthDecode(std::string& encoded) const {
  std::string expanded;
  char to_repeat[2];
  char to_conv[3];
  unsigned int repeat;

  to_conv[2] = to_repeat[1] = 0;

  for (unsigned int i = 0; i < encoded.length(); i++) {
    if (encoded.at(i) == '*') {
      // "*7" is not allowed
      if (0 == i)
        return false;

      // "lalala*1" not allowed
      if ((encoded.length() - 2) == i)
        return false;

      to_repeat[0] = encoded.at(i - 1);

      // convert
      to_conv[0] = encoded.at(i + 1);
      to_conv[1] = encoded.at(i + 2);
      repeat = strtoul(to_conv, NULL, 16);

      // 0 repeat theoretically possible but very unlikely, generate error
      if (0 == repeat)
        return false;

      for (unsigned int j = 0; j < repeat; j++)
        expanded.append(to_repeat);

      // skip over multiplier
      i += 2;
    } else {
      to_repeat[0] = encoded.at(i);
      expanded.append(to_repeat);
    }
  }

  encoded.clear();
  encoded.append(expanded);

  return true;
}

/**
 * Returns information about the debugger options supported
 * by the Cisco 2600 debug client.
 */
DebuggerOptions Cisco2600::getDebuggerOptions() const {
  DebuggerOptions options;

  // It's not possible to terminate the router
  options.canTerminate = false;

  // The router is single-threaded
  options.canMultithread = false;

  // The Cisco 2600 GDB server does not provide memory maps
  options.canMemmap = false;

  // It's not possible to find out whether a memory region
  // is valid because the serial connection is too slow for
  // that.
  options.canValidMemory = false;

  options.hasStack = false;

  options.pageSize = 4096;

  return options;
}

/**
 * Detaches from the router
 */
NaviError Cisco2600::detach(IEventCallback* cb) const {
  // When the router resumes, it goes into console mode.
  // This is just as good as detaching because it won't
  // enter GDB mode again until a breakpoint is hit.

  if (resumeThread(0, cb)) {
    return NaviErrors::COULDNT_DETACH;
  }

  return NaviErrors::SUCCESS;
}
