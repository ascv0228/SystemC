#include "systemc.h"
#include "../ALU.h"
#include "../Monitor.h"
#include "../Pattern.h"
#include "../clockreset.h"
#include "cassert"
#include "cwr_dynamic_loader.h"
#include "cwr_sc_dynamic_stubs.h"
#include "cwr_sc_hierarch_module.h"
#include "cwr_sc_object_creator.h"
#include "scmlinc/scml_abstraction_level_switch.h"
#include "scmlinc/scml_property_registry.h"

using namespace conf;
using namespace std;


class ALU0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "ALU/ALU: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&ALU::A, "A" , string(static_cast<sc_object*>(result)->name()) + ".A" );
       conf::stub_port_registrator<>::register_stub_port(&ALU::B, "B" , string(static_cast<sc_object*>(result)->name()) + ".B" );
       conf::stub_port_registrator<>::register_stub_port(&ALU::OpCode, "OpCode" , string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
       conf::stub_port_registrator<>::register_stub_port(&ALU::Result, "Result" , string(static_cast<sc_object*>(result)->name()) + ".Result" );
       conf::stub_port_registrator<>::register_stub_port(&ALU::Zero, "Zero" , string(static_cast<sc_object*>(result)->name()) + ".Zero" );
       conf::stub_port_registrator<>::register_stub_port(&ALU::Overflow, "Overflow" , string(static_cast<sc_object*>(result)->name()) + ".Overflow" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "ALU/ALU: " << hierach_name << " created." << std::endl; }
      ALU* result = new ALU(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->A, string(static_cast<sc_object*>(result)->name()) + ".A" );
       cwr_sc_object_registry::inst().addPort(&result->B, string(static_cast<sc_object*>(result)->name()) + ".B" );
       cwr_sc_object_registry::inst().addPort(&result->OpCode, string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
       cwr_sc_object_registry::inst().addPort(&result->Result, string(static_cast<sc_object*>(result)->name()) + ".Result" );
       cwr_sc_object_registry::inst().addPort(&result->Zero, string(static_cast<sc_object*>(result)->name()) + ".Zero" );
       cwr_sc_object_registry::inst().addPort(&result->Overflow, string(static_cast<sc_object*>(result)->name()) + ".Overflow" );
      return result;
    }
  }
};


class Clock0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int division = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "division");

    int cycle = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "cycle");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Clock::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: " << hierach_name << " created." << std::endl; }
      Clock* result = new Clock(name.c_str(), division, cycle);
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    }
  }
};

template <class BC>
class BusCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new BC(name.c_str(), helper);
    }
  }
};

template <class GBC>
class GeneratedBlockCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new GBC(name.c_str(), helper);
    }
  }
};



class Monitor0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Monitor::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::clock, "clock" , string(static_cast<sc_object*>(result)->name()) + ".clock" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::A, "A" , string(static_cast<sc_object*>(result)->name()) + ".A" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::B, "B" , string(static_cast<sc_object*>(result)->name()) + ".B" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::OpCode, "OpCode" , string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::Result, "Result" , string(static_cast<sc_object*>(result)->name()) + ".Result" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::Zero, "Zero" , string(static_cast<sc_object*>(result)->name()) + ".Zero" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::Overflow, "Overflow" , string(static_cast<sc_object*>(result)->name()) + ".Overflow" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: " << hierach_name << " created." << std::endl; }
      Monitor* result = new Monitor(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clock, string(static_cast<sc_object*>(result)->name()) + ".clock" );
       cwr_sc_object_registry::inst().addPort(&result->A, string(static_cast<sc_object*>(result)->name()) + ".A" );
       cwr_sc_object_registry::inst().addPort(&result->B, string(static_cast<sc_object*>(result)->name()) + ".B" );
       cwr_sc_object_registry::inst().addPort(&result->OpCode, string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
       cwr_sc_object_registry::inst().addPort(&result->Result, string(static_cast<sc_object*>(result)->name()) + ".Result" );
       cwr_sc_object_registry::inst().addPort(&result->Zero, string(static_cast<sc_object*>(result)->name()) + ".Zero" );
       cwr_sc_object_registry::inst().addPort(&result->Overflow, string(static_cast<sc_object*>(result)->name()) + ".Overflow" );
      return result;
    }
  }
};


class Pattern0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Pattern/Pattern: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Pattern::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::clock, "clock" , string(static_cast<sc_object*>(result)->name()) + ".clock" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::A, "A" , string(static_cast<sc_object*>(result)->name()) + ".A" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::B, "B" , string(static_cast<sc_object*>(result)->name()) + ".B" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::OpCode, "OpCode" , string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Pattern/Pattern: " << hierach_name << " created." << std::endl; }
      Pattern* result = new Pattern(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clock, string(static_cast<sc_object*>(result)->name()) + ".clock" );
       cwr_sc_object_registry::inst().addPort(&result->A, string(static_cast<sc_object*>(result)->name()) + ".A" );
       cwr_sc_object_registry::inst().addPort(&result->B, string(static_cast<sc_object*>(result)->name()) + ".B" );
       cwr_sc_object_registry::inst().addPort(&result->OpCode, string(static_cast<sc_object*>(result)->name()) + ".OpCode" );
      return result;
    }
  }
};


class Reset0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int _ticks = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "_ticks");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Reset::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: " << hierach_name << " created." << std::endl; }
      Reset* result = new Reset(name.c_str(), _ticks);
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    }
  }
};



extern void scv_tr_cwrdb_init();

int sc_main(int argc, char* argv[])
{
  scv_tr_cwrdb_init();
  ScObjectFactory::inst().addCreator ("ALU0", new ALU0Creator());
  ScObjectFactory::inst().addCreator ("Clock0", new Clock0Creator());
  ScObjectFactory::inst().addCreator ("Monitor0", new Monitor0Creator());
  ScObjectFactory::inst().addCreator ("Pattern0", new Pattern0Creator());
  ScObjectFactory::inst().addCreator ("Reset0", new Reset0Creator());
  ScObjectFactory::inst().addCreator ("sc_signal<bool>", new ScPrimChannelCreator<sc_signal<bool> >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_bv<3> >", new ScPrimChannelCreator<sc_signal<sc_bv<3> > >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_int<16> >", new ScPrimChannelCreator<sc_signal<sc_int<16> > >());
  ScPortFactory::inst().addCreator ("sc_in<bool>", new ScPortCreator<sc_in<bool> >());
  ScPortFactory::inst().addCreator ("sc_in<sc_bv<3> >", new ScPortCreator<sc_in<sc_bv<3> > >());
  ScPortFactory::inst().addCreator ("sc_in<sc_int<16> >", new ScPortCreator<sc_in<sc_int<16> > >());
  ScPortFactory::inst().addCreator ("sc_inout<bool>", new ScPortCreator<sc_inout<bool> >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_bv<3> >", new ScPortCreator<sc_inout<sc_bv<3> > >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_int<16> >", new ScPortCreator<sc_inout<sc_int<16> > >());
  ScPortFactory::inst().addCreator ("sc_out<bool>", new ScPortCreator<sc_out<bool> >());
  ScPortFactory::inst().addCreator ("sc_out<sc_bv<3> >", new ScPortCreator<sc_out<sc_bv<3> > >());
  ScPortFactory::inst().addCreator ("sc_out<sc_int<16> >", new ScPortCreator<sc_out<sc_int<16> > >());
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "ALU/ALU loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Clock/Clock loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Monitor/Monitor loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Pattern/Pattern loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Reset/Reset loaded." << std::endl; }

  scml_property_registry::inst().setXMLFile("Properties.xml");

  nSnps::nDynamicLoading::DynamicLoader dynamicLoader
    (scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/dynamic_load_info"));

  string xml_file_path = scml_property_registry::inst().getPropertyXmlFilePath();
  string hierarchy_xml_file = xml_file_path + "/" + 
    scml_property_registry::inst().getStringProperty(
      scml_property_registry::GLOBAL, "", "system_hierarchy_xml_file");

  cwr_sc_hierarch_module* HARDWARE = new cwr_sc_hierarch_module("HARDWARE", hierarchy_xml_file);

  // Enable/disable backdoor accesses
  scml_abstraction_level_switch::instance().set_simulation_mode(scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/simulation_mode")=="MODE_FULL_SIMULATION" ? scml_abstraction_level_switch::MODE_FULL_SIMULATION : scml_abstraction_level_switch::MODE_SPEED_OPTIMIZED);

  sc_start();

  if (sc_is_running()) {
    sc_stop();
  }
  delete HARDWARE;

  return 0;
}
