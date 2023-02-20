/* Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef DIAGNOSTIC_CLIENT_LIB_APPL_SRC_COMMON_DIAGNOSTIC_MANAGER_H
#define DIAGNOSTIC_CLIENT_LIB_APPL_SRC_COMMON_DIAGNOSTIC_MANAGER_H
/* includes */
#include "common_Header.h"
#include "include/diagnostic_client.h"
#include "include/diagnostic_client_message_type.h"
#include "libJsonParser/jsonParser.h"

namespace diag {
namespace client {
// forward declaration
namespace conversation {
class DiagClientConversation;
}

namespace common {
using property_tree = libOsAbstraction::libBoost::jsonparser::boostTree;

/*
 @ Class Name        : DiagnosticManager
 @ Class Description : Parent class to create DCM and DEM class                            
 */
class DiagnosticManager {
public:
  //ctor
  explicit DiagnosticManager(/* DiagnosticManagerPluginFactory &plugin_factory, */
                             property_tree &ptree);

  // dtor
  virtual ~DiagnosticManager();

  // main function
  virtual void Main();

  // signal shutdown
  virtual void SignalShutdown();

  // Initialize
  virtual void Initialize() = 0;

  // Run
  virtual void Run() = 0;

  // Shutdown
  virtual void Shutdown() = 0;

  // Function to get the diagnostic client conversation
  virtual diag::client::conversation::DiagClientConversation &GetDiagnosticClientConversation(
      std::string conversation_name) = 0;

  // Send Vehicle Identification Request and get response
  virtual std::pair<diag::client::DiagClient::VehicleResponseResult,
                    diag::client::vehicle_info::VehicleInfoMessageResponsePtr>
  SendVehicleIdentificationRequest(diag::client::vehicle_info::VehicleInfoListRequestType vehicle_info_request) = 0;

  // Get the list of available Diagnostic Server
  virtual diag::client::vehicle_info::VehicleInfoMessageResponsePtr GetDiagnosticServerList() = 0;

protected:
  // store the json tree
  property_tree &ptree_e;

private:
  // flag to terminate the main thread
  bool exit_requested_;
  // conditional variable to block the thread
  std::condition_variable cond_var;
  // For locking critical section of code
  std::mutex mutex_;
};
}  // namespace common
}  // namespace client
}  // namespace diag
#endif  // DIAGNOSTIC_CLIENT_LIB_APPL_SRC_COMMON_DIAGNOSTIC_MANAGER_H