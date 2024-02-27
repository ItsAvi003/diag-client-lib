/* Diagnostic Client library
 * Copyright (C) 2023  Avijit Dey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <gtest/gtest.h>

#include "include/create_diagnostic_client.h"
#include "include/diagnostic_client.h"
#include "main.h"

namespace test {
namespace component {
namespace test_cases {

TEST_F(DoipClientFixture, VerifyPreselectionModeEmpty) {
  doip_handler::DoipUdpHandler::VehicleAddrInfo vehicle_addr_response{0xFA25U, "ABCDEFGH123456789", "00:02:36:31:00:1c",
                                                                      "0a:0b:0c:0d:0e:0f"};
  // Create an expected vehicle identification response
  GetDoipTestUdpHandlerRef().SetExpectedVehicleIdentificationResponseToBeSent(vehicle_addr_response);

  // Send Vehicle Identification request and expect response
  diag::client::vehicle_info::VehicleInfoListRequestType vehicle_info_request{0u, ""};
  auto response_result{GetDiagClientRef().SendVehicleIdentificationRequest(vehicle_info_request)};

  // Verify Vehicle identification request with no payload
  EXPECT_TRUE(GetDoipTestUdpHandlerRef().VerifyVehicleIdentificationRequestWithExpectedVIN(""));

  // Verify Vehicle identification responses received successfully
  ASSERT_TRUE(response_result.HasValue());
  ASSERT_TRUE(response_result.Value());

  // Get the list of all vehicle available
  diag::client::vehicle_info::VehicleInfoMessage::VehicleInfoListResponseType response_collection{
      response_result.Value()->GetVehicleList()};

  EXPECT_EQ(response_collection.size(), 1U);
  EXPECT_EQ(response_collection[0].ip_address, DiagUdpIpAddress);
  EXPECT_EQ(response_collection[0].logical_address, vehicle_addr_response.logical_address);
  EXPECT_EQ(response_collection[0].vin, vehicle_addr_response.vin);
  EXPECT_EQ(response_collection[0].eid, vehicle_addr_response.eid);
  EXPECT_EQ(response_collection[0].gid, vehicle_addr_response.gid);
}

}  // namespace test_cases
}  // namespace component
}  // namespace test
