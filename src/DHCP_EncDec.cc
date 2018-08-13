/******************************************************************************
* Copyright (c) 2000-2018 Ericsson Telecom AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v2.0
* which accompanies this distribution, and is available at
* https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
*
* Contributors:
*   Jozsef Gyurusi - initial implementation and initial documentation
*   Attila Balasko
*   Gabor Bettesch
*   Gabor Szalai
*   Kulcsár Endre
*   Sandor Palugyai
******************************************************************************/
//
//  File:		DHCP_EncDec.cc
//  Rev:		R6C
//  Prodnr:             CNL 113 461

#include "DHCP_Types.hh"

namespace DHCP__Types {

using namespace DHCP__Options;

OCTETSTRING enc__PDU__DHCP(const PDU__DHCP& pdu)
{
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("Encoding PDU_DHCP: ");
	pdu.log();
	TTCN_Logger::end_event();
    }
    
    TTCN_Buffer buf;
    pdu.encode(PDU__DHCP_descr_, buf, TTCN_EncDec::CT_RAW);
    OCTETSTRING ret_val(buf.get_len(), buf.get_data());
    
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("PDU_DHCP after encoding: ");
	ret_val.log();
	TTCN_Logger::end_event();
    }
    return ret_val;
}


PDU__DHCP dec__PDU__DHCP(const OCTETSTRING& stream)
{
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("Decoding PDU_DHCP:       ");
	stream.log();
	TTCN_Logger::end_event();
    }

    TTCN_Buffer buf;
    buf.put_os(stream);
    PDU__DHCP ret_val;
    ret_val.decode(PDU__DHCP_descr_, buf, TTCN_EncDec::CT_RAW);
    
    // Remove char(0,0,0,0) from sname and file:
    //TTCN_Logger::begin_event(TTCN_DEBUG);
    DHCP__MSG dhcp_msg;
    if (ret_val.ischosen(PDU__DHCP::ALT_bOOT__REQUEST )) {
      if (ret_val.bOOT__REQUEST().sname().ischosen(DHCP__SNAME::ALT_sname)) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REQUEST().sname().sname().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REQUEST().sname().sname()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING sname_cut(len, (const char*)ret_val.bOOT__REQUEST().sname().sname());
        ret_val.bOOT__REQUEST().sname().sname() = sname_cut;
      }
     if (ret_val.bOOT__REQUEST().file().ischosen(DHCP__FILE::ALT_file)) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REQUEST().file().file().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REQUEST().file().file()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING file_cut(len, (const char*)ret_val.bOOT__REQUEST().file().file());
        ret_val.bOOT__REQUEST().file().file() = file_cut;
      }
    } else if (ret_val.ischosen(PDU__DHCP::ALT_bOOT__REPLY )) {
      if (ret_val.bOOT__REPLY().sname().ischosen( DHCP__SNAME::ALT_sname )) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REPLY().sname().sname().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REPLY().sname().sname()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING sname_cut(len, (const char*)ret_val.bOOT__REPLY().sname().sname());
        ret_val.bOOT__REPLY().sname().sname() = sname_cut;
      }
      if (ret_val.bOOT__REPLY().file().ischosen(DHCP__FILE::ALT_file )) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REPLY().file().file().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REPLY().file().file()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REP len: %d\n", len);
        CHARSTRING file_cut(len, (const char*)ret_val.bOOT__REPLY().file().file());
        ret_val.bOOT__REPLY().file().file() = file_cut;
      }
    }
    //TTCN_Logger::end_event();
    

    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("Decoded PDU_DHCP:  ");
	ret_val.log();
	TTCN_Logger::end_event();
    }
    return ret_val;
}

PDU__DHCP dec__PDU__DHCP__Opt82(const OCTETSTRING& stream, const DHCP__Option82__Format& format)
{
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("Decoding PDU_DHCP:       ");
	stream.log();
	TTCN_Logger::end_event();
    }

    TTCN_Buffer buf;
    buf.put_os(stream);
    PDU__DHCP ret_val;
    ret_val.decode(PDU__DHCP_descr_, buf, TTCN_EncDec::CT_RAW);
    
    // Remove char(0,0,0,0) from sname and file:
    //TTCN_Logger::begin_event(TTCN_DEBUG);
    DHCP__MSG dhcp_msg;
    if (ret_val.ischosen(PDU__DHCP::ALT_bOOT__REQUEST )) {
      if (ret_val.bOOT__REQUEST().sname().ischosen(DHCP__SNAME::ALT_sname)) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REQUEST().sname().sname().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REQUEST().sname().sname()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING sname_cut(len, (const char*)ret_val.bOOT__REQUEST().sname().sname());
        ret_val.bOOT__REQUEST().sname().sname() = sname_cut;
      }
      if (ret_val.bOOT__REQUEST().file().ischosen(DHCP__FILE::ALT_file)) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REQUEST().file().file().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REQUEST().file().file()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING file_cut(len, (const char*)ret_val.bOOT__REQUEST().file().file());
        ret_val.bOOT__REQUEST().file().file() = file_cut;
      }

      //Decode option 82 according the requested format
      int opt82_form = (int)format; 
      if (opt82_form > 0)
      {
        if (ret_val.bOOT__REQUEST().options().ispresent())
        {
          DHCP__OPTIONS__FIELD opt_field;
          opt_field = ret_val.bOOT__REQUEST().options();
          for (int i=0; i< opt_field.options().size_of(); i++)
            if(opt_field.options()[i].ischosen(DHCP__OPTION::ALT_relay__agent__information ))
            {
              DHCP__Relay__Agent__Information__OPTION rel_agent;
              rel_agent.code() = opt_field.options()[i].relay__agent__information().code();
              rel_agent.len() = opt_field.options()[i].relay__agent__information().len();

              for (int j=0; j< opt_field.options()[i].relay__agent__information().val().size_of(); j++)
              {
                rel_agent.val()[j].code() = opt_field.options()[i].relay__agent__information().val()[j].code();
                rel_agent.val()[j].id__len() = opt_field.options()[i].relay__agent__information().val()[j].id__len();
                TTCN_Buffer buf2;
                buf2.put_os(opt_field.options()[i].relay__agent__information().val()[j].id().string__format());
    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("buf2:       ");
	buf2.log();
	TTCN_Logger::end_event();
    }
                if (opt82_form == 1)
                  rel_agent.val()[j].id().cisco__format().decode(DHCP__Relay__Agent__Id__Cisco_descr_, buf2, TTCN_EncDec::CT_RAW);
                else if (opt82_form == 3)
                  rel_agent.val()[j].id().eda__configuration__format().decode(DHCP__Relay__Agent__Id__Eda_descr_, buf2, TTCN_EncDec::CT_RAW);
                else
                  rel_agent.val()[j].id().customer__number__format() =
                    oct2char(opt_field.options()[i].relay__agent__information().val()[j].id().string__format());
              }
              opt_field.options()[i].relay__agent__information() = rel_agent;
            }
          ret_val.bOOT__REQUEST().options() = opt_field;
        }
      }

    } else if (ret_val.ischosen(PDU__DHCP::ALT_bOOT__REPLY)) {
      if (ret_val.bOOT__REPLY().sname().ischosen( DHCP__SNAME::ALT_sname)) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REPLY().sname().sname().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REPLY().sname().sname()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REQ len: %d\n", len);
        CHARSTRING sname_cut(len, (const char*)ret_val.bOOT__REPLY().sname().sname());
        ret_val.bOOT__REPLY().sname().sname() = sname_cut;
      }
      if (ret_val.bOOT__REPLY().file().ischosen(DHCP__FILE::ALT_file )) {
        int len = 0;
        for (len=0; len<ret_val.bOOT__REPLY().file().file().lengthof(); len++) {
          if (((const char*)(ret_val.bOOT__REPLY().file().file()))[len]==0) break;
        }
        //TTCN_Logger::log_event("REP len: %d\n", len);
        CHARSTRING file_cut(len, (const char*)ret_val.bOOT__REPLY().file().file());
        ret_val.bOOT__REPLY().file().file() = file_cut;
      }
      //Decode option 82 according the requested format
      int opt82_form = (int)format; 
      if (opt82_form > 0)
      {
        if (ret_val.bOOT__REPLY().options().ispresent())
        {
          DHCP__OPTIONS__FIELD opt_field;
          opt_field = ret_val.bOOT__REPLY().options();
          for (int i=0; i< opt_field.options().size_of(); i++)
            if(opt_field.options()[i].ischosen(DHCP__OPTION::ALT_relay__agent__information ))
            {
              DHCP__Relay__Agent__Information__OPTION rel_agent;
              rel_agent.code() = opt_field.options()[i].relay__agent__information().code();
              rel_agent.len() = opt_field.options()[i].relay__agent__information().len();
              for (int j=0; j< opt_field.options()[i].relay__agent__information().val().size_of(); j++)
              {
                rel_agent.val()[j].code() = opt_field.options()[i].relay__agent__information().val()[j].code();
                rel_agent.val()[j].id__len() = opt_field.options()[i].relay__agent__information().val()[j].id__len();
                TTCN_Buffer buf2;
                buf2.put_os(opt_field.options()[i].relay__agent__information().val()[j].id().string__format());
                if (opt82_form == 1)
                  rel_agent.val()[j].id().cisco__format().decode(DHCP__Relay__Agent__Id__Cisco_descr_, buf2, TTCN_EncDec::CT_RAW);
                else if (opt82_form == 3)
                  rel_agent.val()[j].id().eda__configuration__format().decode(DHCP__Relay__Agent__Id__Eda_descr_, buf2, TTCN_EncDec::CT_RAW);
                else
                  rel_agent.val()[j].id().customer__number__format() =
                    oct2char(opt_field.options()[i].relay__agent__information().val()[j].id().string__format());
              }
              opt_field.options()[i].relay__agent__information() = rel_agent;
            }
          ret_val.bOOT__REPLY().options() = opt_field;
        }
      }

    }
    //TTCN_Logger::end_event();
    

    if (TTCN_Logger::log_this_event(TTCN_DEBUG)) {
	TTCN_Logger::begin_event(TTCN_DEBUG);
	TTCN_Logger::log_event("Decoded PDU_DHCP:  ");
	ret_val.log();
	TTCN_Logger::end_event();
    }
    return ret_val;
}

}//namespace
