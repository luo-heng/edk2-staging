/** @file

  IoMmuDxe driver installs EDKII_IOMMU_PROTOCOL to provide the support for DMA
  operations when memory encryption is enabled.

  Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2017, AMD Inc. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "IoMmu.h"

EFI_STATUS
EFIAPI
IoMmuDxeEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status;
  EFI_HANDLE    Handle;

  //
  // When memory encryption is enabled, install IoMmu protocol otherwise install the
  // placeholder protocol so that other dependent module can run.
  //
  if (MemEncryptIsEnabled (MEM_ENCRYPT_SEV_ENABLED) ||
    MemEncryptIsEnabled (MEM_ENCRYPT_TDX_ENABLED)) {
    Status = IoMmuInstallIoMmuProtocol ();
  } else {
    Handle = NULL;

    Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gIoMmuAbsentProtocolGuid,
                  NULL, NULL);
  }

  return Status;
}